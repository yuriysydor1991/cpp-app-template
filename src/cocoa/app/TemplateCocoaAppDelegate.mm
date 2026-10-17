#import "src/cocoa/app/TemplateCocoaAppDelegate.h"

#include <functional>
#include <utility>

#include "project-global-decls.h"
#include "src/cocoa/helpers/WindowConfig.h"
#include "src/cocoa/main-window/CocoaMainWindow.h"

@implementation TemplateCocoaAppDelegate {
  NSWindow* _window;
  std::function<bool()> _stopRequested;
}

- (instancetype)initWithStopRequest:(std::function<bool()>)stopRequested
{
  self = [super init];

  if (self != nil) {
    _stopRequested = std::move(stopRequested);
  }

  return self;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification
{
  const cocoa::helpers::WindowConfig config{
      project_decls::PROJECT_NAME, project_decls::PROJECT_BUILD_VERSION};

  cocoa::main_window::CocoaMainWindow mainWindow{config};
  _window = mainWindow.window();

  [_window makeKeyAndOrderFront:nil];
  [NSApp activateIgnoringOtherApps:YES];

  [NSTimer scheduledTimerWithTimeInterval:0.1
                                   target:self
                                 selector:@selector(checkStopRequest:)
                                 userInfo:nil
                                  repeats:YES];
}

- (void)checkStopRequest:(NSTimer*)timer
{
  if (!_stopRequested || !_stopRequested()) {
    return;
  }

  [timer invalidate];

  // [NSApp run] returns to the run_cocoa_application() caller, which tears the
  // application down normally; stop: takes effect once the next event is
  // processed, so post one to wake the event loop up.
  [NSApp stop:nil];
  [NSApp postEvent:[NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                      location:NSZeroPoint
                                 modifierFlags:0
                                     timestamp:0
                                  windowNumber:0
                                       context:nil
                                       subtype:0
                                         data1:0
                                         data2:0]
           atStart:YES];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
  return YES;
}

@end
