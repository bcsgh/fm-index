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

cc_library(
    name = "test_main",
    srcs = ["test_main.cc"],
    deps = [
        "@com_github_glog_glog//:glog",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/time",
        "@com_google_googletest//:gtest",
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
        ":test_main",
        "@com_google_googletest//:gtest",
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
        ":test_main",
        ":wavelet-tree",
        "@com_github_glog_glog//:glog",
        "@com_google_absl//absl/cleanup",
        "@com_google_googletest//:gtest",
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
        "@com_github_glog_glog//:glog",
    ],
)

cc_library(
    name = "fm-index_test_lib",
    srcs = ["fm-index_test_lib.cc"],
    hdrs = ["fm-index_test.h"],
    deps = [
        ":fm-index",
        ":test_main",
        "@com_github_glog_glog//:glog",
        "@com_google_absl//absl/cleanup",
        "@com_google_absl//absl/random",
        "@com_google_absl//absl/strings",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "fm-index_test",
    timeout = "short",
    srcs = ["fm-index_test.cc"],
    data = glob(["*"]),
    deps = [
        ":fm-index_test_lib",
        ":test_main",
        "@com_google_googletest//:gtest",
    ],
)
