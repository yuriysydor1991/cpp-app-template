#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GEMMA4CHATTEMPLATE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GEMMA4CHATTEMPLATE_CLASS_H

#include "src/LlamaCPP/ChatTemplate.h"

namespace llamacppi
{

/**
 * @brief The turns of the Gemma 4 models, which no llama.cpp built in template
 * formats: every message is the <|turn>role ... <turn|> one, the answers of
 * the assistant are the ones of the model role.
 *
 * The templates of the bigger Gemma 4 models close the thought channel of the
 * answer ahead of it, so the model answers with no thinking. The template
 * formats the turns the way the Jinja one of the model does with no tools and
 * no thinking enabled.
 */
class Gemma4ChatTemplate : public ChatTemplate
{
 public:
  /**
   * @brief A Gemma4ChatTemplate constructor.
   *
   * @param modelTemplate The Jinja chat template of the model, which tells if
   * the answers start with the closed thought channel.
   */
  explicit Gemma4ChatTemplate(const char* modelTemplate);

  /// @brief Formats the conversation. See the ChatTemplate interface.
  result apply(const messages& conversation) const override;

  /// @brief Tells if the given Jinja chat template of a model is the Gemma 4
  /// one.
  static bool matches(const char* modelTemplate);

 private:
  const bool closedThought;
};

}  // namespace llamacppi

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GEMMA4CHATTEMPLATE_CLASS_H
