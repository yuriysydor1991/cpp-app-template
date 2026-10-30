#include "SherpaONNXLibraryMock.h"

#include <sherpa-onnx/c-api/cxx-api.h>

#include <cstdint>
#include <vector>

namespace sherpaonnx
{

SherpaONNXLibraryMock::SherpaONNXLibraryMock()
{
  using ::testing::_;
  using ::testing::Return;

  ON_CALL(*this, Create(_)).WillByDefault(Return(true));

  instance = this;
}

SherpaONNXLibraryMock::~SherpaONNXLibraryMock() { instance = nullptr; }

}  // namespace sherpaonnx

namespace sherpa_onnx::cxx
{

using sherpaonnx::SherpaONNXLibraryMock;

// The handles are never dereferenced, so any address of no engine will do.

OfflineStream::OfflineStream(const SherpaOnnxOfflineStream* const p)
    : MoveOnly{p}
{
}

void OfflineStream::AcceptWaveform(const std::int32_t sample_rate,
                                   const float* const samples,
                                   const std::int32_t n) const
{
  SherpaONNXLibraryMock::instance->AcceptWaveform(
      sample_rate, std::vector<float>(samples, samples + n));
}

void OfflineStream::Destroy(
    [[maybe_unused]] const SherpaOnnxOfflineStream* const p) const
{
}

OfflineRecognizer::OfflineRecognizer(const SherpaOnnxOfflineRecognizer* const p)
    : MoveOnly{p}
{
}

OfflineRecognizer OfflineRecognizer::Create(
    const OfflineRecognizerConfig& config)
{
  return OfflineRecognizer{
      SherpaONNXLibraryMock::instance->Create(config)
          ? reinterpret_cast<const SherpaOnnxOfflineRecognizer*>(
                SherpaONNXLibraryMock::instance)
          : nullptr};
}

void OfflineRecognizer::Destroy(
    [[maybe_unused]] const SherpaOnnxOfflineRecognizer* const p) const
{
  SherpaONNXLibraryMock::instance->Destroy();
}

OfflineStream OfflineRecognizer::CreateStream() const
{
  return OfflineStream{reinterpret_cast<const SherpaOnnxOfflineStream*>(p_)};
}

void OfflineRecognizer::Decode(
    [[maybe_unused]] const OfflineStream* const s) const
{
  SherpaONNXLibraryMock::instance->Decode();
}

OfflineRecognizerResult OfflineRecognizer::GetResult(
    [[maybe_unused]] const OfflineStream* const s) const
{
  return SherpaONNXLibraryMock::instance->GetResult();
}

}  // namespace sherpa_onnx::cxx
