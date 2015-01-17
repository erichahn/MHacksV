#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

#include <iostream>
#include <string>
#include "serialib.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

class Dynamixel {
private:
	int id, baud;
	serialib uart;

	int calc_crc(unsigned char * message);
public:
    Dynamixel(int id, int baud=9600);
    ~Dynamixel();
	bool set_position(int position);
	float get_position();
	bool set_angle(float angle);
	int get_angle();
	bool set_speed(int speed);
	int get_speed();
	int get_load();
	bool is_moving();
};

#endif