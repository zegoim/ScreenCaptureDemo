#pragma once

#if defined(__APPLE_OS__) || defined(__APPLE__)
#include "TargetConditionals.h"
#endif

#if defined(_WIN32)
#include <codecvt>
#include <locale>
#include <sstream>
#include <wchar.h>
#include <windows.h>
#define ZegoStrncpy strncpy_s
#endif

#if TARGET_OS_OSX || TARGET_OS_IPHONE
#define ZegoStrncpy strncpy
#endif

#if defined(ANDROID)
#define ZegoStrncpy strncpy
#endif

#if defined(__unix__)
#define ZegoStrncpy strncpy
#include <string.h>
#endif

#ifdef ZEGO_DISABLE_SWTICH_THREAD
#define ZEGO_SWITCH_THREAD_PRE {
#define ZEGO_SWITCH_THREAD_ING }
#else
#if defined(_WIN32)
#define ZEGO_SWITCH_THREAD_PRE                                                                     \
    std::function<void(void)> *pFunc = new std::function<void(void)>;                              \
    *pFunc = [=](void) {
#define ZEGO_SWITCH_THREAD_ING                                                                     \
    }                                                                                              \
    ;                                                                                              \
    oInternalOriginBridge->postWindowsMessage(pFunc);
#elif TARGET_OS_OSX || TARGET_OS_IPHONE
#import <Foundation/Foundation.h>
#define ZEGO_SWITCH_THREAD_PRE dispatch_async(dispatch_get_main_queue(), ^{;
#define ZEGO_SWITCH_THREAD_ING                                                                     \
    });
#else
#define ZEGO_SWITCH_THREAD_PRE {
#define ZEGO_SWITCH_THREAD_ING }
#endif
#endif

#ifdef __GNUC__
#define GCC_VERSION_AT_LEAST(x, y) (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#define GCC_VERSION_AT_LEAST(x, y) 0
#endif

#if GCC_VERSION_AT_LEAST(3, 1)
#define ZEGO_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define ZEGO_DEPRECATED __declspec(deprecated)
#else
#define ZEGO_DEPRECATED
#endif

#if defined(__ICL) || defined(__INTEL_COMPILER)
#define ZEGO_DISABLE_DEPRECATION_WARNINGS __pragma(warning(push)) __pragma(warning(disable : 1478))
#define ZEGO_ENABLE_DEPRECATION_WARNINGS __pragma(warning(pop))
#elif defined(_MSC_VER)
#define ZEGO_DISABLE_DEPRECATION_WARNINGS __pragma(warning(push)) __pragma(warning(disable : 4996))
#define ZEGO_ENABLE_DEPRECATION_WARNINGS __pragma(warning(pop))
#else
#define ZEGO_DISABLE_DEPRECATION_WARNINGS                                                          \
    _Pragma("GCC diagnostic push") _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#define ZEGO_ENABLE_DEPRECATION_WARNINGS _Pragma("GCC diagnostic pop")
#endif

#define ZEGO_UNUSED_VARIABLE(x) ((void)(x))

#include <chrono>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
