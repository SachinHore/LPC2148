#include <LPC214X.H>

void delay(int time){
	int i,j;
	for(i=0; i<time; i++){
		for(j=0; j<500; j++);
	}
}

int main(){
	
	int i;
	int arr[13]={0x00000007,0x0000038,0x000001c0,0x00000e00};
	
	IODIR0 = 0x00000FFF;
	IOSET0=0;
	while(1){
	for(i=0;i<4;i++){
		IOCLR0 = IOSET0;
		IOSET0 = arr[i];
		delay(200);
	}
}
}
