#import "src/cocoa/cocoa_includes.h"

#include "project-global-decls.h"
#include "src/cocoa/CocoaLauncher.h"
#include "src/cocoa/helpers/WindowConfig.h"
#include "src/cocoa/main-window/CocoaMainWindow.h"

// The application delegate creates and shows the main window on launch and lets
// the app quit once the last window is closed.
@interface TemplateCocoaAppDelegate : NSObject <NSApplicationDelegate>
@end

@implementation TemplateCocoaAppDelegate {
  NSWindow* _window;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
  const cocoa::helpers::WindowConfig config{project_decls::PROJECT_NAME,
                                            project_decls::PROJECT_BUILD_VERSION};

  cocoa::main_window::CocoaMainWindow mainWindow{config};
  _window = mainWindow.window();

  [_window makeKeyAndOrderFront:nil];
  [NSApp activateIgnoringOtherApps:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
  return YES;
}

@end

namespace cocoa
{

int run_cocoa_application(int& /*argc*/, char**& /*argv*/)
{
  @autoreleasepool {
    NSApplication* app = [NSApplication sharedApplication];
    [app setActivationPolicy:NSApplicationActivationPolicyRegular];

    TemplateCocoaAppDelegate* delegate = [[TemplateCocoaAppDelegate alloc] init];
    [app setDelegate:delegate];

    [app run];
  }

  return 0;
}

}  // namespace cocoa
