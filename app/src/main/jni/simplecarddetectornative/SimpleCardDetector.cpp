#include "SimpleCardDetector.hh"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

SimpleCardDetector::SimpleCardDetector()
{

}

void SimpleCardDetector::detectCard(Mat &original, vector<Rect> &rects)
{
	Mat smallOnce, smallTwice; 
	Mat img_sobel, img_threshold;
	pyrDown(original,smallOnce, Size(original.cols/2,original.rows/2));
	pyrDown(smallOnce,smallTwice, Size(smallOnce.cols/2,smallOnce.rows/2));
	blur(smallTwice, smallTwice, Size(3,3)); 
	Canny(smallTwice, img_sobel, 70, 210, 3 );
	dilate(img_sobel, img_sobel, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);	
	threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	vector< vector< Point> > contours;
    findContours(img_threshold,
            contours, 
            CV_RETR_EXTERNAL, 
            CV_CHAIN_APPROX_NONE);
			
	vector<vector<Point> >::iterator itc= contours.begin();
	vector<Point> poly;
    while (itc!=contours.end()) {
		approxPolyDP(Mat(*itc), poly, arcLength(Mat(*itc), true)*0.02, true);
		Mat contourMat = Mat(poly);
        Rect mr= boundingRect(contourMat);
		if(verifyCorners(poly) &&
			verifySize(mr)){
			++itc;
			//revert size to before pyring down
			mr.x *=4;
			mr.y *=4;
			mr.width *=4;
			mr.height *=4;
			rects.push_back(mr);
		} else {
			itc= contours.erase(itc);
		}
    }
}

//adapted from finding squares 
bool SimpleCardDetector::verifyCorners(vector<Point> &contour)
{
	if(isContourConvex(Mat(contour)) && contour.size() >= 4){
		double maxCosine = 0;
		for (int j = 2; j < 5; j++)
            {
                double cosine = fabs(angle(contour[j%4], contour[j-2], contour[j-1]));
                maxCosine = MAX(maxCosine, cosine);
            }

            if (maxCosine < 0.3)
                return true;
	}
	return false;
}

double SimpleCardDetector::angle(Point pt1, Point pt2, Point pt0)
{
	double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

bool SimpleCardDetector::verifySize(Rect &rect)
{
	//aggregate aspect ratio of card
	float error = 0.3;
	float ratio = 1.54;
	if(rect.area() > 100){
		float r = 0;
		r = (float)rect.width/(float)rect.height;
		if(r < 1)
			r = (float)rect.height/(float)rect.width;
		if(r > (ratio-error) && r < (ratio + error))
			return true;
	}
	else
		return false;
}
