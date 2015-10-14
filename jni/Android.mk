LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(NDK_APP_PROJECT_PATH)/jni/Graphics/
LOCAL_MODULE := engine
LOCAL_CFLAGS := -Wall --std=c++0x
APP_OPTIM := debug

LOCAL_SRC_FILES := File.cpp JniMadeOf.cpp Updatable.cpp nativeUpdatable.cpp, nativeJniMadeOf.cpp utils.cpp EventManager.cpp nativeEventManager.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -ljnigraphics -latomic
include $(BUILD_SHARED_LIBRARY)

ZPATH := $(LOCAL_PATH)
include $(ZPATH)/Graphics/Android.mk
