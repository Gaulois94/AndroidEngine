LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := graphicsEngine
LOCAL_CFLAGS    := -Wall

LOCAL_SRC_FILES := nativeBitmap.cpp Bitmap.cpp nativeRenderer.cpp Renderer.cpp nativeTexture.cpp Texture.cpp nativeTransformable.cpp Transformable.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -ljnigraphics

include $(BUILD_SHARED_LIBRARY)
