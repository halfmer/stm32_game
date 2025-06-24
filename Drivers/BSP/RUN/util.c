#include "./BSP/RUN/util.h"
#include "./BSP/JOYPAD/joypad.h"
#include "./SYSTEM/delay/delay.h"

void KEY0_to_skip(void){
	while(1){
		if(joypad_Scan(0) == START){
		  return;
		}
		else{
			delay_ms(10);
		}
	}
}

