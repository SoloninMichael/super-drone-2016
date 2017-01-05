#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	Mat src, img;
	src = imread(argv[1]);
	double minVal, maxVal;
	Point minLoc, maxLoc;

	cvtColor(src, img, CV_BGR2GRAY);
	bilateralFilter(img, img, 3, 8, 1.5);
	minMaxLoc(img, &minVal, &maxVal, &minLoc, &maxLoc);
	circle(img, maxLoc, 10, (255, 0, 0), 2);
	imshow("this", img);

	waitKey(25);

	return 0;
}