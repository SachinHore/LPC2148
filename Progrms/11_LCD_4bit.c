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

int main(){
	char name[]="Hello";
	
	IO0DIR |= 0x3f0;
	
	lcd_init();

	while(1){		
		lcd_string(name);
		lcd_cmd(0xc0);	//2nd row 1st col
		lcd_string("Sachin Hore");
		while(1){
			//lcd_cmd(0x1c); //rotate left to right
			delay(100);
		}
	}
	
}

