LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL2

# Enable this if you want to support loading JPEG images
# The library path should be a relative path to this directory.
SUPPORT_JPG := false
JPG_LIBRARY_PATH := ../SDL2_image/external/jpeg-9

# Enable this if you want to support loading PNG images
# The library path should be a relative path to this directory.
SUPPORT_PNG := true
PNG_LIBRARY_PATH := ../SDL2_image/external/libpng-1.6.2

# Enable this if you want to support loading WebP images
# The library path should be a relative path to this directory.
SUPPORT_WEBP := false
WEBP_LIBRARY_PATH := .../SDL2_image/external/libwebp-0.3.0

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include $(LOCAL_PATH)/../SDL2_image
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/state/*.cpp)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
	$(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)


