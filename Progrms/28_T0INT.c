#include <LPC214X.H>
#define led 1<<8

__irq void T0_ISR(void){
	IO0PIN = (IO0PIN ^ led);
	T0IR = (T0IR | (0x01));
	VICVectAddr = 0x00;
}

void initPLL(){
	//12MHz to 30MHz
	PLL0CFG = 0x24; //set PSEL=2 and MSEL=5
	PLL0CON = 0x01; //PLL is active but not yet connect
	PLL0FEED = 0xAA;	//FEED sequence
	PLL0FEED = 0x55;	//FEED sequence
	
	while((PLL0STAT & 0x400)==0); //wait for FEED sequence to be inserted
	PLL0CON = 0x03;    //PLL has been active and being connected
	PLL0FEED = 0xAA;		//FEED sequence
	PLL0FEED = 0x55;		//FEED sequence
	VPBDIV = 0x02;   //set PCLK 30MHz
	
}

int main(void){
	IO0DIR = led;
	initPLL();
	VICIntSelect &= ~(1<<14);		//select the irq mode
	VICVectCntl0 = 0x20 | 4; //4 is index of T0
	VICVectAddr0 = (unsigned long)T0_ISR;
	VICIntEnable |= (1<<4);  //Enable T0 to contribute for fiq/irq
	
	T0TCR = 0x02; //timer0 start
	T0CTCR = 0x00; //Config T0 as timer
	T0PR=29; //1us //30KHz
	
	T0MR0 = 100000;  //for 100ms
	T0MCR = 0x03; //Interrupt generate & Reset the TC
	T0TCR = 0x01; 	//Enable TC & PC
	while(1);
	
}
	



