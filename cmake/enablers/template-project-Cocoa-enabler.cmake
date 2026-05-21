cmake_minimum_required(VERSION 3.13)

# Enabler module for the macOS Cocoa / AppKit GUI written in Objective-C++.
#
# Cocoa is a macOS-only UI framework; the native window is implemented in
# Objective-C++ (.mm) translation units that mix C++ and Objective-C. This
# module enables the OBJCXX language and exposes the cocoa::sdk target (the Cocoa
# umbrella framework: AppKit + Foundation) that the native UI links against.
#
# On a non-Apple host this module is a deliberate no-op: the portable Cocoa
# orchestration (cocoa::CocoaIniter + the WindowConfig helper) and the
# cross-platform run_cocoa_application() stub are still built, so the project
# configures, builds and runs its unit/component tests everywhere. The real
# Cocoa window only builds on macOS. See src/cocoa and the documentation.

option(
  ENABLE_COCOA
  "Enables the macOS Cocoa/AppKit + Objective-C++ GUI (macOS only; the portable parts + a stub build elsewhere)"
  ON
)

if(NOT ENABLE_COCOA)
  return()
endif()

if(NOT APPLE)
  message(STATUS "Cocoa / AppKit is a macOS-only framework")
  message(STATUS "Skipping the native Cocoa setup; the portable Cocoa orchestration and the non-Apple run_cocoa_application() stub will be built instead")
  return()
endif()

# The native window code is Objective-C++ (.mm); enable that language for the
# build (it is only available with an Apple/clang toolchain).
enable_language(OBJCXX)

# The Cocoa umbrella framework pulls in AppKit + Foundation + CoreData.
find_library(COCOA_FRAMEWORK Cocoa REQUIRED)

add_library(cocoa-sdk INTERFACE)
add_library(cocoa::sdk ALIAS cocoa-sdk)

target_link_libraries(cocoa-sdk INTERFACE ${COCOA_FRAMEWORK})

# Build the Objective-C++ sources with Automatic Reference Counting so the
# AppKit objects are memory managed for you.
target_compile_options(cocoa-sdk INTERFACE $<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>)

message(STATUS "Cocoa framework target 'cocoa::sdk' configured (${COCOA_FRAMEWORK})")
