#include <stdio.h>

#include "dynamixel.h"
#include "dylib.h"

Dynamixel::Dynamixel(int id, int baud) : id(id), baud(baud), uart() {
    uart.Open("/dev/ttyO0", baud);
}

Dynamixel::~Dynamixel() {

}

bool Dynamixel::set_position(int position) {
    unsigned char message[256];

    message[0] = (unsigned char)0xFF;
    message[1] = (unsigned char)0xFF;
    message[2] = (unsigned char)(0xFF & id);
    message[3] = (unsigned char)0x05;
    message[4] = (unsigned char)0x03;
    message[5] = (unsigned char)0x1E;
    message[6] = (unsigned char)(0xFF & position);
    message[7] = (unsigned char)((0xFF00 & position) >> 8);
    message[8] = (unsigned char)(0xFF & calc_crc(message));

    cout << "message: ";
    
    for (int i = 0; i < 9; i++) {
        printf("%2.2x:", message[i]);
    }
    cout << endl;
    unsigned char recv[255];

    uart.Write((void*)message, 9);
    uart.Read((void*)recv, 12, 1000);

    cout << "recv: ";
    
    for (int i = 0; i < 12; i++) {
        printf("%2.2x:", recv[i]);
    }
    cout << endl;

    // int pos = (int)(position * 1024.0); 
    // pos %= 1024;

    // dxl_write_word(id, 0x1e, pos);
    // printf("goto pos %d dynamixel %d\n ",pos,id);

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

int Dynamixel::calc_crc(unsigned char * message) {
    int crc = 0;

    cout << (int)message[3] + 1 << endl;

    for (int i = 0; i < (int)message[3] + 1; i++) {
        crc += message[2 + i];
        cout << crc << endl;
    }

    return ~crc;
}
