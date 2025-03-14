#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H

namespace templateQt6app
{

/**
 * @brief The Qt initialization and starter class.
 */
class Qt6Initer
{
 public:
  virtual ~Qt6Initer() = default;
  Qt6Initer() = default;

  /**
   * @brief Starts the Qt6 available application.
   *
   * @param argc The arguments count passed by the OS.
   * @param argv The arguments array passed by the OS.
   *
   * @return Should return the application return status.
   * Zero at success and non-zero value otherwise.
   */
  virtual int run(int& argc, char**& argv);

 protected:
  inline static const char* const main_qml_path = "qrc:/ui/qml/main.qml";
};

}  // namespace templateQt6app

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_QT6INITER_CLASS_H
