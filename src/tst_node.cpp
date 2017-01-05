#include <opencv2/opencv.hpp>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"

#include <ros/ros.h>
#include <sstream>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");

  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Duration(0.3).sleep();

  ros::Rate loop_rate(10);

 // int count = 1;

  //  while (ros::ok())
  // {

    std_msgs::String msg;

    msg.data = "land";


    std_msgs::String msg2;
    
    msg.data = "go";
    
    // std::stringstream ss;
    // ss << "hello world ";
    // msg.data = ss.str();

    // //std::stringstream ss;
    // //ss << "hello world " << count;
    // //msg.data = "take_off"; //ss.str();

    // std::cout << "posted" << std::endl;

    // chatter_pub.publish(msg);

    // ros::Duration(3).sleep();

 
    chatter_pub.publish(msg);
    ros::Duration(0.1).sleep();

    chatter_pub.publish(msg);
    ros::Duration(0.1).sleep();

    chatter_pub.publish(msg);
    ros::Duration(0.1).sleep();

    chatter_pub.publish(msg);
    ros::Duration(0.1).sleep();

    // chatter_pub.publish(msg);




    // ROS_INFO("%s", msg.data.c_str());

    // chatter_pub.publish(msg);

    // ros::spinOnce();

    // loop_rate.sleep();
    // ++count;
//  }

  return 0;
}