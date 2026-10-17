#include <functional>

#include "src/cocoa/CocoaLauncher.h"
#import "src/cocoa/app/TemplateCocoaAppDelegate.h"
#import "src/cocoa/cocoa_includes.h"

namespace cocoa
{

int run_cocoa_application(int& /*argc*/, char**& /*argv*/,
                          const std::function<bool()>& stop_requested)
{
  @autoreleasepool {
    NSApplication* app = [NSApplication sharedApplication];
    [app setActivationPolicy:NSApplicationActivationPolicyRegular];

    TemplateCocoaAppDelegate* delegate =
        [[TemplateCocoaAppDelegate alloc] initWithStopRequest:stop_requested];
    [app setDelegate:delegate];

    [app run];
  }

  return 0;
}

}  // namespace cocoa
