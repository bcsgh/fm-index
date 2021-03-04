load("@bazel_rules//graphviz:graphviz.bzl", "gen_dot")
load("@bazel_rules//latex:latex.bzl", "tex_to_pdf")

gen_dot(
  name = "wavelet_graph",
  src = "wavelet.dot",
  out = "wavelet.png",
)

tex_to_pdf(
  name = "fm-index",
  src = "fm-index.tex",
  pdf = "fm-index.pdf",
  data = [":wavelet.png"],
)
