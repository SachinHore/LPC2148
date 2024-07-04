#include <LPC214X.H>
#define LED1 (1<<2)
#define LED2 (1<<3)

__irq void UART_RX_ISR(void){
	char temp = U0RBR;
		switch(temp){
			case '1' : IO0SET |= LED1;
								break;
			case '0' : IO0CLR |= LED1;
								break;
			case 'a' : IO0SET |= LED2;
								break;
			case 'b' : IO0CLR |= LED2;
								break;
		}
}

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
	//VPBDIV = 0x00;   //set PCLK 15MHz
	VPBDIV = 0x01;   //set PCLK 60MHz
}

void uart0_init(){
	PINSEL0=0x05;	//config the TX & RX pins 
	U0LCR=0x83;		//8bits, no parity 1 stop bit, dlab=1
	//U0DLL=0x61;		//9600 Baud rate (15MHZ)
	//U0DLM=0x00;
	U0DLL=0x86;		//9600 Baud rate (60MHZ)
	U0DLM=0x01;
	U0LCR=0x03;		//8bits, no parity 1 stop bit, dlab=0
}

void init_interrupt(){
	VICIntSelect &= ~(1<<6);		//select the irq mode
	VICVectCntl0 = 0x20 | 6; //4 is index of T0
	VICVectAddr0 = (unsigned long)UART_RX_ISR;
	VICIntEnable |= (1<<6);  //Enable UART0 to contribute for fiq/irq
	
	U0IER = 0x01;
}


int main(){
	IO0DIR |= LED1;
	IO0DIR |= LED2;
	
	initPLL();
	uart0_init();
	init_interrupt();
	
	while(1);
}

/*
debug mode on
view Tab > serial window > Uart1 window
*/

