#include "dynamixel.h"

Dynamixel::Dynamixel(int id, int baud) : id(id), baud(baud) {

}

Dynamixel::~Dynamixel() {

}

bool Dynamixel::set_position(int position) {

    return false;
}

int Dynamixel::get_position() {

    return 0;
}

bool Dynamixel::set_angle(float angle) {

    return false;
}

int Dynamixel::get_angle() {
    
    return 0;
}

bool Dynamixel::set_speed(int speed) {
    
    return false;
}

int Dynamixel::get_speed() {
    
    return 0;
}

int Dynamixel::get_load() {

    return 0;
}

bool Dynamixel::is_moving() {

    return 0;
}
