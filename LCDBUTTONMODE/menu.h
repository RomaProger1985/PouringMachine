
#ifndef MENU_H_
#define MENU_H_

#include "main.h"

typedef enum {
	MENU_STATE_IDLE = 0,
	MENU_STATE_WAIT,
	MENU_STATE_SETING,
	MENU_STATE_STARTING,
	MENU_STATE_STARTED,
	MENU_STATE_MANUAL,
}MENU_StateTypeDef;

typedef enum {
	RinghtSeparator_On = 0,
	LeftSeparator_On,
	Lift_On,
	Value_On,
	Cover_On,
}Manual_State;

typedef enum {
	None = 0,
	BootelSpaising,
	InBootleDelau,
	ValyeDelay,
	liftdownDelay,
	BottleOutDelay,
	AfterLiftUpDelay,
	AfterLiftDownDelay,
}Set_ParametrsTypeDef;

unsigned char setingNavigation;
MENU_StateTypeDef menu_state;

void MenuProcess(void);

#endif /* MENU_H_ */