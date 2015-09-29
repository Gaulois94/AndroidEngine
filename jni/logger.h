#ifndef LOGGER_INCLUDE
#define LOGGER_INCLUDE

#include <strings.h>
#include <android/log.h>

#define LOG_TAG "Engine" /* <The log tag for android logcat */

#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__) /* <Print an info on the android log */
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__) /* <Print an error on the android log */


#endif
