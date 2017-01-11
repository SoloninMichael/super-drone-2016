#!/usr/bin/env python

import rospy
import time
from std_msgs.msg import String, Empty
from geometry_msgs.msg import Twist

class vec:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

class State:
    def __init__(self, action = "hover", times = 0):
        self.action = action
        self.times = times

class Params:
	def __init__(self, time, speed):
		self.time = time
		if abs(speed) > 1:
			self.speed = 0
			raise()
		else:
			self.speed = speed;

state = State()
linear_params = Params(time=0.65, speed=0.25)
angle_params = Params(time=1.0/3, speed=0.5)


def update_state(data):

	global state

	if data.data == "pass":
		return
	
	tmp = data.data.split()
	if len(tmp) == 1:
		state = State(tmp[0]);
		return

	if len(tmp) > 2:
		print "incorrect message! Drone will be landed!"
		rospy.sleep(1)
		state = State("land")

	state = State(tmp[0], float(tmp[1]))


def drone_driver():
    rospy.init_node('drone_driver', anonymous=True)

    global state

    takeoff_pub = rospy.Publisher('/ardrone/takeoff', Empty, queue_size=10)
    land_pub = rospy.Publisher('/ardrone/land', Empty, queue_size=10)
    go_pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    
    done_pub = rospy.Publisher('action_done', Empty, queue_size=10)

    rate = rospy.Rate(1)


    rospy.Subscriber('action', String, update_state)

    while not rospy.is_shutdown():

    	if state.action == "hover":
			go_pub.publish(Twist(linear=vec(0,0,0), angular=vec(0,0,0)))
			rate.sleep()

        elif state.action == "take_off":
		    print "gonna take off"
		    takeoff_pub.publish(Empty())
		    rate.sleep()
		    state.action = "hover"

        elif state.action == "land":
            land_pub.publish(Empty())
            rate.sleep()
            state.action = "hover"

        elif state.action == "forward":
            go_pub.publish(Twist(linear=vec(linear_params.speed,0,0), angular=vec(0,0,0)))
            rospy.sleep(state.times * linear_params.time)
            state.action = "hover"

    	elif state.action == "back":
    		go_pub.publish(Twist(linear=vec( (-1) * linear_params.speed,0,0), angular=vec(0,0,0)))
    		rospy.sleep(state.times * linear_params.time)
    		state.action = "hover"

    	elif state.action == "up":
    		go_pub.publish(Twist(linear=vec(0,0,linear_params.speed), angular=vec(0,0,0)))
    		rospy.sleep(state.times * linear_params.time)
    		state.action = "hover"

    	elif state.action == "down":
    		go_pub.publish(Twist(linear=vec(0,0,(-1) * linear_params.speed), angular=vec(0,0,0)))
    		rospy.sleep(state.times * linear_params.time)
    		state.action = "hover"

    	elif state.action == "turn_left":
    		go_pub.publish(Twist(linear=vec(0,0,0), angular=vec(0,0,angle_params.speed)))
    		rospy.sleep(state.times * angle_params.time)
    		state.action = "hover"

    	elif state.action == "turn_right":
    		go_pub.publish(Twist(linear=vec(0,0,0), angular=vec(0,0, (-1) * angle_params.speed)))
    		rospy.sleep(state.times * angle_params.time)
    		state.action = "hover"

    	else:
    		print "incorrect state! Drone will be landed! ", state.action, state.times
    		land_pub.publish(Empty())
    		rate.sleep()
    		break
    	done_pub.publish(Empty())
    	rate.sleep()

if __name__ == '__main__':
    try:
        drone_driver()
    except rospy.ROSInterruptException:
        pass
