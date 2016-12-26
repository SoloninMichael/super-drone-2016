#include <opencv2/opencv.hpp>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int count = 0;

ros::Subscriber sub;

static const std::string OPENCV_WINDOW = "Image window";

void chatterCallback(const sensor_msgs::ImageConstPtr& msg)
{
    ROS_INFO("I heard!");

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

	//Draw an example circle on the video stream
	if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
	  cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

	//Update GUI Window
    cv::imshow(OPENCV_WINDOW, cv_ptr->image);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "cpp_img_listener");
  ros::NodeHandle n;
  ros::Rate(1).sleep();

// %Tag(SUBSCRIBER)%
  sub = n.subscribe("/ardrone/image_raw", 100, chatterCallback);
// %EndTag(SUBSCRIBER)%

// %Tag(SPIN)%
  ros::spin();
// %EndTag(SPIN)%

  return 0;
}