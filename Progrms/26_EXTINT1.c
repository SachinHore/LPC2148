#include <LPC214X.H>
#define led (1<<16)

void DelayMS(unsigned int count){
	unsigned int i,j;
	for(i=0;i<count;i++){
		for(j=0;j<count;j++);
	}
}

void EXTINT_Serve1(void)__irq{
	IO1SET = led;
	DelayMS(1000);
	IO1CLR = led;
	DelayMS(1000);
	EXTINT |= 2;
	VICVectAddr=0;
}

void ExtInt_Init1(){
	PINSEL0 = 0x20000000;		//Enable EINT1 on P014
	VICIntSelect &= ~(1<<15);		//select the irq mode
	VICVectCntl0 = 0x20 |15; //15 is index of EINT1
	VICVectAddr0 = (unsigned long) EXTINT_Serve1;
	VICIntEnable |= (1<<15);  //Enable INT1 to contribute for fiq/irq
	
	//EXTINT=0x02;  //EXTINT !=1<<1
	EXTMODE |=2;		//Edge sensitive mode on EINT1
	EXTPOLAR = 0;		//Falling edge sensitive
	//EXTPOLAR &= ~(1<<1); //optional
}

int main(){
	IO1DIR = led;
	
	ExtInt_Init1();  //Initialize Interrupt
	while(1);
	
}
	
