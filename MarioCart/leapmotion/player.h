#pragma once
#include "Keyboard.h"
#include "windows.h"

namespace MarioCart{


enum Button{AButton=0, BButton, XButton, YButton, ZButton};

class Player : public Keyboard{
public:
	Player(char up='w', char down='s', char left='a', char right='d', 
				char a='x', char b='c', char l='z', char r='v', char z='b', char s=VK_RETURN);
	~Player();

	// move somewhere
	// duration means the miliseconds the arrow key will be held down
	virtual void up(int dur=25);
	virtual void down(int dur=25);
	virtual void left(int dur=25);
	virtual void right(int dur=25);


	virtual void button(Button but, int delay=10);
	virtual void back(int delay=0);

	virtual void start();

private:

	char m_upKey, m_leftKey, m_rightKey, m_downKey;

	char m_A, m_B, m_X, m_Y, m_Z, m_Start;

	bool m_picked;

	
};

}