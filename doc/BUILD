load("@com_github_bcsgh_graphviz//graphviz:graphviz.bzl", "gen_dot")
load("@com_github_bcsgh_latex_rules//latex:latex.bzl", "tex_to_pdf")

gen_dot(
    name = "wavelet_graph",
    src = "wavelet.dot",
    out = "wavelet.png",
)

tex_to_pdf(
    name = "fm-index",
    src = "fm-index.tex",
    data = [":wavelet.png"],
    pdf = "fm-index.pdf",
)
