workspace(name = "com_github_apstndb_zetasql_local_service_docker")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_zetasql",
    patches = ["//:zetasql.patch"],
    strip_prefix = "zetasql-2020.10.1",
    urls = [
        "https://github.com/google/zetasql/archive/2020.10.1.tar.gz",
    ],
)

# Bazel doesn't support recursively loading dependencies.
# The recommended pattern is for a repo to provide a 'my_repo_deps()' method
# which will download all dependencies. Thus, a _direct dependency of 'my_repo'
# can ask it to load it dependencies. However, if 'my_repo' has dependencies
# which themselves have dependencies, and provide a 'child_repo_deps()',
# there is no way to compose a workspace such that 'my_repo_deps' calls
# 'child_repo_deps' (since this would represent a serialization of
# load-then-statement, which is forbidden).  So, we take the tactic of providing
# a serialized sequence of numbered steps that must be invoked in series to
# load all dependencies.  Copy the following code exactly into your WORKSPACE
# to fully download all dependencies. The exactly nature of what happens at
# each step may change over time (and additional steps may be added in the
# future).

# such that 'my_repo_deps'
load("@com_google_zetasql//bazel:zetasql_deps_step_1.bzl", "zetasql_deps_step_1")

zetasql_deps_step_1()

load("@com_google_zetasql//bazel:zetasql_deps_step_2.bzl", "zetasql_deps_step_2")

zetasql_deps_step_2()

load("@com_google_zetasql//bazel:zetasql_deps_step_3.bzl", "zetasql_deps_step_3")

zetasql_deps_step_3()

load("@com_google_zetasql//bazel:zetasql_deps_step_4.bzl", "zetasql_deps_step_4")

zetasql_deps_step_4()

# Download the rules_docker repository at release v0.14.4
http_archive(
    name = "io_bazel_rules_docker",
    sha256 = "4521794f0fba2e20f3bf15846ab5e01d5332e587e9ce81629c7f96c793bb7036",
    strip_prefix = "rules_docker-0.14.4",
    urls = ["https://github.com/bazelbuild/rules_docker/releases/download/v0.14.4/rules_docker-v0.14.4.tar.gz"],
)

load(
    "@io_bazel_rules_docker//repositories:repositories.bzl",
    container_repositories = "repositories",
)

container_repositories()

load("@io_bazel_rules_docker//repositories:deps.bzl", container_deps = "deps")

container_deps()

load("@io_bazel_rules_docker//repositories:pip_repositories.bzl", "pip_deps")

pip_deps()

load(
    "@io_bazel_rules_docker//container:container.bzl",
    "container_pull",
)
