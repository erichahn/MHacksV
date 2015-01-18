<<<<<<< HEAD
//#include "stdafx.h"
=======
>>>>>>> 7da31b8514175da386324fc65e4a8a922b79edd6
#include "Keyboard.h"
#include "windows.h"


Keyboard::Keyboard() : m_delay(20){

}

Keyboard::~Keyboard(){

}

<<<<<<< HEAD
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
=======
static void sendK(char key){

	INPUT ip;

	//Set up the INPUT structure
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0; //We're doing scan codes instead
	ip.ki.dwExtraInfo = 0;

	//This let's you do a hardware scan instead of a virtual keypress
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = 0x1e;  //Set a unicode character to use (A)

	//Send the press
	SendInput(1, &ip, sizeof(INPUT));
	
	//Prepare a keyup event
	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}
static void releaseK(char key){

	INPUT ip;
	
	//Set up the INPUT structure
	ip.type = INPUT_KEYBOARD;
	ip.ki.time = 0;
	ip.ki.wVk = 0; //We're doing scan codes instead
	ip.ki.dwExtraInfo = 0;

	//This let's you do a hardware scan instead of a virtual keypress
	ip.ki.dwFlags = KEYEVENTF_SCANCODE;
	ip.ki.wScan = 0x1e;  //Set a unicode character to use (A)


	//Prepare a keyup event
	ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}
void Keyboard::tapKey(char key, int delay){
>>>>>>> 7da31b8514175da386324fc65e4a8a922b79edd6
	char buf[2] = {key, '\0'};
	return tapKey(buf, delay,flags);
}

<<<<<<< HEAD
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
=======
void Keyboard::tapKey(const char* key, int delay){

	for (const char* i = key; *i; i++)
		//keybd_event(getKeyCode(*i), 0,0,NULL);
		sendK(getKeyCode(*i));
	Sleep(delay ? delay : m_delay );
	for (const char* i = key; *i; i++)
		//keybd_event(getKeyCode(*i), 0,KEYEVENTF_KEYUP,NULL);
		releaseK(getKeyCode(*i));
	Sleep(delay ? delay : m_delay );
>>>>>>> 7da31b8514175da386324fc65e4a8a922b79edd6
}

void Keyboard::up(int dur){
	
}
void Keyboard::down(int dur){

}
void Keyboard::left(int dur){

}
void Keyboard::right(int dur){

}


<<<<<<< HEAD
=======
int Keyboard::getKeyCode(char key){
	switch(key){
	case 'x': return 0x58;
	case 'c': return 0x43;
	case 'y': return 0x59;
	case 'u': return 0x55;
	case 'v': return 0x56;
	case VK_RETURN:
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
		return key;
	}
	return key;
}
>>>>>>> 7da31b8514175da386324fc65e4a8a922b79edd6
