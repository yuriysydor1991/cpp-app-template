#include "src/cocoa/main-window/CocoaMainWindow.h"

namespace cocoa::main_window
{

CocoaMainWindow::CocoaMainWindow(const helpers::WindowConfig& config)
{
  const NSRect frame = NSMakeRect(0, 0, config.width(), config.height());

  win = [[NSWindow alloc]
      initWithContentRect:frame
                styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                           NSWindowStyleMaskMiniaturizable |
                           NSWindowStyleMaskResizable)
                  backing:NSBackingStoreBuffered
                    defer:NO];

  [win setTitle:[NSString stringWithUTF8String:config.title().c_str()]];
  [win setMinSize:NSMakeSize(config.min_width(), config.min_height())];

  build_content(config);

  [win center];
}

NSWindow* CocoaMainWindow::window() const { return win; }

void CocoaMainWindow::build_content(const helpers::WindowConfig& config)
{
  NSTextField* header = [NSTextField
      labelWithString:[NSString stringWithUTF8String:config.header_text().c_str()]];
  [header setFont:[NSFont boldSystemFontOfSize:24]];

  NSTextField* explanation = [NSTextField
      labelWithString:[NSString
                          stringWithUTF8String:config.explanation_text().c_str()]];

  NSStackView* stack = [NSStackView stackViewWithViews:@[ header, explanation ]];
  [stack setOrientation:NSUserInterfaceLayoutOrientationVertical];
  [stack setAlignment:NSLayoutAttributeCenterX];
  [stack setSpacing:12];
  [stack setTranslatesAutoresizingMaskIntoConstraints:NO];

  NSView* content = [win contentView];
  [content addSubview:stack];

  [NSLayoutConstraint activateConstraints:@[
    [[stack centerXAnchor] constraintEqualToAnchor:[content centerXAnchor]],
    [[stack centerYAnchor] constraintEqualToAnchor:[content centerYAnchor]]
  ]];
}

}  // namespace cocoa::main_window
