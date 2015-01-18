<<<<<<< HEAD
//#include "stdafx.h"
=======
>>>>>>> 7da31b8514175da386324fc65e4a8a922b79edd6
#pragma once

class Keyboard{
public:
	Keyboard();
	~Keyboard();

	virtual void tapKey(char key, int delay=0, int flags=0);
	virtual void tapKey(const char* key, int delay=0, int flags=0);

	virtual void up(int dur=50);
	virtual void down(int dur=50);
	virtual void left(int dur=50);
	virtual void right(int dur=50);
	
	static int getKeyCode(char key);

private:
	int m_delay;
	long long m_ts;

};