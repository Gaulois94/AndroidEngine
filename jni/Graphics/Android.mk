LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := graphicsEngine
LOCAL_CFLAGS    := -Wall --std=c++0x
APP_OPTIM := debug

LOCAL_SRC_FILES := nativeBitmap.cpp Bitmap.cpp nativeRenderer.cpp Renderer.cpp nativeTexture.cpp Texture.cpp nativeTransformable.cpp Transformable.cpp nativeShader.cpp Shader.cpp nativeFont.cpp Font.cpp nativeText.cpp Text.cpp nativeDrawable.cpp Drawable.cpp nativeCamera.cpp Camera.cpp Color.cpp
LOCAL_C_INCLUDES := $(NDK_APP_PROJECT_PATH)/jni/
LOCAL_SHARED_LIBRARIES := engine
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2 -ljnigraphics

include $(BUILD_SHARED_LIBRARY)
