#include <LPC214X.H>
int main(){
	int i;
	PINSEL1=0x00080000;
	IODIR0=0x0200000;
	while(1){
		for(i=0x00;i<=0x3ff;i++){
			DACR=i<<6;
		}
		for(i=0x3ff;i>=0x00;i--){
			DACR=i<<6;
		}
	}
}

