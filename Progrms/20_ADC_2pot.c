#include <LPC214X.H>
#define rs (1<<8)
#define en (1<<9)

void delay(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<500;j++);
	}
}

void lcd_cmd(int cmd){
	IO0SET |= cmd;
	IO0CLR |= rs;  //0 for sending command
	IO0SET |= en;
	delay(20);
	IO0CLR |= en;
	IO0CLR |= cmd;
}

void lcd_data(int data){
	IO0SET |= data;
	IO0SET |= rs;  //1 for sending data
	IO0SET |= en;
	delay(20);
	IO0CLR |= en;
	IO0CLR |= data;
}

void lcd_init(){
	lcd_cmd(0x0f); //switching on lcd
	lcd_cmd(0x0C);	//Display on, cursor off
	//lcd_cmd(0x0E);	//Display on, cursor blink
	lcd_cmd(0x38); //for 8 bit mode 5x7 matrix
	lcd_cmd(0x01); //clearing screen
	lcd_cmd(0x06);	
	lcd_cmd(0x80); //first row first col
}

void lcd_string(char *str){
	while(*str!='\0'){
		lcd_data(*str++);
	}
}

void adc_init(){
	unsigned int temp,result;
	unsigned char a,b,c,d;
	while(!((AD0GDR >> 31) & 1));
	result = AD0GDR;
	result = (( result>>6) & 0x3ff);
	
	temp =result;
		
	a = (temp%10);
	temp = temp/10;
		
	b=(temp%10);
	temp = temp/10;
	
	c=(temp%10);
	temp = temp/10;
	
	d=(temp%10);
	
	
	lcd_data(d+48);
	lcd_data(c+48);
	lcd_data(b+48);
	lcd_data(a+48);
		
	
	delay(500);
	
	AD0GDR &= 0x80000000;//~(1<<31);
}

int main(){	
	IO0DIR = 0x000003ff;
	lcd_init();
	PINSEL1 = 0x05000000;
	while(1){
		AD0CR = 0x01200202;
		lcd_cmd(0x80);
		lcd_string("ADC1 value:");
		adc_init();
		delay(2000);
		AD0CR = 0x01200204;
		lcd_cmd(0xc0);
		lcd_string("ADC2 value:");
		adc_init();
		delay(2000);
	}	
}

