LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_CFLAGS  = -Werror -O0 -Wno-unused-parameter
LOCAL_SRC_FILES:= yuv2jpeg.c turbojpeg.c jdatadst-tj.c
LOCAL_SHARED_LIBRARIES:= libcutils libdl
LOCAL_STATIC_LIBRARIES := libjpeg_static_ndk libyuv_static
LOCAL_MODULE:= yuv2jpeg
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_CFLAGS  = -Werror -O0 -Wno-unused-parameter
LOCAL_SRC_FILES:= yuv2jpeg.c turbojpeg.c jdatadst-tj.c
LOCAL_SHARED_LIBRARIES:= libcutils libdl
LOCAL_STATIC_LIBRARIES := libjpeg_static_ndk libyuv_static
LOCAL_MODULE:= yuv2jpeg_32
LOCAL_MODULE_TAGS := optional
LOCAL_32_BIT_ONLY := true
include $(BUILD_EXECUTABLE)
