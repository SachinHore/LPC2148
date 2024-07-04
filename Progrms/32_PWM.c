#include <LPC214X.H>
void pwm_init(){
	PINSEL0 = 0x8002;		//PWM1,PWM2 configuration
	PWMPCR = 0x600; 		//PWM1&2 o/p enabled
	//PWMTCR = 0x0A;		//reset TC & PC, disabled timer, Enabled PWM
	PWMTCR = 0x02;		//reset TC & PC, disabled timer
	PWMMR0=1500000;			//period register 150KHz
	PWMTCR = 0x09;		//PWM & counter enabled
	PWMMCR=0x02;		//PWMMR0=0 if PWMMR=PWMTC
	
}

int main(){
	pwm_init();
	while(1){
		PWMMR1=750000;	//50%
		PWMMR2=45000;	//30%
		PWMLER=0x06;
	}
}
