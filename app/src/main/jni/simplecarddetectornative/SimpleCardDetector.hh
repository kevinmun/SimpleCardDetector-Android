#ifndef SIMPLE_CARD_DETECTOR_HH
#define SIMPLE_CARD_DETECTOR_HH
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;
class SimpleCardDetector{
public:
  SimpleCardDetector();
  void detectCard(Mat &original, vector<Rect> &cards);
  bool verifySize(Rect &rect);
  bool verifyCorners(vector<Point> &contour);
  double angle(Point pt1, Point pt2, Point pt0);
private:
  Mat src;
};
#endif