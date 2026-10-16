#include "GlobalLocaleGuard.h"

#include <locale>

GlobalLocaleGuard::GlobalLocaleGuard(const std::locale& newGlobal)
    : previous{std::locale::global(newGlobal)}
{
}

GlobalLocaleGuard::~GlobalLocaleGuard() { std::locale::global(previous); }
