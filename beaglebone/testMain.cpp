#include "dynamixel.h"

int main() {
	Dynamixel servo(3, 9600);
	usleep(100000);
	servo.set_position(1023);
	usleep(1000000);
	servo.set_position(0);

	return 0;
}