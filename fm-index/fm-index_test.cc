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

#include "fm-index/fm-index_test.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace fm_index {
namespace {

using ::testing::ValuesIn;

// Processes some literal strings.
constexpr auto kShortFixed = "hello world, this is a test of this structure,"
                             " don't worry, we think it works.";
constexpr auto kLongFixed = "one line\ntwo lines\nthree lines\nfloor!";
INSTANTIATE_TEST_SUITE_P(
  Fixed, FmIndexTestP,
  testing::Values(
    FmCase{"ShortFixed", kShortFixed},
    FmCase{"LongFixed", kLongFixed}
  ),
  [](testing::TestParamInfo<FmCase> c) { return c.param.Name(); });

INSTANTIATE_TEST_SUITE_P(
  All, FmIndexTestP,
  ValuesIn(GetFromFiles("fm-index/*.*")),
  [](testing::TestParamInfo<FmCase> c) { return c.param.Name(); });

}  // namespace
}  // namespace fm_index
