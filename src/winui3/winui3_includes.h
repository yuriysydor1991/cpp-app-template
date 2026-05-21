#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_INCLUDES_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_INCLUDES_H

// Aggregated C++/WinRT + WinUI 3 (Windows App SDK) headers used by the native,
// Windows-only UI translation units. This header is only ever included from
// WIN32 builds (the portable orchestration never pulls it in).
//
// The winrt/* headers are produced by the C++/WinRT projection (cppwinrt.exe)
// from the Windows SDK + Windows App SDK metadata; see the WinUI 3 enabler and
// the documentation for how that generation is wired on a Windows host.

#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_WINUI3_INCLUDES_H
