#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_CHATTEMPLATE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_CHATTEMPLATE_CLASS_H

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace llamacppi
{

/**
 * @brief The chat template of a language model, which turns the conversation
 * into the prompt the model continues with it's answer.
 *
 * Every model is trained on the turns of it's own format, the one the Jinja
 * chat template of it's GGUF file describes, so the ChatTemplate::create call
 * picks the implementation of the model template.
 */
class ChatTemplate
{
 public:
  /// @brief A message of the conversation: the role (the user, the assistant
  /// or the system one) and the text of it.
  using message = std::pair<std::string, std::string>;
  using messages = std::vector<message>;
  using result = std::optional<std::string>;
  using ChatTemplatePtr = std::shared_ptr<ChatTemplate>;

  virtual ~ChatTemplate() = default;
  ChatTemplate() = default;

  /**
   * @brief Formats the given conversation into the prompt, which ends with
   * the start of the next answer of the assistant.
   *
   * @param conversation The messages of the conversation in their order.
   *
   * @return Returns the prompt or nothing if the conversation fails to format.
   */
  virtual result apply(const messages& conversation) const = 0;

  /**
   * @brief Creates the template of the given chat template of a model.
   *
   * @param modelTemplate The Jinja chat template of the model GGUF file (the
   * llama_model_chat_template one), nullptr for a model of no template.
   *
   * @return Returns the template of the llama.cpp built in ones the model
   * template matches or the Gemma 4 one, nullptr for an unknown template.
   */
  static ChatTemplatePtr create(const char* modelTemplate);
};

using ChatTemplatePtr = ChatTemplate::ChatTemplatePtr;

}  // namespace llamacppi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_CHATTEMPLATE_CLASS_H
