#include <LPC214X.H>
#define LED1 (1<<2)
#define LED2 (1<<3)
#define rs (1<<8)
#define en (1<<9)

void delay(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<500;j++);
	}
}

void lcd_cmd(int cmd){
	int temp;
	IO0CLR |= rs;  //0 for sending command
	
	temp = cmd & 0xF0;
	IO0SET |= temp;
	IO0SET |= en;
	delay(10);
	IO0CLR |= en;
	IO0CLR |= temp;
	
	temp = (cmd & 0x0F)<<4;
	IO0SET |= temp;
	IO0SET |= en;
	delay(10);
	IO0CLR |= en;
	IO0CLR |= temp;
}

void lcd_data(int data){
	int temp;
	IO0SET |= rs;  //1 for sending data
	
	temp = data & 0xF0;
	IO0SET |= temp;
	IO0SET |= en;
	delay(10);
	IO0CLR |= en;
	IO0CLR |= temp;
	
	temp = (data & 0x0F)<<4;
	IO0SET |= temp;
	IO0SET |= en;
	delay(10);
	IO0CLR |= en;
	IO0CLR |= temp;
}

void lcd_init(){
	lcd_cmd(0x02); //for 4 bit mode 5x7 matrix
	lcd_cmd(0x28);
	//lcd_cmd(0x0f); //switching on lcd
	lcd_cmd(0x0C);	//Display on, cursor off
	//lcd_cmd(0x0E);	//Display on, cursor blink
	lcd_cmd(0x01); //clearing screen
	lcd_cmd(0x80); //first row first col
}

void lcd_string(char *str){
	while(*str!='\0'){
		lcd_data(*str++);
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

__irq void UART_RX_ISR(void){
	char temp = U0RBR;
		lcd_data(temp);
}

void init_interrupt(){
	VICIntSelect &= ~(1<<6);		//select the irq mode
	VICVectCntl0 = 0x20 | 6; //4 is index of T0
	VICVectAddr0 = (unsigned long)UART_RX_ISR;
	VICIntEnable |= (1<<6);  //Enable UART0 to contribute for fiq/irq
	
	U0IER = 0x01;
}


int main(){
	IO0DIR |= 0x3f0;
	initPLL();
	lcd_init();
	uart0_init();
	init_interrupt();
	
	while(1);
}

/*
debug mode on
view Tab > serial window > Uart1 window
*/

