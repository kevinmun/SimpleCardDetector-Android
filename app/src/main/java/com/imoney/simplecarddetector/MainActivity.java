package com.imoney.simplecarddetector;

import android.app.Activity;
import android.os.Bundle;

import org.opencv.android.CameraBridgeViewBase;
import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.core.MatOfRect;
import org.opencv.core.Rect;
import org.opencv.core.RotatedRect;
import org.opencv.core.Scalar;
import org.opencv.imgproc.Imgproc;


public class MainActivity extends Activity implements CameraBridgeViewBase.CvCameraViewListener2 {
    private static final Scalar CARD_RECT_COLOR     = new Scalar(0, 255, 0, 255);
    private Mat srcFrame;
    private Mat grayFrame;
    private CameraBridgeViewBase   cameraView;
    private CardDetector cardDetector;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.loadLibrary("opencv_java3");
        System.loadLibrary("simplecarddetector");
        System.loadLibrary("simplecarddetectorjni");
        setContentView(R.layout.activity_main);
        cardDetector = new CardDetector();
        cameraView = (CameraBridgeViewBase) findViewById(R.id.surface_view);
        cameraView.setCvCameraViewListener(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
        if(cameraView!=null)
            cameraView.disableView();
    }

    @Override
    protected void onResume() {
        super.onResume();
        if(cameraView!=null)
            cameraView.enableView();
    }

    @Override
    public void onCameraViewStarted(int width, int height) {
        srcFrame = new Mat();
        grayFrame = new Mat();
    }

    @Override
    public void onCameraViewStopped() {
        srcFrame.release();
        grayFrame.release();
    }

    @Override
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {
        srcFrame = inputFrame.rgba();
        grayFrame = inputFrame.gray();

        MatOfRect cards = new MatOfRect();
        cardDetector.detect(grayFrame,cards);

        Rect[] cardsArray = cards.toArray();
        for (int i = 0; i < cardsArray.length; i++)
            Imgproc.rectangle(srcFrame, cardsArray[i].tl(), cardsArray[i].br(), CARD_RECT_COLOR, 3);
        return srcFrame;
    }
}
