<<<<<<< HEAD
//#include "stdafx.h"
=======
>>>>>>> 7da31b8514175da386324fc65e4a8a922b79edd6
#include "player.h"
#include "windows.h"

using MarioCart::Player;

Player::Player(char up, char down, char left, char right, 
				char a, char b, char l, char r, char z, char s):
m_upKey(up), m_downKey(down), m_leftKey(left), m_rightKey(right), 
m_A(a), m_B(b), m_X(l), m_Y(r), m_Z(z), m_Start(s)
{

}

Player::~Player(){
}

void Player::up(int dur, int flags){
	if (dur)tapKey('w', dur, flags);
}
void Player::down(int dur, int flags){
	if (dur)tapKey('s', dur, flags);
}
void Player::left(int dur, int flags){
	if (dur)tapKey('a', dur, flags);
}
void Player::right(int dur, int flags){
	if (dur)tapKey('d', dur, flags);
}

void Player::upOff(int dur, int flags){
	tapKey('w', 0, 0);
}
void Player::downOff(int dur, int flags){
	tapKey('s', 0,0);
}
void Player::leftOff(int dur, int flags){
	tapKey('a', 0,0);
}
void Player::rightOff(int dur, int flags){
	tapKey('d', 0, 0);
}

void Player::button(MarioCart::Button but, int delay){
	switch (but)
	{
		case AButton:
			tapKey(m_A, delay);
			break;
		case BButton:
			tapKey(m_B, delay);
			break;
		case XButton:
			tapKey(m_X, delay);
			break;
		case YButton:
			tapKey(m_Y, delay);
			break;
		case ZButton:
			tapKey(m_Z, delay);
			break;
	}
	
}
void Player::back(int delay){
	tapKey(m_B,delay);
}

void Player::start(){
	tapKey(m_Start);
}



