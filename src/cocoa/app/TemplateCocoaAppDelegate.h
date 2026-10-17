#ifndef YOUR_CPP_APP_TEMPLATE_PROJECT_TEMPLATECOCOAAPPDELEGATE_CLASS_H
#define YOUR_CPP_APP_TEMPLATE_PROJECT_TEMPLATECOCOAAPPDELEGATE_CLASS_H

// The Objective-C interface is visible to the Objective-C++ (.mm) translation
// units only, so the C++ only tools (cppcheck) skip it.
#ifdef __OBJC__

#include <functional>

#import "src/cocoa/cocoa_includes.h"

/**
 * @brief The Cocoa application delegate.
 *
 * Creates and shows the main window on launch and lets the application quit
 * once the last window is closed. Polls the stop request every 100 ms and
 * leaves the event loop once it is raised (the signals handlers only raise the
 * application context stop flag).
 */
@interface TemplateCocoaAppDelegate : NSObject <NSApplicationDelegate>

/**
 * @brief Initializes the delegate with the stop request to poll.
 *
 * @param stopRequested Returns true once the application stop is requested.
 */
- (instancetype)initWithStopRequest:(std::function<bool()>)stopRequested;

@end

#endif  // __OBJC__

#endif  // YOUR_CPP_APP_TEMPLATE_PROJECT_TEMPLATECOCOAAPPDELEGATE_CLASS_H
