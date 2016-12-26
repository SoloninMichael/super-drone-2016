#include <opencv2/opencv.hpp>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"

int count = 0;

ros::Subscriber sub;

void chatterCallback(const std_msgs::EmptyConstPtr& msg)
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
    sdfsdfsd
    // Draw an example circle on the video stream
    // if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
    //   cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, cv_ptr->image);}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "cpp_img_listener");
  ros::NodeHandle n;
  ros::Rate(1).sleep();

// %Tag(SUBSCRIBER)%
  sub = n.subscribe("/ardrone/takeoff", 100, chatterCallback);
// %EndTag(SUBSCRIBER)%

// %Tag(SPIN)%
  ros::spin();
// %EndTag(SPIN)%

  return 0;
}