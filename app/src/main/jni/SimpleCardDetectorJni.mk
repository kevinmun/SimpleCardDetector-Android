LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#opencv
OPENCVROOT:= C:\OpenCV-3.0.0-android-sdk-1\OpenCV-android-sdk
OPENCV_CAMERA_MODULES:=off
OPENCV_INSTALL_MODULES:=on
OPENCV_LIB_TYPE:=SHARED
include ${OPENCVROOT}/sdk/native/jni/OpenCV.mk

SIMPLECARDDETECTORJNI_FILES  := $(wildcard $(LOCAL_PATH)/simplecarddetectorjni/*.cpp)
SIMPLECARDDETECTORJNI_FILES  := $(SIMPLECARDDETECTORJNI_FILES:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := $(SIMPLECARDDETECTORJNI_FILES)
LOCAL_LDLIBS += -llog
LOCAL_MODULE := simplecarddetectorjni
LOCAL_C_INCLUDES += $(LOCAL_PATH)/simplecarddetectorjni $(LOCAL_PATH)/simplecarddetectornative
LOCAL_STATIC_LIBRARIES := simplecarddetector

include $(BUILD_SHARED_LIBRARY)