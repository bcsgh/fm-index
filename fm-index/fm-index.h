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

#ifndef FM_INDEX_FM_INDEX_H_
#define FM_INDEX_FM_INDEX_H_

#include <set>
#include <string>
#include <string_view>
#include <vector>

#include "fm-index/wavelet-tree.h"

namespace fm_index {

class FMIndex {
 public:
  FMIndex(std::string text);

  int count(std::string_view);

 private:
  friend class FMIndexLookup;

  std::pair<size_t, size_t> Find(std::string_view);

  size_t Walk(size_t from);

  std::string bwt_;
  WaveletTree wt_;
  std::array<size_t, 256> cumulative_;
};

// An index of strings/records.
// Given a query, the set of records contaning that query can be returned,
// and then the content of those records looked up.
//
// This is intended to be used in contexts like an auto-compleet backend.
class FMIndexLookup : FMIndex {
 public:
  // Generate an index from a collection of *unique* records.
  FMIndexLookup(std::vector<std::string> text);

  std::set<size_t> FindCanonical(std::string_view q);
  // Lookup a string from it's canonical index.
  std::string_view Lookup(size_t i) { return text_[i]; }

 private:
  std::vector<std::string> text_;
};

}  // namespace fm_index

#endif  // FM_INDEX_FM_INDEX_H_
