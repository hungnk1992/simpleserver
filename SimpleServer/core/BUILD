load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "lib",
    srcs = ["Server.cpp"],
    hdrs = ["Server.h"],
    visibility = ["//SimpleServer:__pkg__"],
)

cc_binary(
    name = "client",
    srcs = ["Client.cpp"],
)