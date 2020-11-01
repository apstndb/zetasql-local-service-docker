//
// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <csignal>
#include <cstdlib>
#include <errno.h>
#include <fcntl.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_posix.h>
#include <memory>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "zetasql/local_service/local_service_grpc.h"

namespace {
static grpc::Server *GetServer() {
  static grpc::Server *server = []() {
    // The service must remain for the lifetime of the server.
    static zetasql::local_service::ZetaSqlLocalServiceGrpcImpl *service =
        new zetasql::local_service::ZetaSqlLocalServiceGrpcImpl();
    grpc::ServerBuilder builder;
    builder.RegisterService(service);
    builder.AddListeningPort("0.0.0.0:50051",
                             grpc::InsecureServerCredentials());

    return builder.BuildAndStart().release();
  }();
  return server;
}

} // namespace

extern "C" {
static void signal_handler(int signal) { GetServer()->Shutdown(); }
}

int main() {
  auto server = GetServer();

  std::signal(SIGTERM, signal_handler);
  std::signal(SIGINT, signal_handler);

  server->Wait();
}