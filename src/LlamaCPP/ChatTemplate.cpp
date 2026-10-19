#include "src/LlamaCPP/ChatTemplate.h"

#include <memory>

#include "src/LlamaCPP/BuiltinChatTemplate.h"
#include "src/LlamaCPP/Gemma4ChatTemplate.h"

namespace llamacppi
{

ChatTemplatePtr ChatTemplate::create(const char* const modelTemplate)
{
  // A template the llama.cpp recognizes formats a probe conversation.
  auto builtin = std::make_shared<BuiltinChatTemplate>(modelTemplate);

  if (builtin->apply({{"user", "?"}}).has_value()) {
    return builtin;
  }

  if (Gemma4ChatTemplate::matches(modelTemplate)) {
    return std::make_shared<Gemma4ChatTemplate>(modelTemplate);
  }

  return nullptr;
}

}  // namespace llamacppi
