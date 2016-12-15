#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

ros::Subscriber sub;

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