#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

#define MAX_X 1280
#define MAX_Y 720
#define MED_X MAX_X / 2
#define MED_Y MAX_Y / 2

int fly_to (int x, int y)
{
	int spin = MED_X - x;
	if ( spin )
	{
		// send message: turn_left spin
		std_msgs::String msg;
		std::stringstream ss;
		ss << "turn_left " << spin;
		msg.data = ss.str();
		ROS_INFO("%s", msg.data.c_str());
		chatter_pub.publish(msg);
		ros::spinOnce();
	}

	int altitude = MED_Y - y;
	if ( altitude )
	{
		// send message: up altitude
		std_msgs::String msg;
		std::stringstream ss;
		ss << "up " << altitude;
		msg.data = ss.str();
		ROS_INFO("%s", msg.data.c_str());
		chatter_pub.publish(msg);
		ros::spinOnce();
	}
	
	// ready to fly towards the flash light
}



