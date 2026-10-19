#include "src/LlamaCPP/BuiltinChatTemplate.h"

#include <llama.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <string>
#include <vector>

namespace llamacppi
{

BuiltinChatTemplate::BuiltinChatTemplate(const char* const modelTemplate)
    : llamaTemplate{modelTemplate != nullptr ? modelTemplate : "chatml"}
{
}

ChatTemplate::result BuiltinChatTemplate::apply(
    const messages& conversation) const
{
  std::vector<llama_chat_message> chat;

  std::transform(conversation.cbegin(), conversation.cend(),
                 std::back_inserter(chat), [](const message& turn) {
                   return llama_chat_message{turn.first.c_str(),
                                             turn.second.c_str()};
                 });

  std::string prompt;
  int32_t length{0};

  // The first call tells the length of the prompt, a negative one for an
  // unknown template.
  do {
    prompt.resize(static_cast<std::size_t>(length));
    length = llama_chat_apply_template(llamaTemplate.c_str(), chat.data(),
                                       chat.size(), true, prompt.data(),
                                       static_cast<int32_t>(prompt.size()));
  } while (length > static_cast<int32_t>(prompt.size()));

  if (length < 0) {
    return {};
  }

  prompt.resize(static_cast<std::size_t>(length));

  return prompt;
}

}  // namespace llamacppi
