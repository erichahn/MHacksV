#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

#include "serialib.h"
#include <iostream>
#include <string>
#include <errno.h>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

class Dynamixel {
private:
	int id, baud;

public:
	Dynamixel(int id, int baud);
	~Dynamixel();
	bool set_position(int position);
	int get_position();
	bool set_angle(float angle);
	int get_angle();
	bool set_speed(int speed);
	int get_speed();
	int get_load();
	bool is_moving();
};

#endif