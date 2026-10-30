#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXLIBRARYMOCK_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXLIBRARYMOCK_CLASS_H

#include <gmock/gmock.h>
#include <sherpa-onnx/c-api/cxx-api.h>

#include <cstdint>
#include <vector>

namespace sherpaonnx
{

/**
 * @brief The mock of the sherpa-onnx C++ API calls the SherpaONNXController
 * makes. The SherpaONNXLibraryMock.cpp file defines the
 * sherpa_onnx::cxx::OfflineRecognizer and the sherpa_onnx::cxx::OfflineStream
 * methods in place of the library, which the unit test links not, and
 * forwards them to the SherpaONNXLibraryMock::instance one, so a test
 * controls the engine.
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
  MOCK_METHOD(bool, Create,
              (const sherpa_onnx::cxx::OfflineRecognizerConfig& config));
  MOCK_METHOD(void, Destroy, ());
  MOCK_METHOD(void, AcceptWaveform,
              (std::int32_t sampleRate, const std::vector<float>& samples));
  MOCK_METHOD(void, Decode, ());
  MOCK_METHOD(sherpa_onnx::cxx::OfflineRecognizerResult, GetResult, ());

  inline static SherpaONNXLibraryMock* instance{nullptr};
};

}  // namespace sherpaonnx

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_SHERPAONNXLIBRARYMOCK_CLASS_H
