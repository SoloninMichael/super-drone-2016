#include <opencv2/opencv.hpp>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"
#include "FlashDetector2.hpp"

#include <string>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

#define MAX_X 640
#define MAX_Y 360
#define MED_X MAX_X / 2
#define MED_Y MAX_Y / 2
#define MAX_FRAMES 150

int frame_counter = 0;

int key = 0;

vector<KeyPoint>  keyImg;

vector<int> num_flash;

vector<int> last_flash;


ros::Publisher pub; 


int fly_to (int x, int y)
{
	ros::Duration(0.01).sleep();
	int spin = MED_X - x;
	if ( std::abs( spin ) > 100)
	{
		// send message: turn_left spin
		std_msgs::String msg;

		if (spin > 0)
			//msg.data = "turn_left " + std::to_string(spin / 100);
			msg.data = "turn_left 1";

		else
			//msg.data = "turn_right " + std::to_string( (- spin) / 100);
			msg.data = "turn_right 1";

		ROS_INFO("%s", msg.data.c_str());
		pub.publish(msg);
		ros::Duration(0.01).sleep();
	}

	else
	{

		int altitude = MED_Y - y;
		if ( std::abs(altitude) > 100 )
		{
			// send message: up altitude
			std_msgs::String msg;
			if (altitude > 0)
				//msg.data = "up " + std::to_string(altitude / 100);
				msg.data = "up 1";
			else
				//msg.data = "down " + std::to_string( (- altitude) / 100);
				msg.data = "down 1";

			ROS_INFO("%s", msg.data.c_str());
			pub.publish(msg);
			ros::Duration(0.01).sleep();
		}
		else
		{
			std_msgs::String msg;
			msg.data = "land";

			ROS_INFO("%s", msg.data.c_str());
			pub.publish(msg);
			ros::Duration(0.01).sleep();
		}
	}


	
	// ready to fly towards the flash light
}

int detector(Mat &frame)
{
	FlashDetector det;

	Mat desc, result(frame.rows, frame.cols, CV_8UC3);

	det.detectFlash(frame, keyImg, num_flash, last_flash, frame_counter);

	drawKeypoints(frame, keyImg, result);

	// int i = 0;

	// for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); k++, i++) 

	// 	circle(result, k->pt, (int)k->size, palette[i % 65536]);

		//int kk = 0;

		//while (kk != 'a') {

	imshow("res", result);

	cvWaitKey(33);

		//}

	return 0;
}


int count = 0;

ros::Subscriber sub;

static const std::string OPENCV_WINDOW = "Image window";


void chatterCallback(const sensor_msgs::ImageConstPtr& msg)
{
    //ROS_INFO("I heard!");

    frame_counter++;

    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e)
	{
	  ROS_ERROR("cv_bridge exception: %s", e.what());
	  return;
	}

	Mat img;
	double minVal, maxVal;
	Point minLoc, maxLoc;
    int dilation_size = 3;
    
	// cvtColor(cv_ptr->image, img, CV_BGR2GRAY);
	//bilateralFilter(img, img, 3, 8, 1.5);
	Mat element = getStructuringElement(MORPH_ELLIPSE,
	Size(2 * dilation_size + 1, 2 * dilation_size + 1),
	Point(dilation_size, dilation_size));
	
	Mat new_img;

    new_img = cv_ptr->image.clone();
    
    GaussianBlur(new_img, new_img, Size(9, 9), 2, 2);
    
    dilate(new_img, new_img, element);
    
	detector(new_img);//cv_ptr->image);

	//minMaxLoc(img, &minVal, &maxVal, &minLoc, &maxLoc);
	
	if (frame_counter < MAX_FRAMES)
		return;

	vector<int>::iterator f = find_if(num_flash.begin(), num_flash.end(), IsFlash);

	
	if (f != num_flash.end()) {

		KeyPoint fin = keyImg[f - num_flash.begin()];

		cout << fin.pt.x << " " << fin.pt.y << ";   ";

		circle(cv_ptr->image, Point(fin.pt.x, fin.pt.y), 10, 255);

		imshow("found you", cv_ptr->image);

		waitKey(15); //blaze it

		fly_to (fin.pt.x, fin.pt.y);
	}

	else {
		cout << "Nothing found.\n";
		std_msgs::String msg;

		msg.data = "turn_left 1";
		
		ROS_INFO("%s", msg.data.c_str());
		pub.publish(msg);
		ros::Duration(0.01).sleep();
	}

	frame_counter = 0;
	num_flash.erase(num_flash.begin(), num_flash.end());
	last_flash.erase(last_flash.begin(), last_flash.end());
	keyImg.erase(keyImg.begin(), keyImg.end());	

	//circle(img, maxLoc, 10, (255, 0, 0), 2);
	//imshow("this", img);
	
	//waitKey(25);

	//Draw an example circle on the video stream
	//if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
	//  cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

	//Update GUI Window
    //cv::imshow(OPENCV_WINDOW, cv_ptr->image);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "cpp_img_listener");
  ros::NodeHandle n;
  ros::Rate(1).sleep();

  pub = n.advertise<std_msgs::String>("for_master", 1000);

// %Tag(SUBSCRIBER)%
  sub = n.subscribe("/ardrone/image_raw", 100, chatterCallback);
// %EndTag(SUBSCRIBER)%

// %Tag(SPIN)%
  ros::spin();
// %EndTag(SPIN)%

  return 0;
}
