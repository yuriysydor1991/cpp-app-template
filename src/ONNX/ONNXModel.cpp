#include "src/ONNX/ONNXModel.h"

#include <onnxruntime_cxx_api.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <opencv2/core.hpp>
#include <string>
#include <vector>

#include "src/log/log.h"

namespace onnxi
{

bool ONNXModel::load(const std::string& path)
{
  mshape.clear();

  try {
    msession.emplace(menv, std::filesystem::path{path}.c_str(),
                     Ort::SessionOptions{});

    Ort::AllocatorWithDefaultOptions allocator;
    const auto input = msession->GetInputTypeInfo(0);

    minput = msession->GetInputNameAllocated(0, allocator).get();
    mshape = input.GetTensorTypeAndShapeInfo().GetShape();
    moutputs.clear();

    for (std::size_t index = 0; index < msession->GetOutputCount(); ++index) {
      moutputs.emplace_back(
          msession->GetOutputNameAllocated(index, allocator).get());
    }
  }
  catch (const Ort::Exception& error) {
    msession.reset();
    mshape.clear();
    LOGE("Fail to load the " << path << " ONNX model: " << error.what());
    return false;
  }

  moutputNames.resize(moutputs.size());
  std::transform(moutputs.cbegin(), moutputs.cend(), moutputNames.begin(),
                 [](const std::string& name) { return name.c_str(); });

  return true;
}

const ONNXModel::shape& ONNXModel::input_shape() const { return mshape; }

ONNXModel::outputs ONNXModel::run(cv::Mat& input)
{
  if (!msession.has_value()) {
    LOGE("No ONNX model is loaded");
    return {};
  }

  const shape dimensions(input.size.p, input.size.p + input.dims);
  const auto memory =
      Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
  const char* inputName = minput.c_str();

  try {
    auto tensor = input.depth() == CV_32S
                      ? Ort::Value::CreateTensor<int32_t>(
                            memory, input.ptr<int32_t>(), input.total(),
                            dimensions.data(), dimensions.size())
                      : Ort::Value::CreateTensor<float>(
                            memory, input.ptr<float>(), input.total(),
                            dimensions.data(), dimensions.size());

    return msession->Run(Ort::RunOptions{nullptr}, &inputName, &tensor, 1U,
                         moutputNames.data(), moutputNames.size());
  }
  catch (const Ort::Exception& error) {
    LOGE("Fail to run the ONNX model: " << error.what());
    return {};
  }
}

cv::Mat ONNXModel::planar(const cv::Mat& image)
{
  const int dimensions[] = {1, image.channels(), image.rows, image.cols};
  cv::Mat tensor(4, dimensions, CV_32F);
  std::vector<cv::Mat> planes;

  planes.reserve(static_cast<std::size_t>(image.channels()));

  for (int channel = 0; channel < image.channels(); ++channel) {
    planes.emplace_back(image.rows, image.cols, CV_32F,
                        tensor.ptr<float>(0, channel));
  }

  cv::split(image, planes);

  return tensor;
}

}  // namespace onnxi
