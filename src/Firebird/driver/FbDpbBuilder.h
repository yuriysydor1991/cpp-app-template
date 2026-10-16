#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FBDPBBUILDER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FBDPBBUILDER_CLASS_H

#include <cstddef>
#include <string>
#include <vector>

namespace firebirdi::driver
{

/**
 * @brief Builds the Firebird database parameter buffer (DPB) of the
 * isc_attach_database call.
 *
 * A version 1 DPB stores every value length in a single byte, so the builder
 * refuses the values longer than 255 bytes instead of silently corrupting
 * them.
 */
class FbDpbBuilder
{
 public:
  virtual ~FbDpbBuilder() = default;

  /**
   * @param version The DPB version byte the buffer starts with, e.g. the
   * isc_dpb_version1.
   */
  explicit FbDpbBuilder(char version);

  /**
   * @brief Appends the tag with its value to the buffer. An empty value is
   * skipped.
   *
   * @return Returns false and leaves the buffer unchanged if the value does
   * not fit the single byte length, true otherwise.
   */
  virtual bool append(char tag, const std::string& value);

  /// @brief The DPB built so far.
  const std::vector<char>& data() const;

  /// @brief The longest value a single byte length may describe.
  static constexpr std::size_t max_value_length = 255U;

 private:
  std::vector<char> dpb;
};

}  // namespace firebirdi::driver

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FBDPBBUILDER_CLASS_H
