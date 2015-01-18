#ifndef LEAPINTERFACE_H
#define LEAPINTERFACE_H
#include "../../player.h"

enum Position{Left=0, Right=1, Forward=2, Backward=3, Centered};
enum Grip{Closed=0, Open=1, Nuetral=2};

using namespace MarioCart;

struct myleap
{
	Position posX;
	Position posZ;
	Grip grip;
};

class leapInterface
{

public:
	leapInterface();
	void doGame(myleap leap);
	myleap tempLeap;
	Player human;

private:

	
};
#endif