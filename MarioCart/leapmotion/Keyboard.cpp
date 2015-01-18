//#include "stdafx.h"
#include "Keyboard.h"
#include "windows.h"


Keyboard::Keyboard() : m_delay(20){

}

Keyboard::~Keyboard(){

}

static int getVKeyCode(char key){
	switch(key){
	case 'w': return 0x57;
	case 's': return 0x53;
	case 'v': return 0x56;
	case 'a': return 0x41;
	case 'd': return 0x44;
	case VK_RETURN:
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
		return key;
	}
	return key;
}
static int getHWKeyCode(char key){
	switch(key){
	case 'w': return 0x11;
	case 's': return 0x1f;
	case 'v': return 0x2f;
	case 'a': return 0x1e;
	case 'd': return 0x20;
	case VK_RETURN:
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
		return key;
	}
	return key;
}
void Keyboard::tapKey(char key, int delay, int flags){
	char buf[2] = {key, '\0'};
	return tapKey(buf, delay,flags);
}

void Keyboard::tapKey(const char* key, int delay, int flags){
	if(delay){
		for (const char* i = key; *i; i++)
			keybd_event(getVKeyCode(*i), getHWKeyCode(*i),0,NULL);
	}
	if (!flags){
		Sleep(delay ? delay : m_delay );
		for (const char* i = key; *i; i++)
			keybd_event(getVKeyCode(*i), getHWKeyCode(*i),KEYEVENTF_KEYUP,NULL);
		Sleep(delay ? delay : m_delay );
	}
}

void Keyboard::up(int dur){
	
}
void Keyboard::down(int dur){

}
void Keyboard::left(int dur){

}
void Keyboard::right(int dur){

}


