#include <LPC214X.H>

void delay(){
	int i,j;
	for(i=0; i<500; i++){
		for(j=0; j<500; j++);
	}

}

int main(){
	
	IODIR0 |= (1<<4) | (1<<10);
	
	while(1){
		IOSET0 |= (1<<4) | (1<<10);
		delay();
		IOCLR0 |= (1<<4) | (1<<10);
		delay();
	}
	
	return 0;
}