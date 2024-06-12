#include <LPC214X.H>

void delay(int time){
	int i,j;
	for(i=0; i<time; i++){
		for(j=0; j<500; j++);
	}
}

int main(){
	int i,j;
	int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};	
	IODIR0 = 0xffff;
	
	while(1){
		for(i=0; i<10; i++){
			IOSET0 |= arr[i];
			for(j=0; j<10; j++){
				IOSET0 |= arr[j]<<8;
				delay(300);
				IOCLR0 |= arr[j]<<8;
			}	
			IOCLR0 |= arr[i];
		}
	}
}
