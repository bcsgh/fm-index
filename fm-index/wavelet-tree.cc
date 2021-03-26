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

#include <stdlib.h>
#include <array>
#include <string_view>

namespace fm_index {
namespace {
//// Build a pop-count table for 8-bit numbers, at compile time.
template<int i> constexpr int popcount = (i & 0x1) + popcount<(i >> 1)>;
template<> constexpr int popcount<0> = 0;

template<int i, int... I> constexpr auto run = run<i - 1, i - 1, I...>;
template<int... I> constexpr int run<0, I...>[] = {popcount<I>...};

static auto kBitCounts = run<256>;
}  // namespace

WaveletTree::WaveletTree(std::string_view src, int step) : step_(step), src_(src) {
  // Counts for each vec.
  std::array<size_t, 512 - 1> counts;
  for (auto &i : counts) i = 0;

  // Populate bit masks
  for (const char c : src_) {
    size_t at = 0;
    for (unsigned char m = 0b10000000 ; m ; m >>= 1) {
      auto &bits = tree_[at].bits;
      auto &count = counts[at];

      bits.resize((count / 8) + 1);  // ensure there is room.
      if (c & m) bits[count / 8] |= (1 << (count % 8)); // populate bits

      count++;  // update for next iteration.
      at *= 2;
      at += (c & m) ? 2 : 1;
    }
  }

  // Construct running sums.
  for (auto &v : tree_) {
    v.pre.resize(v.bits.size() / step_ + 1);

    size_t sum = 0;
    for (size_t i = 0; i < v.bits.size() ; i++) {
      v.pre[i / step_] = (sum += kBitCounts[v.bits[i]]);
    }
  }
}

size_t WaveletTree::index(size_t i) const {
  const char c = src_[i];
  return index(c, i);
}

size_t WaveletTree::index(const char c, size_t i) const {
  size_t at = 0;

  for (unsigned char m = 0b10000000 ; m ; m >>= 1) {
    const auto &v = tree_[at];

    // Get indexes.
    unsigned char mask = ~(~0 << (i % 8));
    size_t last_byte = i / 8;
    size_t start_sum = last_byte / step_;
    size_t start_byte = start_sum * step_;

    if (last_byte >= v.bits.size()) {
      last_byte = v.bits.size();
      mask = 0;
    }

    // Cached sum
    auto count = (start_sum <= 0) ? 0 : v.pre[start_sum - 1];
    // Full bytes
    for (size_t off = start_byte; off < last_byte; off++) {
      count += kBitCounts[v.bits[off]];
    }
    // Partial byte
    if (mask) count += kBitCounts[v.bits[last_byte] & mask];  //?

    // Take or leave?
    i = (c & m) ? count : (i - count);

    // update for next iteration.
    at *= 2;
    at += (c & m) ? 2 : 1;
  }



  return i;
}

}  // namespace fm_index
