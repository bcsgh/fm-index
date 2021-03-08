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

#include "fm-index/fm-index.h"

#include <glob.h>

#include <fstream>
#include <sstream>
#include <string>

#include "absl/cleanup/cleanup.h"
#include "absl/random/random.h"
#include "absl/strings/str_cat.h"
#include "glog/logging.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace fm_index {
namespace {

using ::testing::Eq;
using ::testing::Ge;
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

class FmIndexTestP : public TestWithParam<Case> {};

TEST_P(FmIndexTestP, CountFind) {
  const std::string kTest = GetParam().content;
  FMIndex idx(kTest);

  // Pick something to look up.
  static auto* bitgen = new absl::BitGen;
  auto min = absl::Uniform<size_t>(*bitgen, 0, kTest.size() - 5);
  auto len = absl::Uniform<size_t>(*bitgen, 5, std::min<size_t>(kTest.size() - min, 30));
  auto f = std::string_view(kTest).substr(min, len);

  // count instances of f in kTest, the hard way.
  int c = 0;
  for (size_t s = kTest.find(f); s != std::string::npos;) {
    s = kTest.find(f, s + 1);
    c++;
  }

  EXPECT_THAT(idx.count(f), Eq(c)) << "[" << min << ", " << (min + len) << ")";
}

TEST_P(FmIndexTestP, CountMissing) {
  const std::string kTest = GetParam().content;

  // Find a string that
  int i = 0;
  std::string missing;
  for (int c = 10; c--; i += 37) {
    missing = absl::StrCat("X", kTest.substr(i % (kTest.size() - 9), 9));
    LOG(INFO) << "<<" << missing << ">>";
    if (kTest.find(missing) == std::string::npos) break;
  }
  ASSERT_THAT(kTest.find(missing), Eq(std::string::npos));

  FMIndex idx(kTest);
  EXPECT_THAT(idx.count(missing), Eq(0));
}

// Processes some literal strings.
constexpr auto kShortFixed = "hello world, this is a test of this structure,"
                             " don't worry, we think it works.";
INSTANTIATE_TEST_SUITE_P(
  Fixed, FmIndexTestP,
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
  All, FmIndexTestP,
  ValuesIn(GetFromFiles()),
  [](testing::TestParamInfo<Case> c) { return c.param.Name(); });

}  // namespace
}  // namespace fm_index
