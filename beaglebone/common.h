#ifndef _COMMON_H_
#define _COMMON_H_


// beaglebone listener port
#define PORT      2000

// delay between leap motion data broadcast
#define LOOPDELAY 10000

// software limits for servos so they dont break
#define x_plus_limit 100
#define x_neg_limit 0

#define y_plus_limit 100
#define y_neg_limit 0

// max possible reading from leapmotion
#define max_x_pos 1.0f
#define max_y_pos 1.0f


// leap motion data
struct __attribute__((__packed__)) Leap_Messages {
	float x_pos;
	float y_pos;
	float x_vel;
	float y_vel;
};

#endif
