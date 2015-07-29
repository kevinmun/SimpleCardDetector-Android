package com.imoney.simplecarddetector;

import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;

/**
 * Created by Kevin on 7/29/2015.
 */
public class CardDetector {
    private long mNativeDetector = 0;

    public CardDetector(){
        mNativeDetector = nativeCreateObject();
    }

    public void release() {
        nativeDestroyObject(mNativeDetector);
        mNativeDetector = 0;
    }

    public void detect(Mat imageGray, MatOfRect cards) {
        nativeDetect(mNativeDetector, imageGray.getNativeObjAddr(), cards.getNativeObjAddr());
    }

    private static native long nativeCreateObject();
    private static native void nativeDestroyObject(long thiz);
    private static native void nativeDetect(long thiz, long inputImage, long cards);
}
