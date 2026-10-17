#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_TEMPLATECOCOAAPPDELEGATE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_TEMPLATECOCOAAPPDELEGATE_CLASS_H

// The Objective-C interface is visible to the Objective-C++ (.mm) translation
// units only, so the C++ only tools (cppcheck) skip it.
#ifdef __OBJC__

#import "src/cocoa/cocoa_includes.h"

/**
 * @brief The Cocoa application delegate.
 *
 * Creates and shows the main window on launch and lets the application quit
 * once the last window is closed.
 */
@interface TemplateCocoaAppDelegate : NSObject <NSApplicationDelegate>
@end

#endif  // __OBJC__

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_TEMPLATECOCOAAPPDELEGATE_CLASS_H
