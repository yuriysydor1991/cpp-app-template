#include "src/Firebird/driver/FbClient.h"

#include <ibase.h>

#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "src/log/log.h"

namespace firebirdi::driver
{

std::shared_ptr<IFbClient> create_fb_client()
{
  return std::make_shared<FbClient>();
}

/**
 * @brief Holds the native Firebird handles so that ibase.h does not leak into
 * the FbClient.h header.
 */
struct FbClient::Impl
{
  isc_db_handle db{0};
  ISC_STATUS_ARRAY status{};
};

namespace
{

/// @brief Returns true and logs the Firebird error if the status vector holds
/// one.
bool has_error(const ISC_STATUS_ARRAY& status)
{
  if (status[0] == 1 && status[1] != 0) {
    char message[512];
    const ISC_STATUS* sptr = status;

    if (fb_interpret(message, sizeof(message),
                     const_cast<const ISC_STATUS**>(&sptr))) {
      LOGE("Firebird error: " << message);
    }

    return true;
  }

  return false;
}

}  // namespace

FbClient::FbClient() : impl{std::make_unique<Impl>()} {}

FbClient::~FbClient() { detach(); }

bool FbClient::attach(const std::string& database, const std::string& user,
                      const std::string& password)
{
  // Build the database parameter buffer (DPB) with the credentials.
  std::vector<char> dpb;
  dpb.push_back(isc_dpb_version1);

  const auto append_dpb = [&dpb](char tag, const std::string& value) {
    if (value.empty()) {
      return;
    }
    dpb.push_back(tag);
    dpb.push_back(static_cast<char>(value.size()));
    dpb.insert(dpb.end(), value.begin(), value.end());
  };

  append_dpb(isc_dpb_user_name, user);
  append_dpb(isc_dpb_password, password);

  isc_attach_database(impl->status, static_cast<short>(database.size()),
                      database.c_str(), &impl->db,
                      static_cast<short>(dpb.size()), dpb.data());

  if (has_error(impl->status)) {
    LOGE("Failure to attach to the Firebird database: " << database);
    impl->db = 0;
    return false;
  }

  return attached();
}

void FbClient::detach()
{
  if (!attached()) {
    return;
  }

  isc_detach_database(impl->status, &impl->db);

  impl->db = 0;
}

bool FbClient::attached() const { return impl->db != 0; }

std::string FbClient::query_scalar(const std::string& query)
{
  if (!attached()) {
    LOGE("Not attached to any Firebird database");
    return {};
  }

  isc_tr_handle trans{0};
  isc_stmt_handle stmt{0};
  std::string result;

  isc_start_transaction(impl->status, &trans, 1, &impl->db, 0, nullptr);
  if (has_error(impl->status)) {
    LOGE("Failure to start the Firebird transaction");
    return {};
  }

  // Output descriptor for a single column.
  XSQLDA* out_sqlda = reinterpret_cast<XSQLDA*>(std::malloc(XSQLDA_LENGTH(1)));
  std::memset(out_sqlda, 0, XSQLDA_LENGTH(1));
  out_sqlda->version = SQLDA_VERSION1;
  out_sqlda->sqln = 1;

  isc_dsql_allocate_statement(impl->status, &impl->db, &stmt);

  isc_dsql_prepare(impl->status, &trans, &stmt, 0, query.c_str(), SQL_DIALECT_V6,
                   out_sqlda);
  if (has_error(impl->status) || out_sqlda->sqld < 1) {
    LOGE("Failure to prepare the Firebird query: " << query);
    isc_dsql_free_statement(impl->status, &stmt, DSQL_drop);
    isc_rollback_transaction(impl->status, &trans);
    std::free(out_sqlda);
    return {};
  }

  // Bind the single (VARCHAR) output column to a local buffer.
  XSQLVAR& var = out_sqlda->sqlvar[0];
  const short buffer_len = static_cast<short>(var.sqllen + sizeof(short) + 1);
  std::vector<char> buffer(static_cast<size_t>(buffer_len), 0);
  short null_flag = 0;

  var.sqldata = buffer.data();
  var.sqltype = SQL_VARYING + 1;  // +1 -> provide a NULL indicator
  var.sqlind = &null_flag;

  isc_dsql_execute(impl->status, &trans, &stmt, SQL_DIALECT_V6, nullptr);
  if (has_error(impl->status)) {
    LOGE("Failure to execute the Firebird query: " << query);
  } else if (isc_dsql_fetch(impl->status, &stmt, SQL_DIALECT_V6, out_sqlda) ==
                 0 &&
             null_flag == 0) {
    // SQL_VARYING data is a 2-byte length prefix followed by the characters.
    const PARAMVARY* vary = reinterpret_cast<const PARAMVARY*>(buffer.data());
    result.assign(reinterpret_cast<const char*>(vary->vary_string),
                  vary->vary_length);
  }

  isc_dsql_free_statement(impl->status, &stmt, DSQL_drop);
  isc_commit_transaction(impl->status, &trans);
  std::free(out_sqlda);

  return result;
}

}  // namespace firebirdi::driver
