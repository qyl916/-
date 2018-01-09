#include<reg51.h>
#include"beeper.h"


sbit en = P1 ^ 7;
sbit mode = P1 ^ 6;
sbit sel = P1 ^ 5;

void BEEPER_Set_Tune(signed char tune){
	en = 1, mode = 0, sel = 0;
	P2 = tune + 48;
	en = 0;
}

void BEEPER_Set_Length(unsigned char length){
	en = 1, mode = 0, sel = 1;
	P2 = length;
	en = 0;
}

void BEEPER_Stop(void){
	en = 1, mode = 1, sel = 1;
	en = 0;
}

void BEEPER_Start(void){
	BEEPER_Stop();
	en = 1, mode = 1, sel = 0;
	en = 0;
}
