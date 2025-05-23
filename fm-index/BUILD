# Copyright (c) 2018, Benjamin Shropshire,
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 3. Neither the name of the copyright holder nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

test_suite(
    name = "manual_tests",
    tags = ["manual"],
    tests = [
        # Slow tests
        ":fm-index_slow_test",
    ],
)

########################################################
cc_library(
    name = "bw-transform",
    srcs = ["bw-transform.cc"],
    hdrs = ["bw-transform.h"],
)

cc_test(
    name = "bw-transform_test",
    timeout = "short",
    srcs = ["bw-transform_test.cc"],
    deps = [
        ":bw-transform",
        "@com_github_bcsgh_test_base//test_base:test_main",
        "@googletest//:gtest",
    ],
)

########################################################
cc_library(
    name = "wavelet-tree",
    srcs = ["wavelet-tree.cc"],
    hdrs = ["wavelet-tree.h"],
)

cc_test(
    name = "wavelet-tree_test",
    timeout = "short",
    srcs = ["wavelet-tree_test.cc"],
    data = glob(["*"]) + ["@com_github_dwyl_english_words//:words.txt"],
    deps = [
        ":wavelet-tree",
        "@abseil-cpp//absl/cleanup",
        "@abseil-cpp//absl/log:log",
        "@com_github_bcsgh_test_base//test_base:test_main",
        "@googletest//:gtest",
    ],
)

########################################################
cc_library(
    name = "fm-index",
    srcs = ["fm-index.cc"],
    hdrs = ["fm-index.h"],
    deps = [
        ":bw-transform",
        ":wavelet-tree",
        "@abseil-cpp//absl/log:log",
        "@abseil-cpp//absl/strings",
    ],
)

cc_library(
    name = "fm-index_test_lib",
    srcs = ["fm-index_test_lib.cc"],
    hdrs = ["fm-index_test.h"],
    deps = [
        ":fm-index",
        "@abseil-cpp//absl/cleanup",
        "@abseil-cpp//absl/log:log",
        "@abseil-cpp//absl/random",
        "@abseil-cpp//absl/strings",
        "@com_github_bcsgh_test_base//test_base:test_main",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "fm-index_test",
    timeout = "moderate",
    srcs = ["fm-index_test.cc"],
    data = glob(["*"]) + ["@com_github_dwyl_english_words//:words.txt"],
    deps = [
        ":fm-index_test_lib",
        "@com_github_bcsgh_test_base//test_base:test_main",
        "@googletest//:gtest",
    ],
)

cc_test(
    name = "fm-index_slow_test",
    timeout = "moderate",
    srcs = ["fm-index_slow_test.cc"],
    data = ["@com_github_dwyl_english_words//:words.txt"],
    shard_count = 2,  # 2x len(data)
    tags = ["manual"],
    deps = [
        ":fm-index_test_lib",
        "@com_github_bcsgh_test_base//test_base:test_main",
        "@googletest//:gtest",
    ],
)
