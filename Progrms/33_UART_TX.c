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

void uart_TX_string(char *arr){
	int i;
	for(i=0;arr[i-1] != '\0';i++){
		U0THR = arr[i];
		while(!(U0LSR & 0x20));	//waiting for TX
	}
}

int main(){
	initPLL();
	uart0_init();
	uart_TX_string("Sachin\n\r"); //in uart \n\r new line
	while(1);
}

/*
debug mode on
view Tab > serial window > Uart1 window
*/

