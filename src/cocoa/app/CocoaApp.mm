#include "src/cocoa/CocoaLauncher.h"
#import "src/cocoa/app/TemplateCocoaAppDelegate.h"
#import "src/cocoa/cocoa_includes.h"

namespace cocoa
{

int run_cocoa_application(int& /*argc*/, char**& /*argv*/)
{
  @autoreleasepool {
    NSApplication* app = [NSApplication sharedApplication];
    [app setActivationPolicy:NSApplicationActivationPolicyRegular];

    TemplateCocoaAppDelegate* delegate =
        [[TemplateCocoaAppDelegate alloc] init];
    [app setDelegate:delegate];

    [app run];
  }

  return 0;
}

}  // namespace cocoa
