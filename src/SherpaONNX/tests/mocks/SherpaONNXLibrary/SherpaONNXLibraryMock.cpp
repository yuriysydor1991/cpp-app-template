#include "SherpaONNXLibraryMock.h"

#include <sherpa-onnx/c-api/cxx-api.h>

#include <cstdint>
#include <string>

namespace sherpaonnx
{

SherpaONNXLibraryMock::SherpaONNXLibraryMock()
{
  using ::testing::_;
  using ::testing::Return;

  ON_CALL(*this, Create(_)).WillByDefault(Return(true));
  ON_CALL(*this, NumSpeakers()).WillByDefault(Return(SPEAKERS));
  ON_CALL(*this, Generate(_, _, _))
      .WillByDefault(Return(sherpa_onnx::cxx::GeneratedAudio{{}, SAMPLE_RATE}));

  instance = this;
}

SherpaONNXLibraryMock::~SherpaONNXLibraryMock() { instance = nullptr; }

}  // namespace sherpaonnx

namespace sherpa_onnx::cxx
{

using sherpaonnx::SherpaONNXLibraryMock;

OfflineTts::OfflineTts(const SherpaOnnxOfflineTts* const p) : MoveOnly{p} {}

OfflineTts OfflineTts::Create(const OfflineTtsConfig& config)
{
  // The handle is never dereferenced, so any address of no engine will do.
  return OfflineTts{SherpaONNXLibraryMock::instance->Create(config)
                        ? reinterpret_cast<const SherpaOnnxOfflineTts*>(
                              SherpaONNXLibraryMock::instance)
                        : nullptr};
}

void OfflineTts::Destroy(
    [[maybe_unused]] const SherpaOnnxOfflineTts* const p) const
{
  SherpaONNXLibraryMock::instance->Destroy();
}

std::int32_t OfflineTts::NumSpeakers() const
{
  return SherpaONNXLibraryMock::instance->NumSpeakers();
}

GeneratedAudio OfflineTts::Generate(
    const std::string& text, const std::int32_t sid, const float speed,
    [[maybe_unused]] const OfflineTtsCallback callback,
    [[maybe_unused]] void* const arg) const
{
  return SherpaONNXLibraryMock::instance->Generate(text, sid, speed);
}

}  // namespace sherpa_onnx::cxx
