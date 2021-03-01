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

#include "fm-index/bw-transform.h"

#include <algorithm>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

namespace fm_index {

std::string BwTransform(const std::string_view inp) {
  const auto s = inp.size();
  std::vector<size_t> shuf(s);
  for(size_t i = 0; i < shuf.size(); i++) shuf[i] = i;

  std::sort(shuf.begin(), shuf.end(), [&inp, s](size_t a, size_t b) {

    size_t l1 = std::min({
      (s - a),
      (s - b),
      ((a > b) ? (a - b) : (b - a)),
    });
    size_t a1 = (a + l1) % s, b1 = (b + l1) % s;
    size_t l2 = std::min({
      (s - a1),
      (s - b1),
      ((a1 > b1) ? (a1 - b1) : (b1 - a1)),
    });
    size_t a2 = (a1 + l2) % s, b2 = (b1 + l2) % s;
    size_t l3 = s - l1 - l2;

    using I = std::tuple<std::string_view, std::string_view, std::string_view>;
    I A{inp.substr(a, l1), inp.substr(a1, l2), inp.substr(a2, l3)};
    I B{inp.substr(b, l1), inp.substr(b1, l2), inp.substr(b2, l3)};
    return A < B;
  });

  std::string ret(s, '\0');
  for(size_t i = 0; i < shuf.size(); i++) ret[i] = inp[(shuf[i] + s - 1) % s];
  return ret;
}

}  // namespace fm_index
