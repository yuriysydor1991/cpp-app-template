#include "src/Firebird/driver/FbClient.h"

#include <ibase.h>

#include <memory>
#include <string>
#include <vector>

#include "src/Firebird/driver/FbDpbBuilder.h"
#include "src/Firebird/driver/FbHandles.h"
#include "src/log/log.h"

namespace firebirdi::driver
{

std::shared_ptr<IFbClient> create_fb_client()
{
  return std::make_shared<FbClient>();
}

namespace
{

/// @brief Returns true and logs the Firebird error if the status vector holds
/// one.
bool has_error(const ISC_STATUS_ARRAY& status)
{
  if (status[0] == 1 && status[1] != 0) {
    char message[512];
    const ISC_STATUS* sptr = status;

    if (fb_interpret(message, sizeof(message), &sptr)) {
      LOGE("Firebird error: " << message);
    }

    return true;
  }

  return false;
}

}  // namespace

FbClient::FbClient() : handles{std::make_unique<FbHandles>()} {}

// Calls the non-virtual do_detach(): a virtual call during destruction would
// bypass the dynamic dispatch anyway.
FbClient::~FbClient() { do_detach(); }

bool FbClient::attach(const std::string& database, const std::string& user,
                      const std::string& password)
{
  // Build the database parameter buffer (DPB) with the credentials.
  FbDpbBuilder dpb{isc_dpb_version1};

  if (!dpb.append(isc_dpb_user_name, user) ||
      !dpb.append(isc_dpb_password, password)) {
    LOGE("The Firebird user name and password may not exceed "
         << FbDpbBuilder::max_value_length << " bytes");
    return false;
  }

  isc_attach_database(handles->status, static_cast<short>(database.size()),
                      database.c_str(), &handles->db,
                      static_cast<short>(dpb.data().size()), dpb.data().data());

  if (has_error(handles->status)) {
    LOGE("Failure to attach to the Firebird database: " << database);
    handles->db = 0;
    return false;
  }

  return attached();
}

void FbClient::detach() { do_detach(); }

bool FbClient::attached() const { return handles->db != 0; }

void FbClient::do_detach()
{
  if (handles->db == 0) {
    return;
  }

  isc_detach_database(handles->status, &handles->db);

  handles->db = 0;
}

std::string FbClient::query_scalar(const std::string& query)
{
  if (!attached()) {
    LOGE("Not attached to any Firebird database");
    return {};
  }

  isc_tr_handle trans{0};
  isc_stmt_handle stmt{0};
  std::string result;

  isc_start_transaction(handles->status, &trans, 1, &handles->db, 0, nullptr);
  if (has_error(handles->status)) {
    LOGE("Failure to start the Firebird transaction");
    return {};
  }

  // Output descriptor for a single column: the XSQLDA embeds exactly one
  // XSQLVAR, so XSQLDA_LENGTH(1) is its own size and no heap block is needed.
  XSQLDA out_sqlda{};
  out_sqlda.version = SQLDA_VERSION1;
  out_sqlda.sqln = 1;

  isc_dsql_allocate_statement(handles->status, &handles->db, &stmt);

  isc_dsql_prepare(handles->status, &trans, &stmt, 0, query.c_str(),
                   SQL_DIALECT_V6, &out_sqlda);
  if (has_error(handles->status) || out_sqlda.sqld < 1) {
    LOGE("Failure to prepare the Firebird query: " << query);
    isc_dsql_free_statement(handles->status, &stmt, DSQL_drop);
    isc_rollback_transaction(handles->status, &trans);
    return {};
  }

  // Bind the single (VARCHAR) output column to a local buffer.
  XSQLVAR& var = out_sqlda.sqlvar[0];
  const size_t buffer_len = static_cast<size_t>(var.sqllen) + sizeof(short) + 1;
  std::vector<char> buffer(buffer_len, 0);
  short null_flag = 0;

  var.sqldata = buffer.data();
  var.sqltype = SQL_VARYING + 1;  // +1 -> provide a NULL indicator
  var.sqlind = &null_flag;

  isc_dsql_execute(handles->status, &trans, &stmt, SQL_DIALECT_V6, nullptr);
  if (has_error(handles->status)) {
    LOGE("Failure to execute the Firebird query: " << query);
  } else if (isc_dsql_fetch(handles->status, &stmt, SQL_DIALECT_V6,
                            &out_sqlda) == 0 &&
             null_flag == 0) {
    // SQL_VARYING data is a 2-byte length prefix followed by the characters.
    const PARAMVARY* vary = reinterpret_cast<const PARAMVARY*>(buffer.data());
    result.assign(reinterpret_cast<const char*>(vary->vary_string),
                  vary->vary_length);
  }

  isc_dsql_free_statement(handles->status, &stmt, DSQL_drop);
  isc_commit_transaction(handles->status, &trans);

  return result;
}

}  // namespace firebirdi::driver
