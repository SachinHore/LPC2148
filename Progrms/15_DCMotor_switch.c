#include <LPC214X.H>
#define IN1 1<<0
#define IN2 1<<1
#define EN1 1<<2
#define sw1 (1<<3)



int main(){
	IO0DIR |= 0x7;
	IO0DIR &= (~sw1);
	IO0SET = EN1;
	while(1){
		if((IO0PIN & sw1) == 0){
			IO0SET = IN1;
			IO0CLR = IN2;
		}
		else{
			IO0SET = IN2;
			IO0CLR = IN1;
		}
		
	}
}
