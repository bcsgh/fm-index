workspace(name = "com_github_bcsgh_fm_index")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

#############################################
# needed by com_github_glog_glog
git_repository(
    name = "com_github_gflags_gflags",
    commit = "827c769e5fc98e0f2a34c47cef953cc6328abced",  # current as of 2021/02/17
    remote = "git://github.com/gflags/gflags.git",
    shallow_since = "1604052972 +0000",
)

#############################################
git_repository(
    name = "com_github_glog_glog",
    commit = "764162569a26da4401a8b59c96ca3525d7618a28",  # current as of 2021/06/15
    remote = "git://github.com/google/glog.git",
    shallow_since = "1623780547 +0200",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "e2239ee6043f73722e7aa812a459f54a28552929",  # current as of 2021/06/15
    remote = "git://github.com/google/googletest.git",
    shallow_since = "1623433346 -0700",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "311bbd2e50ea35e921a08186840d3b6ca279e880",  # current as of 2021/06/15
    remote = "git://github.com/abseil/abseil-cpp.git",
    shallow_since = "1623359638 -0400",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "b13bb0a8ff74dc0ce06470ff07a105e377fc5fdc",  # current as of 2021/06/15
    remote = "git://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1623790590 -0700",
)

#############################################
new_git_repository(
    name = "com_github_dwyl_english_words",
    build_file = "//extern:BUILD.raw_files",
    commit = "11735d0d68f051b817ad224e14d999acc94fcf00",  # current as of 2021/03/16
    remote = "https://github.com/dwyl/english-words",
    shallow_since = "1602748980 +0100",
)
