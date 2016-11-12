#!/usr/bin/env python

import rospy
from std_msgs.msg import String, Empty

def drone_talker():
    rospy.init_node('drone_talker', anonymous=True)

    takeoff_pub = rospy.Publisher('/ardrone/takeoff', Empty, queue_size=10)
    land_pub = rospy.Publisher('/ardrone/land', Empty, queue_size=10)

    rate = rospy.Rate(0.1)
    rospy.Rate(1).sleep()
    takeoff_pub.publish(Empty())

#    rate = rospy.Rate(1)
#    while not rospy.is_shutdown():
    rate.sleep()


    land_pub.publish(Empty())
#    rate = rospy.Rate(10) # 10hz
'''    while not rospy.is_shutdown():
        #hello_str = "hello world %s" % rospy.get_time()
        rospy.loginfo(hello_str)
        pub.publish(1)
        rate.sleep()
'''
if __name__ == '__main__':
    try:
        drone_talker()
    except rospy.ROSInterruptException:
        pass
