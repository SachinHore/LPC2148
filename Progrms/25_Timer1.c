#include <LPC214X.H>
void initPLL(){
	//12MHz to 60MHz
	PLL0CFG = 0x24; //set PSEL=2 and MSEL=5
	PLL0CON = 0x01; //PLL is active but not yet connect
	PLL0FEED = 0xAA;	//FEED sequence
	PLL0FEED = 0x55;	//FEED sequence
	
	while((PLL0STAT & 0x400)==0); //wait for FEED sequence to be inserted
	PLL0CON = 0x03;    //PLL has been active and being connected
	PLL0FEED = 0xAA;		//FEED sequence
	PLL0FEED = 0x55;		//FEED sequence
	VPBDIV = 0x01;   //set PCLK same as FCCLK
	
}

void delay(unsigned int us){
	
	T1CTCR = 0x00; //Config T0 as timer
	T1PR=59; //1us //1MHz
	T1TCR = 0x01; //timer0 start
	while(T1TC < us);
	T1TC =0;
	T1TCR=0x00;
}



int main(){
	IO0DIR=1<<0;
	initPLL();
	while(1){
		IO0SET = 1;
		delay(100);
		IO0CLR = 1;
		delay(100);
	}
	
	
}
	
