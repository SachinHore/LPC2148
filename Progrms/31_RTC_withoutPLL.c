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
	IO0SET=cmd;
	IO0CLR |= rs;  //0 for sending command
	IO0SET |= en;
	delay(20);
	IO0CLR |= en;
	IO0CLR |= cmd;
}

void lcd_data(int data){
	IO0SET=data;
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


void set_Time(){		//RTC Init
	//PREINT = 456;
	//PREFRAC = 25024;
	CCR = 0x02;				//clk tick counter are reset
	
	HOUR = 12;
	MIN = 59;
	SEC = 56;
	CCR = 0x11;		//Clock enable, CTC take clk from RTC pins
	//CCR = 0x01;		//clk enabled, clk from internal FREQ
}

void Time(){
	lcd_cmd(0xc0); //2nd row 1st pos
	lcd_data(48+(HOUR/10));
	lcd_data(48+(HOUR%10));

	
	lcd_data(':');
	lcd_data(48+(MIN/10));
	lcd_data(48+(MIN%10));
	lcd_data(':');
	lcd_data(48+(SEC/10));
	lcd_data(48+(SEC%10));
	

}

int main(){
	IO0DIR = 0xFFF;
	lcd_init();
	set_Time();
	lcd_string("HH:MM:SS");
	
	while(1){
		Time();
	}
	
}

