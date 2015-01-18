

#include <stdio.h>

#include "Player.h"
#include "windows.h"

using namespace MarioCart;

int main(){

	Keyboard kb;
	printf("%c = %x\n", 'A', 'A');


	// char up, char down, char left, char right, 
	// char a, char b, char x, char y, char z, char start
	Player p1(VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,
			  'z','x','c','v','b', VK_RETURN);
	Player p2('i','k','j','l',
				'1','2','3','4','5','\\');

	//getc(stdin);
	//return 0;
	while (1)
	{
		kb.tapKey("A");
		Sleep(100);
	}
	return 0;

}