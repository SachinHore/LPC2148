#include <LPC214X.H>
#define rs (1<<25)
#define en (1<<26)

void delay(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<500;j++);
	}
}

void lcd_cmd(int cmd){
	IO0SET = cmd<<16;
	IO0CLR |= rs;  //0 for sending command
	IO0SET |= en;
	delay(10);
	IO0CLR |= en;
	IO0CLR |= cmd<<16;
}

void lcd_data(int data){
	IO0SET=data<<16;
	IO0SET |= rs;  //1 for sending data
	IO0SET |= en;
	delay(10);
	IO0CLR |= en;
	IO0CLR |= data<<16;
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



int main(){
	int i;
	char name[]="Hello world";
	IO0DIR |= 0x6ff<<16;
	lcd_init();
	while(1){
		for(i=0;name[i]!='\0';i++){
			lcd_data(name[i]);	
		}
		while(1){
			lcd_cmd(0x1c); //rotate left to right
			delay(100);
		}
	}
	
}

