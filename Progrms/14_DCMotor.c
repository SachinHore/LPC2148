#include <LPC214X.H>
#define IN1 1<<0
#define IN2 1<<1
#define EN1 1<<2


int main(){
	IO0DIR = 0x7;
	
	while(1){
		IO0SET = EN1;
		IO0SET = IN1;
		IO0CLR = IN2;
	}
}
