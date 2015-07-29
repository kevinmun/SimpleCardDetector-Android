#include <com_imoney_simplecarddetector_CardDetector.h>
#include <opencv2/core/core.hpp>
#include <vector>
#include "SimpleCardDetector.hh"

using namespace std;
using namespace cv;

JNIEXPORT jlong JNICALL Java_com_imoney_simplecarddetector_CardDetector_nativeCreateObject
  (JNIEnv * jenv, jclass)
  {
	return (jlong)new SimpleCardDetector();
  }

/*
 * Class:     com_imoney_simplecarddetector_CardDetector
 * Method:    nativeDestroyObject
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_imoney_simplecarddetector_CardDetector_nativeDestroyObject
  (JNIEnv *, jclass, jlong thiz)
  {
	delete (SimpleCardDetector*)thiz;
  }

/*
 * Class:     com_imoney_simplecarddetector_CardDetector
 * Method:    nativeDetect
 * Signature: (JJJ)V
 */
JNIEXPORT void JNICALL Java_com_imoney_simplecarddetector_CardDetector_nativeDetect
  (JNIEnv *, jclass, jlong thiz, jlong imageGray, jlong cards)
  {
	vector<Rect> cardRects;
	((SimpleCardDetector*)thiz)->detectCard(*((Mat*)imageGray),cardRects);
	*((Mat*)cards) = Mat(cardRects, true);
	return;
  }

