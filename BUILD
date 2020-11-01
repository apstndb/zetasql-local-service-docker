load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@io_bazel_rules_docker//cc:image.bzl", "cc_image")

cc_binary(
    name = "local_service_entrypoint",
    srcs = ["local_service_entrypoint.cc"],
    copts = [
        "-Wno-char-subscripts",
        "-Wno-return-type",
        "-Wno-sign-compare",
        "-Wno-switch",
        "-Wno-unused-but-set-parameter",
        "-Wno-unused-function",
        "-Wnonnull-compare",
    ],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_google_zetasql//zetasql/local_service:local_service_grpc",
    ],
)

cc_image(
    name = "local_service_entrypoint_image",
    base = "@cc_image_base//image",
    binary = ":local_service_entrypoint",
)
