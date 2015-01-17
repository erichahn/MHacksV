#ifndef _DYNAMIXEL_H_
#define _DYNAMIXEL_H_

// beaglebone listener port
#define PORT      2000

// beaglebone name
#define IP        "192.168.1.3"

// delay between leap motion data broadcast
#define LOOPDELAY 10000

// leap motion data
struct __attribute__((__packed__)) Leap_Messages {
	float x_pos;
	float y_pos;
	float x_vel;
	float y_vel;
};

#endif
