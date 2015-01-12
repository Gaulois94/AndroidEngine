#ifndef LOGGER_INCLUDE
#define LOGGER_INCLUDE

#include <strings.h>
#include <android/log.h>

#define LOG_TAG "Engine"

#define LOG_INFO(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOG_ERROR(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#endif
