#include <LPC214X.H>
#define rs (1<<8)
#define en (1<<9)

#define r1 (1<<20)
#define r2 (1<<21)
#define r3 (1<<22)
#define r4 (1<<23)

#define c1 (1<<16)
#define c2 (1<<17)
#define c3 (1<<18)
#define c4 (1<<19)


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
	delay(10);
	IO0CLR |= en;
	IO0CLR |= cmd;
}

void lcd_data(int data){
	IO0SET=data;
	IO0SET |= rs;  //1 for sending data
	IO0SET |= en;
	delay(10);
	IO0CLR |= en;
	IO0CLR |= data;
}

void lcd_init(){
	lcd_cmd(0x0f); //switching on lcd
	//lcd_cmd(0x0C);	//Display on, cursor off
	lcd_cmd(0x0E);	//Display on, cursor blink
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

char keypad(){
	
	while(1){
		
		IO1CLR = c1;
		IO1SET = (c2 | c3 | c4);
		if(!(IO1PIN & r1)){
			return '7';
		}
		if(!(IO1PIN & r2)){
			return '4';
		}
		if(!(IO1PIN & r3)){
			return '1';
		}
		if(!(IO1PIN & r4)){
			return 'c';
		}
		
		IO1CLR = c2;
		IO1SET = (c1 | c3 | c4);
		if(!(IO1PIN & r1)){
			return '8';
		}
		if(!(IO1PIN & r2)){
			return '5';
		}
		if(!(IO1PIN & r3)){
			return '2';
		}
		if(!(IO1PIN & r4)){
			return '0';
		}
		
		IO1CLR = c3;
		IO1SET = (c1 | c2 | c4);
		if(!(IO1PIN & r1)){
			return '9';
		}
		if(!(IO1PIN & r2)){
			return '6';
		}
		if(!(IO1PIN & r3)){
			return '3';
		}
		if(!(IO1PIN & r4)){
			return '=';
		}
		
		IO1CLR = c4;
		IO1SET = (c1 | c2 | c3);
		if(!(IO1PIN & r1)){
			return '/';
		}
		if(!(IO1PIN & r2)){
			return 'x';
		}
		if(!(IO1PIN & r3)){
			return '-';
		}
		if(!(IO1PIN & r4)){
			return '+';
		}
	}
}

int main(){

	IO0DIR |= 0x3ff;
	IO1DIR |= (0xf << 16);
	IO1DIR &= ~(0xf << 20);
	
	lcd_init();

	while(1){	
		
		lcd_data(keypad());
		while((IO1PIN &(0xf<<20)) != (0xf<<20));
		delay(100);
	}
	
}

