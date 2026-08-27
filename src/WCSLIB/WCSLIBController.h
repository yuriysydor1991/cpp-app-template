#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WCSLIBCONTROLLER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WCSLIBCONTROLLER_CLASS_H

#include <memory>
#include <string>
#include <vector>

#include "src/CFITSIO/CFITSIOContext.h"

/// @brief The WCSLIB coordinate representation. Only the pointers to it are
/// held here, so the WCSLIB headers stay inside the implementation.
struct wcsprm;

/**
 * @brief The WCSLIB adaptor subsystem namespace.
 */
namespace wcslibi
{

/**
 * @brief The WCSLIB (the FITS World Coordinate System) converter class.
 *
 * A single instance holds the coordinate representations parsed out of a
 * single FITS header, which it takes from the very same CFITSIOContext the
 * CFITSIO component reads that header into. Every call reports it's outcome
 * through the return value and leaves the WCSLIB status code of the performed
 * call in the last_status accessor, so nothing throws.
 */
class WCSLIBController
{
 public:
  /// @brief A single coordinate, one value per axis: the pixel ones counted
  /// from 1.0 as the FITS standard does and the world ones in the axis units,
  /// degrees for the celestial axes.
  using coordinates = std::vector<double>;

  /// @brief The context both of the custom components operate by.
  using context = cfitsioi::CFITSIOContextPtr;

  using WCSLIBControllerPtr = std::shared_ptr<WCSLIBController>;

  virtual ~WCSLIBController();
  WCSLIBController() = default;
  WCSLIBController(const WCSLIBController&) = delete;
  WCSLIBController(WCSLIBController&&) = delete;

  /**
   * @brief Parses the coordinate representations out of the FITS header the
   * context carries and selects the primary one.
   *
   * @param ctx The context carrying the header, as the
   * cfitsioi::CFITSIOController::read_header call fills it out of a file.
   *
   * @return Returns true when at least one representation has been parsed.
   */
  virtual bool parse(const context& ctx);

  /**
   * @brief Selects the parsed representation to convert with.
   *
   * @param index The zero index selects the primary representation and the
   * rest select the alternate ones, in the order the header declares them.
   *
   * @return Returns true when the representation has been selected and set up.
   */
  virtual bool select(const int index);

  /// @brief Releases the parsed representations. Not named reset, so no
  /// call of it reads like the reset of a smart pointer holding the
  /// controller.
  virtual void release();

  virtual bool is_ready() const;

  /// @brief Gives the count of the representations parsed out of the header.
  virtual int get_representations_count() const;

  /// @brief Gives the axes count of the selected representation, zero while
  /// none is selected.
  virtual int get_axes_count() const;

  /**
   * @brief Gives the CTYPEi keyvalue of the given axis, "RA---TAN" for
   * example.
   *
   * @param axis The zero based axis index.
   *
   * @return Returns the axis type, empty in case of any error.
   */
  virtual std::string get_axis_type(const int axis) const;

  /**
   * @brief Converts the given pixel coordinate into the world one.
   *
   * @param pixel One value per axis of the selected representation.
   *
   * @return Returns the world coordinate, empty in case of any error.
   */
  virtual coordinates to_world(const coordinates& pixel);

  /**
   * @brief Converts the given world coordinate into the pixel one.
   *
   * @param world One value per axis of the selected representation.
   *
   * @return Returns the pixel coordinate, empty in case of any error.
   */
  virtual coordinates to_pixel(const coordinates& world);

  /// @brief Gives the count of the header keyrecords the last parse call has
  /// rejected as the malformed WCS ones.
  virtual int get_rejected_count() const;

  /// @brief Gives the WCSLIB status code of the last performed call, where
  /// the zero one reports a success.
  virtual int last_status() const;

  /// @brief Gives the WCSLIB description of the last_status value, empty
  /// while no call has been performed yet.
  virtual std::string last_error() const;

  static WCSLIBControllerPtr create();

 private:
  /**
   * @brief Drops the status of the previous call and tells whether the given
   * coordinate fits the selected representation.
   *
   * @param given The coordinate the conversion has been asked for.
   */
  bool prepare(const coordinates& given);

  /**
   * @brief Logs the WCSLIB error of the just performed call, if any, and
   * keeps it's description for the last_error accessor.
   *
   * @param action The description of the performed call for the log message.
   * @param messages The status messages table of the performed call, since
   * every WCSLIB routine group carries an own one.
   * @param messagesCount The entries count of that table.
   *
   * @return Returns true when the call left no error behind.
   */
  bool succeeded(const std::string& action, const char* const* messages,
                 const int messagesCount);

  /// @brief A FITS header keyrecord is exactly that many characters long and
  /// carries no terminator of it's own.
  inline static constexpr const std::string::size_type KEYRECORD_LENGTH = 80U;

  std::string error;

  /// @brief The representations array the parse call has allocated and the
  /// one of it the select call has picked.
  struct wcsprm* parsed{nullptr};
  struct wcsprm* selected{nullptr};

  int count{0};
  int rejected{0};
  int status{0};
};

using WCSLIBControllerPtr = WCSLIBController::WCSLIBControllerPtr;

}  // namespace wcslibi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WCSLIBCONTROLLER_CLASS_H
