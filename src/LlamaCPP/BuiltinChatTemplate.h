#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_BUILTINCHATTEMPLATE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_BUILTINCHATTEMPLATE_CLASS_H

#include <string>

#include "src/LlamaCPP/ChatTemplate.h"

namespace llamacppi
{

/**
 * @brief The chat templates the llama.cpp formats on it's own with the
 * llama_chat_apply_template call: the ChatML, the Llama 3, the Gemma 3, the
 * Mistral, the Phi and the rest of it's built in list. The llama.cpp tells the
 * template of a model by the markers of the Jinja one, which it runs not.
 */
class BuiltinChatTemplate : public ChatTemplate
{
 public:
  /**
   * @brief A BuiltinChatTemplate constructor.
   *
   * @param modelTemplate The Jinja chat template of the model, nullptr for a
   * model of no template, which gets the ChatML one.
   */
  explicit BuiltinChatTemplate(const char* modelTemplate);

  /**
   * @brief Formats the conversation. See the ChatTemplate interface.
   *
   * @return Returns nothing for a template the llama.cpp knows not.
   */
  result apply(const messages& conversation) const override;

 private:
  /// @brief The template the llama.cpp tells the built in one by.
  const std::string llamaTemplate;
};

}  // namespace llamacppi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_BUILTINCHATTEMPLATE_CLASS_H
