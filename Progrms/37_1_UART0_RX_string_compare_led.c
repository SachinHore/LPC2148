#include <LPC214X.H>
#include <string.h>
#define LED (1<<2)

char str[10]="";
char i=0;

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
	VPBDIV = 0x01;   //set PCLK 60MHz
	
}

__irq void T0_ISR(void){
		T0TCR |= 0x03;		//timer and counter enable and reset and timer stop
		T0IR = (T0IR | (0x01));
	
		str[i] = '\0';
		if(!(strcmp("sachin",str))){
				IO0SET |= LED;
		}
		if(!(strcmp("hore",str))){
			IO0CLR |= LED;
		}
		strcpy(str,"");
		i=0;		
}

void init_t0(){
	VICIntSelect &= ~(1<<14);		//select the irq mode
	VICVectCntl0 = 0x20 | 4; //4 is index of T0
	VICVectAddr0 = (unsigned long)T0_ISR;
	VICIntEnable |= (1<<4);  //Enable T0 to contribute for fiq/irq
	
	T0TCR = 0x02; //timer0 start
	T0CTCR = 0x00; //Config T0 as timer
	T0PR=59999; //1ms //1KHz
	
	T0MR0 = 200;  //for 200ms
	T0MCR = 0x03; //Interrupt generate & Reset the TC
	T0TCR = 0x01; 	//Enable TC & PC
}


__irq void UART_RX_ISR(void){
		char temp = U0RBR;
		str[i] = temp;
		i++;
		T0TC = 0;		// TC reset to 0
		T0TCR = 0x01;		//timer and counter enable and reset and timer start
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

void init_uart0_interrupt(){
	VICIntSelect &= ~(1<<6);		//select the irq mode
	VICVectCntl1 = 0x20 | 6; //4 is index of T0
	VICVectAddr1 = (unsigned long)UART_RX_ISR;
	VICIntEnable |= (1<<6);  //Enable UART0 to contribute for fiq/irq
	U0IER = 0x01;
}



int main(void){
	IO0DIR |= LED;
	initPLL();
	uart0_init();
	init_uart0_interrupt();
	init_t0();
	while(1);
}
	



