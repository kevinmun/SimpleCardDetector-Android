LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#opencv
OPENCVROOT:= C:\OpenCV-3.0.0-android-sdk-1\OpenCV-android-sdk
OPENCV_CAMERA_MODULES:=off
OPENCV_INSTALL_MODULES:=on
OPENCV_LIB_TYPE:=SHARED
include ${OPENCVROOT}/sdk/native/jni/OpenCV.mk

SIMPLECARDDETECTOR_FILES  := $(wildcard $(LOCAL_PATH)/simplecarddetectornative/*.cpp)
SIMPLECARDDETECTOR_FILES  := $(SIMPLECARDDETECTOR_FILES:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES := $(SIMPLECARDDETECTOR_FILES)
LOCAL_LDLIBS += -llog
LOCAL_MODULE := simplecarddetector
LOCAL_C_INCLUDES += $(LOCAL_PATH)/simplecarddetectornative

include $(BUILD_SHARED_LIBRARY)