#include <opencv2/opencv.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <iterator>
#include <limits>
#include <cmath>

using namespace std;
using namespace cv;

static double EPS;

static KeyPoint pnt;

bool InEps(KeyPoint&);

bool IsFlash(int&);

class FlashDetector {           //based on SimpleBlobDetector
public:

	struct CV_EXPORTS Center
	{
		Point2d location;
		double radius;
		double confidence;
	};

	virtual void detectFlash(InputArray image, std::vector<KeyPoint>& keypoints, std::vector<int>& num_flsh);//InputArray mask = noArray());
	virtual void findBlobs(InputArray image, InputArray binaryImage, std::vector<Center> &centers, InputArray img) const;

private:

	const double minArea = 10;
	const double maxArea = 800;
	const double minCircularity = 0.5;
	const double maxCircularity = 1.0;
	const double minInertiaRatio = 0.5;
	const double maxInertiaRatio = 1.0;
	const double minConvexity = 0.1;
	const double maxConvexity = 1.0;
	const int blobColor = 255;

	const int thresholdStep = 10;
	const int minThreshold = 50;
	const int maxThreshold = 220;
	const int minRepeatability = 2;
	const int minDistBetweenBlobs = 10;

};

