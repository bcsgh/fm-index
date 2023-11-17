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
    commit = "b10fad38c4026a29ea6561ab15fc4818170d1c10",  # current as of 2023/11/12
    remote = "https://github.com/google/googletest.git",
    shallow_since = "1698701593 -0700",
)

#############################################
git_repository(
    name = "com_google_absl",
    commit = "483a2d59e649179ea9d9bc4d808f6c9d16646f9d",  # current as of 2023/11/12
    remote = "https://github.com/abseil/abseil-cpp.git",
    shallow_since = "1699496241 -0800",
)

#############################################
git_repository(
    name = "bazel_rules",
    commit = "be9e3fa50c41cf9a1e93d2288ce02c67047d71c3",  # current as of 2023/11/16
    remote = "https://github.com/bcsgh/bazel_rules.git",
    shallow_since = "1700184387 -0800",
)

load("@bazel_rules//repositories:repositories.bzl", "jsoncpp")

#############################################
load("@bazel_rules//latex:repo.bzl", "latex_toolchain_repository")
latex_toolchain_repository(name="local_latex_toolchain")
register_toolchains("@local_latex_toolchain//:local_latex")

#############################################
git_repository(
    name = "com_github_dwyl_english_words",
    commit = "a77cb15f4f5beb59c15b945f2415328a6b33c3b0",  # current as of 2023/11/12
    remote = "https://github.com/dwyl/english-words",
    build_file = "//extern:BUILD.raw_files",
    shallow_since = "1667945476 +0000",
)

#############################################
jsoncpp()
