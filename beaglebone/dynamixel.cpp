#include <stdio.h>

#include "dynamixel.h"
#include "dylib.h"

Dynamixel::Dynamixel(int id, int baud) : id(id), baud(baud) {
    
}

Dynamixel::~Dynamixel() {

}

bool Dynamixel::set_position(float position) {
    int pos = (int)(position * 1024.0); 
    pos %= 1024;

    dxl_write_word(id, 0x1e, pos);
    printf("goto pos %d dynamixel %d\n ",pos,id);

    return false;
}

float Dynamixel::get_position() {
    
    return 0/1024.0;
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
