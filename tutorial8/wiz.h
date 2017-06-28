// This file came from Pickle's Wiz3D development pack. 
// I removed a lot of the SDL and keyboard related functionality.
// Thanks Pickle!
// Be sure to call WIZ_Init & WIZ_Close as appropriate

#ifndef __WIZ_H__
#define __WIZ_H__

#ifndef WIN32

int WIZ_Init( void );
void WIZ_Close( void );

#define BIT(number) (1<<(number))

enum {
	BTN_A = BIT(20),
	BTN_B = BIT(21),
	BTN_X = BIT(22),
	BTN_Y = BIT(23),
	BTN_L = BIT(7),
	BTN_R = BIT(6),
	BTN_MENU = BIT(9),
	BTN_SELECT = BIT(8),
	BTN_LEFT = BIT(16),
	BTN_RIGHT = BIT(17),
	BTN_UP = BIT(18),
	BTN_DOWN = BIT(19),
	BTN_VOLUP = BIT(10),
	BTN_VOLDOWN = BIT(11)
};

bool HW_ButtonPushed(int Button);

#endif

#endif // __WIZ_H__
