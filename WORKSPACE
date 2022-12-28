workspace(name = "com_github_bcsgh_fm_index")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

#############################################
# Bazel Skylib.
http_archive(
    name = "bazel_skylib",
    urls = ["https://github.com/bazelbuild/bazel-skylib/releases/download/1.2.1/bazel-skylib-1.2.1.tar.gz"],
    sha256 = "f7be3474d42aae265405a592bb7da8e171919d74c16f082a5457840f06054728",
)

#############################################
git_repository(
    name = "com_google_googletest",
    commit = "3026483ae575e2de942db5e760cf95e973308dd5",  # current as of 2022/10/25
    remote = "https://github.com/google/googletest.git",
    shallow_since = "1666712359 -0700",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "827940038258b35a29279d8c65b4b4ca0a676f8d",  # current as of 2022/10/27
    remote = "https://github.com/abseil/abseil-cpp.git",
    shallow_since = "1666903548 -0700",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "19c3dc86fd46d68f13fdb51717ff871e32e5447a",  # current as of 2022/12/27
    remote = "https://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1672162894 -0800",
)

load("@bazel_rules//repositories:repositories.bzl", "jsoncpp")

#############################################
new_git_repository(
    name = "com_github_dwyl_english_words",
    commit = "60eb05a1285cae4ff306f0d9dcea407490cf2a99",  # current as of 2022/10/25
    remote = "https://github.com/dwyl/english-words",
    build_file = "//extern:BUILD.raw_files",
    shallow_since = "1662553508 +0100",
)

#############################################
jsoncpp()
