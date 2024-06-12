#include <LPC214X.H>

void delay(int time){
	int i,j;
	for(i=0; i<time; i++){
		for(j=0; j<500; j++);
	}
}

int main(){
	
	int i;
	int arr[13]={0x00000003,0x00000006,0x0000000C,0x00000018,0x00000030,0x00000060,0x000000C0,0x00000180,0x00000300,0x00000600,0x00000C00,0x00000801};
	
	IODIR0 = 0x00000FFF;
	IOSET0 = 0;
	
	while(1){
	for(i=0;i<12;i++){
		IOCLR0 = IOSET0;
		IOSET0 = arr[i];
		delay(100);
	}
}
	
}
