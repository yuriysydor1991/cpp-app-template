#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXT_TRANSLATION_DECLARATIONS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXT_TRANSLATION_DECLARATIONS_H

#include <libintl.h>

namespace gettexti
{

/**
 * @brief Translates the message into the language of the user through the
 * catalogs the GettextController class binds. Pass the string literals only,
 * since the gettext-pot target extracts the messages to translate out of the
 * tr calls of the sources.
 *
 * @param msgid The English message, which is given back as is while no
 * translation of it is available.
 *
 * @return Returns the translated UTF-8 message.
 */
inline const char* tr(const char* msgid) { return gettext(msgid); }

/**
 * @brief Translates the message in the plural form the count asks for in the
 * language of the user (e.g. the Ukrainian language has three of them).
 *
 * @param msgid The English singular message.
 * @param msgidPlural The English plural message.
 * @param n The count to choose the plural form for.
 *
 * @return Returns the translated UTF-8 message.
 */
inline const char* trn(const char* msgid, const char* msgidPlural,
                       unsigned long n)
{
  return ngettext(msgid, msgidPlural, n);
}

}  // namespace gettexti

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_GETTEXT_TRANSLATION_DECLARATIONS_H
