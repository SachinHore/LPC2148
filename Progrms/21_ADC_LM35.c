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
	lcd_cmd(0x38); //for 8 bit mode 5x7 matrix
	lcd_cmd(0x01); //clearing screen
	lcd_cmd(0x06);
}

void lcd_string(char *str){
	while(*str!='\0'){
		lcd_data(*str++);
	}
}

int temp;
char a,b,c,d,e;

void display_adc_values(int result){
	lcd_cmd(0x80);
	lcd_string("ADC values: ");
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
}

void display_temperature_values(int result){
	lcd_cmd(0xc0);
	lcd_string("Temp: ");
	temp =(((3.3/1023)*result)/0.01)*100;
	a = (temp%10);
	temp = temp/10;	
	b=(temp%10);
	temp = temp/10;
	c=(temp%10);
	temp = temp/10;
	d=(temp%10);
	temp = temp/10;
	e=(temp%10);
	lcd_data(e+48);
	lcd_data(d+48);
	lcd_data(c+48);
	lcd_data('.');
	lcd_data(b+48);
	lcd_data(a+48);
	lcd_data(' ');
	lcd_data('C');
	
}

void adc_init(){
	//static int i=0;
	int result;
	AD0CR = 0x01200202;
	while(!((AD0GDR >> 31) & 1));
	result = (( AD0GDR >> 6) & 0x3ff);
	//result = i;  //0x01D1;
	
	display_adc_values(result);
	display_temperature_values(result);
	
	//AD0GDR &= 0x80000000;
	//i=i+20;
}

int main(){	
	IO0DIR = 0x000003ff;
	PINSEL1 = 0x01000000;
	lcd_init();
	while(1){
		adc_init();
	}	
}

