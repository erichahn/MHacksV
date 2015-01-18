#include "stdafx.h"
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

void Player::up(int dur){
	if (dur)tapKey(m_upKey, dur);
}
void Player::down(int dur){
	if (dur)tapKey(m_downKey, dur);
}
void Player::left(int dur){
	if (dur)tapKey(m_leftKey, dur);
}
void Player::right(int dur){
	if (dur)tapKey(m_rightKey, dur);
}


void Player::button(MarioCart::Button but, int delay){
	switch (but)
	{
		AButton: tapKey(m_A, delay); break;
		BButton: tapKey(m_B, delay); break;
		XButton: tapKey(m_X, delay); break;
		YButton: tapKey(m_Y, delay); break;
		ZButton: tapKey(m_Z, delay); break;
	}
	
}
void Player::back(int delay){
	tapKey(m_B,delay);
}

void Player::start(){
	tapKey(m_Start);
}



