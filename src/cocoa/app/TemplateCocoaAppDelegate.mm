#import "src/cocoa/app/TemplateCocoaAppDelegate.h"

#include "project-global-decls.h"
#include "src/cocoa/helpers/WindowConfig.h"
#include "src/cocoa/main-window/CocoaMainWindow.h"

@implementation TemplateCocoaAppDelegate {
  NSWindow* _window;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
  const cocoa::helpers::WindowConfig config{
      project_decls::PROJECT_NAME, project_decls::PROJECT_BUILD_VERSION};

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
