#pragma once

#include <colmap/controllers/automatic_reconstruction.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>

#include <thread>
#include <unordered_map>

#include "reconstruct.pb.h"
#include "tools.grpc.pb.h"

class ReconstructServiceImpl : public PointCloudTools::PhotogrammetryServices::Service {
 public:
  ReconstructServiceImpl() = default;
  virtual ~ReconstructServiceImpl() = default;

  ::grpc::Status reconstructFromImages(
      ::grpc::ServerContext* context, const ::PointCloudTools::ReconstructImageRequest* request,
      ::PointCloudTools::ReconstructImageResponse* response) override;

  ::grpc::Status getJobStatus(::grpc::ServerContext* context,
                              const ::google::protobuf::Empty* request,
                              ::PointCloudTools::JobStatusResponse* response) override;

  PointCloudTools::JobStatusResponse& get_job_status_map() { return jobs_status_; }

 protected:
  std::unordered_map<std::string, std::thread*> jobs_;
  PointCloudTools::JobStatusResponse jobs_status_;  // direct gRPC response
  // std::vector<std::thread> jobs_;
};