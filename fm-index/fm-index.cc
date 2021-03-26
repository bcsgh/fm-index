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

#include <array>
#include <iterator>
#include <string_view>

#include "fm-index/bw-transform.h"
#include "fm-index/wavelet-tree.h"
#include "glog/logging.h"

namespace fm_index {

FMIndex::FMIndex(std::string text) : bwt_(BwTransform(text)), wt_(bwt_) {
  for(auto &c : cumulative_) c = 0;
  for(auto c : text) cumulative_[c]++;

  size_t sum = 0;
  for(auto &c : cumulative_) {
    auto inc = c;
    c = sum;
    sum += inc;
  }
}

namespace {
// Wrap a container to iterate in reverse.

// TODO move this somewhere
template <typename T>
struct reversion_wrapper{ T& iterable; };

template <typename T>
auto begin(reversion_wrapper<T>& w) { return std::rbegin(w.iterable); }

template <typename T>
auto end(reversion_wrapper<T>& w) { return std::rend(w.iterable); }

template <typename T>
reversion_wrapper<T> reverse(T&& iterable) { return { iterable }; }

}  // namespace

// Return the indexes into the BTW for the query string:
// for the first and one past the last.
std::pair<size_t, size_t> FMIndex::Find(std::string_view q) {
  size_t low = 0, high = bwt_.size();

  for (const auto c : reverse(q)) {
    const auto start = cumulative_[c];
    low = start + wt_.index(c, low);
    high = start + wt_.index(c, high);
  }
  return {low, high};
}

int FMIndex::count(std::string_view q) {
  auto b = Find(q);
  return b.second - b.first;
}

}  // namespace fm_index
