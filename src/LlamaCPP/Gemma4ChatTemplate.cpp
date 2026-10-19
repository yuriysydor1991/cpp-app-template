#include "src/LlamaCPP/Gemma4ChatTemplate.h"

#include <string>
#include <string_view>

namespace llamacppi
{

namespace
{

/// @brief Tells if the given model template carries the given text.
bool carries(const char* const modelTemplate, const std::string_view text)
{
  return modelTemplate != nullptr &&
         std::string_view{modelTemplate}.find(text) != std::string_view::npos;
}

}  // namespace

Gemma4ChatTemplate::Gemma4ChatTemplate(const char* const modelTemplate)
    : closedThought{carries(modelTemplate, "'<|channel>thought\\n<channel|>'")}
{
}

ChatTemplate::result Gemma4ChatTemplate::apply(
    const messages& conversation) const
{
  std::string prompt;

  for (const auto& [role, text] : conversation) {
    prompt += "<|turn>" + (role == "assistant" ? "model" : role) + "\n" + text +
              "<turn|>\n";
  }

  return prompt + "<|turn>model\n" +
         (closedThought ? "<|channel>thought\n<channel|>" : "");
}

bool Gemma4ChatTemplate::matches(const char* const modelTemplate)
{
  return carries(modelTemplate, "<|turn>");
}

}  // namespace llamacppi
