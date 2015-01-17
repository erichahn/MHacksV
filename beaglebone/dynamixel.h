
#ifndef _DYNAMIXEL_H_
#define _DYNAMIXEL_H_

class Dynamixel{
    public:
    Dynamixel(int id, int baud=9600);
    ~Dynamixel();
	bool set_position(float position);
	float get_position();
	bool set_angle(float angle);
	int get_angle();
	bool set_speed(int speed);
	int get_speed();
	int get_load();
	bool is_moving();


    int id,baud;
};

#endif
