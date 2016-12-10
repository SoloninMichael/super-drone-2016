#!/usr/bin/env python

import rospy
import time
from std_msgs.msg import String, Empty

def master_drone():
    pub = rospy.Publisher('master', String, queue_size=10)
    rospy.init_node('master_drone', anonymous=True)

    # Here we can write write whatever we need drone to do
    # and post it to the topic

    pub.publish("take_off")

    rospy.sleep(4)

    pub.publish("pass")

    rospy.sleep(4)

    pub.publish("turn_left 1")

    rospy.sleep(4)

    pub.publish("turn_right 1")

    rospy.sleep(4)

    pub.publish("land")

if __name__ == '__main__':
    try:
        master_drone()
    except rospy.ROSInterruptException:
        pass
