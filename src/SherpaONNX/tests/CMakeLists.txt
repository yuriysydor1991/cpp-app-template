cmake_minimum_required(VERSION 3.13)

if (NOT (ENABLE_UNIT_TESTS OR ENABLE_COMPONENT_TESTS))
  return()
endif()

# The log mock of the whole project is kept under the app tests, so it is taken
# from there rather than duplicated.
set(SHERPAONNX_APP_MOCKS_ROOT "${PROJECT_SOURCE_DIR}/src/app/tests/mocks")
set(SHERPAONNX_MOCKS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/mocks")

# The downloaded model carries an English speech sample, while the Ukrainian
# one of the sherpa-onnx asr-models release gets downloaded once, so the tests
# have something to recognize. The test cases needing them skip themselves
# while they are not available, with no network for example.
set(SHERPAONNX_TEST_SPEECH "${PROJECT_STT_MODEL}/test_wavs/en.wav")
set(SHERPAONNX_TEST_UK_SPEECH "${CMAKE_CURRENT_BINARY_DIR}/uk.wav")

if (NOT EXISTS "${SHERPAONNX_TEST_UK_SPEECH}")
  file(
    DOWNLOAD "https://github.com/k2-fsa/sherpa-onnx/releases/download/asr-models/uk.wav"
    "${SHERPAONNX_TEST_UK_SPEECH}"
    EXPECTED_HASH SHA256=e9c007687c3fb78fbd5382ab654093cb3c90989472607324faf487ae01de198f
    TLS_VERIFY ON
    STATUS downloadStatus
  )

  list(GET downloadStatus 0 downloadCode)

  if (NOT downloadCode EQUAL 0)
    file(REMOVE "${SHERPAONNX_TEST_UK_SPEECH}")
    message(WARNING "Fail to download the uk.wav sherpa-onnx test speech: ${downloadStatus}")
  endif()
endif()

add_subdirectory(unit)
add_subdirectory(component)
