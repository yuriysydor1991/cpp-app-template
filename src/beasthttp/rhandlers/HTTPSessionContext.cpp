#include "src/beasthttp/rhandlers/HTTPSessionContext.h"

#include <memory>

#include "src/beasthttp/beast-includes.h"

namespace beasthttp::rhandlers
{

HTTPSessionContext::HTTPSessionContext(std::shared_ptr<tcp::socket> nsocket)
    : socket{nsocket}
{
}

}  // namespace beasthttp::rhandlers
