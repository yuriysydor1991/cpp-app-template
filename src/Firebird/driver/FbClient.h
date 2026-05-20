#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_FBCLIENT_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_FBCLIENT_CLASS_H

#include <memory>
#include <string>

#include "src/Firebird/IFbClient.h"

namespace firebirdi::driver
{

/**
 * @brief Factory that creates the default, fbclient backed IFbClient
 * implementation.
 *
 * It is declared here (and not as a constructor call inside the Firebird class)
 * on purpose: this is the single link-time seam that pulls in the native
 * Firebird client library. The Firebird component tests provide their own
 * definition of this function so that the orchestration logic may be built and
 * run without the fbclient library at all.
 *
 * @return Returns a freshly created, fbclient backed IFbClient instance.
 */
std::shared_ptr<IFbClient> create_fb_client();

/**
 * @brief The default IFbClient implementation backed by the native Firebird
 * client library (fbclient / ibase.h).
 *
 * The whole implementation, together with the ibase.h inclusion, lives in the
 * FbClient.cpp translation unit so that the native library stays isolated from
 * the rest of the project.
 */
class FbClient : public IFbClient
{
 public:
  ~FbClient() override;
  FbClient();

  bool attach(const std::string& database, const std::string& user,
              const std::string& password) override;
  void detach() override;
  bool attached() const override;
  std::string query_scalar(const std::string& query) override;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl;
};

}  // namespace firebirdi::driver

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_FBCLIENT_CLASS_H
