#include "src/app/signals-handlers/handlers/posix/PosixSignalsHandler.h"

namespace app
{

// The out of line destructor pins the class vtable to the current translation
// unit instead of emitting a copy of it into every including one.
PosixSignalsHandler::~PosixSignalsHandler() = default;

}  // namespace app
