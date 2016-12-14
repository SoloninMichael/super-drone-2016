#!/usr/bin/env python

import rospy
import time
from std_msgs.msg import String, Empty

def move(data):
	pub.publish(data.data)

def master_drone():
    global pub
    pub = rospy.Publisher('master', String, queue_size=10)
    sub = rospy.Subscriber('for_master', String, move)
    rospy.init_node('master_drone', anonymous=True)

    # Here we can write write whatever we need drone to do
    # and post it to the topic    

    pub.publish("take_off")

    rospy.spin()
    

if __name__ == '__main__':
    try:
        master_drone()
    except rospy.ROSInterruptException:
        pass
