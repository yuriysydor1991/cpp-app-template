#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_UTTERANCEDETECTOR_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_UTTERANCEDETECTOR_CLASS_H

#include <cstddef>
#include <vector>

namespace whisperi
{

/**
 * @brief Cuts the continuously captured audio into the utterances at the
 * pauses of the speech, so every utterance gets transcribed on it's own.
 *
 * The audio is examined by the frames of the FRAME_MS length, and a frame
 * louder than the SPEECH_RATIO times the noise floor is a speech one. The
 * first frames measure the floor, which follows the loudness of the
 * surroundings afterwards: it falls fast and rises slow, so the silence lowers
 * it right away, while it takes a lasting noise and not a single sentence to
 * raise it.
 */
class UtteranceDetector
{
 public:
  using samples = std::vector<float>;

  /**
   * @brief An UtteranceDetector constructor.
   *
   * @param sampleRate The samples count per second of the examined audio.
   */
  explicit UtteranceDetector(std::size_t sampleRate);

  /**
   * @brief Appends the given samples to the ones awaiting the examination
   * and looks for the end of an utterance among them.
   *
   * @param captured The mono samples captured next.
   *
   * @return Returns the first utterance completed by a pause or by the
   * maximum length together with the lead audio preceding it, or the empty
   * one while none is complete. The samples behind the returned utterance
   * await the next call.
   */
  samples feed(const samples& captured);

 private:
  /// @brief Tells whether the frame starting at the given sample is a speech
  /// one and lets the noise floor follow it's loudness.
  bool is_speech(const float* frame);

  /// @brief Adds the frame starting at the given sample to the utterance
  /// being collected and gives the utterance away once it is complete.
  samples collect(const float* frame);

  inline static constexpr const std::size_t FRAME_MS = 30U;

  /// @brief The 300 ms preceding the speech come with it, so it's first word
  /// is not cut. As much audio measures the noise floor at the start.
  inline static constexpr const std::size_t LEAD_FRAMES = 10U;

  /// @brief The 750 ms of the silence end an utterance.
  inline static constexpr const std::size_t PAUSE_FRAMES = 25U;

  /// @brief An utterance of less than 240 ms of the speech is a click or a
  /// knock, so it gets dropped.
  inline static constexpr const std::size_t MIN_SPEECH_FRAMES = 8U;

  /// @brief A speech of no pause gets cut into the 15 s utterances.
  inline static constexpr const std::size_t MAX_FRAMES = 500U;

  inline static constexpr const float SPEECH_RATIO = 3.0F;

  /// @brief The frames quieter than this level of the full scale are no
  /// speech in any surroundings, the digital silence included.
  inline static constexpr const float MIN_SPEECH_LEVEL = 0.002F;

  /// @brief The weights the noise floor follows a quieter and a louder frame
  /// with.
  inline static constexpr const float FLOOR_FALL = 0.1F;
  inline static constexpr const float FLOOR_RISE = 0.0005F;

  const std::size_t frameSamples;
  samples pending;
  samples utterance;
  float noiseFloor{0.0F};
  std::size_t examinedFrames{0U};
  std::size_t speechFrames{0U};
  std::size_t silentFrames{0U};
};

}  // namespace whisperi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_UTTERANCEDETECTOR_CLASS_H
