#include <LPC214X.H>
#define IN1 1<<0
#define IN2 1<<1
#define EN1 (1<<2)
#define sw1 (1<<3)

#define EN2 (1<<4)
#define IN3 1<<5
#define IN4 1<<6
#define sw2 (1<<7)


int main(){
	IO0DIR = 0x77;
	IO0DIR &= ((~sw1) | (~sw2));
	IO0SET = EN1 | EN2;
	while(1){
		
		if((IO0PIN & sw1) == 0){
			IO0SET = IN1;
			IO0CLR = IN2;
		}
		else{
			IO0SET = IN2;
			IO0CLR = IN1;
		}
		
		if((IO0PIN & sw2) == 0){
			IO0SET = IN3;
			IO0CLR = IN4;
		}
		else{
			IO0SET = IN4;
			IO0CLR = IN3;
		}
	}
}
