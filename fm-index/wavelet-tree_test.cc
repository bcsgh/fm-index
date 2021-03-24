// Copyright (c) 2018, Benjamin Shropshire,
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "fm-index/wavelet-tree.h"

#include <glob.h>

#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "absl/cleanup/cleanup.h"
#include "glog/logging.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace fm_index {
namespace {

using ::testing::Eq;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

struct Case {
  std::string name;
  std::string content;

  std::string Name() {
    auto ret = name;
    for (auto &c : ret) if (!isalnum(c)) c = '_';
    return ret;
  }

  friend std::ostream& operator<<(std::ostream& o, const Case& c) {
    return o << c.name << "[" << c.content.size() << "]";
  }
};

class WaveletTreeTestP : public TestWithParam<Case> {};

TEST_P(WaveletTreeTestP, Basic) {
  const std::string kTest = GetParam().content;
  LOG(INFO) << "Create WaveletTree size: " << kTest.size() << " ...";
  WaveletTree wt(kTest);
  LOG(INFO) << "Created WaveletTree.";

  std::map<char, int> counts;
  for (size_t i = 0; i < kTest.size(); i++) {
    auto at = counts[kTest[i]]++;
    EXPECT_THAT(wt.index(i), Eq(at))
        << "Error at position " << i << " ('" << kTest[i] << "')";

    // Also check that things work if a different char is asked about.
    const char c = kTest[i] + 1;
    EXPECT_THAT(wt.index(c, i), Eq(counts[c]))
        << "Error at position " << i << " ('" << c << "')";
  }
}

// Processes some literal strings.
constexpr auto kShortFixed = "hello world, this is a test of this structure,"
                             " don't worry, we think it works.";
INSTANTIATE_TEST_SUITE_P(
  Fixed, WaveletTreeTestP,
  testing::Values(Case{"ShortFixed", kShortFixed}),
  [](testing::TestParamInfo<Case> c) { return c.param.Name(); });

// Grab and process all the sources files in this dir.
std::vector<Case> GetFromFiles() {
  glob_t pglob;
  pglob.gl_pathc = 0;
  pglob.gl_pathv = nullptr;
  pglob.gl_offs = 0;
  absl::Cleanup free_glob = [&pglob] { globfree(&pglob); };

  glob("fm-index/*.*", GLOB_MARK | GLOB_NOSORT, NULL, &pglob);

  std::vector<Case> ret;
  for (size_t i = 0 ; i < pglob.gl_pathc ; i++) {
    std::string file = pglob.gl_pathv[i];
    if (*file.rbegin() == '/') continue;

    std::ifstream t(file);
    std::stringstream buffer;
    buffer << t.rdbuf();

    // Dump things that are too long.
    if (buffer.str().size() > (16 << 10)) continue;

    ret.emplace_back(Case{std::move(file), std::move(buffer.str())});
  }

  return ret;
}

INSTANTIATE_TEST_SUITE_P(
  All, WaveletTreeTestP,
  ValuesIn(GetFromFiles()),
  [](testing::TestParamInfo<Case> c) { return c.param.Name(); });

INSTANTIATE_TEST_SUITE_P(
  Large, WaveletTreeTestP,
  ValuesIn(GetFromFiles("external/com_github_dwyl_english_words/words.txt", 5<<20)),
  [](testing::TestParamInfo<WtCase> c) { return c.param.Name(); });

}  // namespace
}  // namespace fm_index
