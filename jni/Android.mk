LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := engine
LOCAL_CFLAGS := -Wall --std=c++0x
APP_OPTIM := debug

LOCAL_SRC_FILES := File.cpp JniMadeOf.cpp Updatable.cpp nativeJniMadeOf.cpp utils.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -ljnigraphics -latomic
include $(BUILD_SHARED_LIBRARY)

ZPATH := $(LOCAL_PATH)
include $(ZPATH)/Graphics/Android.mk
