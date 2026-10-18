#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXLIBRARYMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXLIBRARYMOCK_CLASS_H

#include <gmock/gmock.h>
#include <sherpa-onnx/c-api/cxx-api.h>

#include <cstdint>
#include <string>

namespace sherpaonnx
{

/**
 * @brief The mock of the sherpa-onnx C++ API calls the SherpaONNXController
 * makes. The SherpaONNXLibraryMock.cpp file defines the
 * sherpa_onnx::cxx::OfflineTts methods in place of the library, which the
 * unit test links not, and forwards them to the
 * SherpaONNXLibraryMock::instance one, so a test controls the engine.
 */
class SherpaONNXLibraryMock
{
 public:
  /// @brief Makes the created mock the forwarded one, every call of it a
  /// successful one by default.
  SherpaONNXLibraryMock();
  virtual ~SherpaONNXLibraryMock();
  SherpaONNXLibraryMock(const SherpaONNXLibraryMock&) = delete;
  SherpaONNXLibraryMock& operator=(const SherpaONNXLibraryMock&) = delete;

  /// @brief Tells if the creation of the engine of the given configuration
  /// succeeds.
  MOCK_METHOD(bool, Create, (const sherpa_onnx::cxx::OfflineTtsConfig& config));
  MOCK_METHOD(void, Destroy, ());
  MOCK_METHOD(std::int32_t, NumSpeakers, ());
  MOCK_METHOD(sherpa_onnx::cxx::GeneratedAudio, Generate,
              (const std::string& text, std::int32_t sid, float speed));

  /// @brief The sample rate and the speakers count the mock reports by
  /// default.
  inline static constexpr const int SAMPLE_RATE = 24000;
  inline static constexpr const int SPEAKERS = 10;

  inline static SherpaONNXLibraryMock* instance{nullptr};
};

}  // namespace sherpaonnx

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXLIBRARYMOCK_CLASS_H
