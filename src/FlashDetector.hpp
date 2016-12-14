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
//std::vector<int> num_flsh;

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

	double minArea = 10;
	double maxArea = 800;
	double minCircularity = 0.5;
	double maxCircularity = 1.0;
	double minInertiaRatio = 0.5;
	double maxInertiaRatio = 1.0;
	double minConvexity = 0.1;
	double maxConvexity = 1.0;
	int blobColor = 255;

	int thresholdStep = 10;
	int minThreshold = 50;
	int maxThreshold = 220;
	int minRepeatability = 2;
	int minDistBetweenBlobs = 10;

};

