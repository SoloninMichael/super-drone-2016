#include <opencv2/opencv.hpp>

#include "FlashDetector.h"

using namespace std;
using namespace cv;


int main(int argc, char *argv[]) {

	VideoCapture cap;

	if (argc > 1) 
		cap.open(argv[1]);
	else
		cap.open(0);

	if (!cap.isOpened()) {
		std::cerr << "Cannot initialize video." << std::endl;
		return -1;
	}

	FlashDetector det;
	vector< Vec3b >  palette;
	for (int i = 0; i<65536; i++)
		palette.push_back(Vec3b((uchar)rand(), (uchar)rand(), (uchar)rand()));

	int num = 0;
	int key = 0;

	vector<KeyPoint>  keyImg;
	vector<int> num_flash;
	vector<int> last_flash;
	Mat fr, frame;
	int dilation_size = 10;
	Size size(600, 400); //set desired size 
	Mat element = getStructuringElement(MORPH_ELLIPSE,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));

	/*
	please note that our goal here is merely to recognize the flash every time it happenes. 
	for this purpose the frame number is printed to stdout when a found blob is updated (found again)
	to identify the flashlight calibrate the parameters 
	*/
	while (key != 'q' && num < 130) {
		cap.read(fr);
		resize(fr, fr, size, 0, 0); //resize image for faster processing. might not need this on drone //Size(), 0.5, 0.5); //shrink by a factor of two 
		frame = fr.clone();
		dilate(fr, frame, element); //emphasize light, may not work if flashlight too close to other light scources! => change dilation_size (lower)
		//imshow("res", frame);
		//waitKey(300);
		//medianBlur(fr, frame, 11); // blur image to minimize noise 

		if (frame.empty()) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}

		num++;
		//cout << "frame: " << num << "\n";

		Mat desc, result(frame.rows, frame.cols, CV_8UC3);
		det.detectFlash(frame, keyImg, num_flash, last_flash, num);
		drawKeypoints(frame, keyImg, result);

		int i = 0;

		for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); k++, i++) 
			circle(result, k->pt, (int)k->size, palette[i % 65536]);

		//int kk = 0;
		//while (kk != 'a') {
			imshow("res", result);
			waitKey(30);
		//	kk = cvWaitKey(33);
		//}

		
		key = cvWaitKey(33);
	}

	vector<int>::iterator f = find_if(num_flash.begin(), num_flash.end(), IsFlash);
	if (f != num_flash.end()) {
		KeyPoint fin = keyImg[f - num_flash.begin()];
		cout << fin.pt.x << " " << fin.pt.y << ";   ";
		circle(frame, Point(fin.pt.x, fin.pt.y), 10, 255);
		while (key != 'q') {
			imshow("found you", frame);
			key = cvWaitKey(33);
		}
	}
	else {
		cout << "Nothing found.\n";
	}


	return 0;
}


