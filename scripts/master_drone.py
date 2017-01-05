#!/usr/bin/env python

import rospy
import time
from std_msgs.msg import String, Empty

def move(data):
    print "heard it!", data.data
    pub.publish(data.data)

def master_drone():
    global pub
    pub = rospy.Publisher('master', String, queue_size=10)
    sub = rospy.Subscriber('for_master', String, move)
    rospy.init_node('master_drone', anonymous=True)

    # Here we can write write whatever we need drone to do
    # and post it to the topic    

    try:

	#count = 200;
        #while count > 0:
	#	count -= 1
	#	pass

        pub.publish("take_off")

	print "taking off"

        rospy.sleep(5)

        #pub.publish("up 3")

        #rospy.sleep(10)

       # pub.publish("turn_left 5")

       # print "senT up"
      #  rospy.sleep(3)

       # pub.publish("land")
        #print "land"

        rospy.spin()
    except:
        pub.publish("land")
    

if __name__ == '__main__':
    try:
        master_drone()
    except rospy.ROSInterruptException:
        pass
