#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
from std_msgs.msg import String
from cv_bridge import CvBridge, CvBridgeError
import cv2
import os
import signal
i = 0

def myshow(data):
    global i
    '''f = open('img', 'w')
    f.write(data.data)
    f.close()'''
    cv_image = CvBridge().imgmsg_to_cv2(data, "bgr8")
    gr = cv2.cvtColor(cv_image, cv2.COLOR_BGR2GRAY)
    cv2.imshow("Image window", gr)
    cv2.waitKey(25)
    print i
    i += 1
    if i > 100:
	sub.unregister()
#    rospy.Rate(0.1).sleep()

def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('img_listener', anonymous=True)
    rospy.Rate(1).sleep()

    global sub
    sub = rospy.Subscriber('/ardrone/image_raw', Image, myshow)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()
    exit()

if __name__ == '__main__':
    listener()
