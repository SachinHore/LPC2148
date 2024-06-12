#include <LPC214X.H>

void delay(int time){
	int i,j;
	for(i=0; i<time; i++){
		for(j=0; j<500; j++);
	}
}

int main(){
	
	int i;
	int arr[13]={0x00000000,0x00000001,0x00000002,0x00000004,0x00000008,0x00000010,0x00000020,
							0x00000040,0x00000080,0x00000100,0x00000200,0x00000400,0x00000800,};
	
	IODIR0 = 0x00000FFF;
	
	for(i=0;i<13;i++){
		IOCLR0 |= arr[i];
		IOSET0 |= arr[i+1];
		delay(200);
	}
}
