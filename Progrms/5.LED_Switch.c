#include <LPC214X.H>
# define led1 1<<19
# define led2 1<<20
#define sw1 1<<8
#define sw2 1<<14

int main(){
	
	IODIR0 |= led1;
	IODIR0 |= led2;
	IODIR0 &= ~(sw1);
	IODIR0 &= ~(sw2);
	
	while(1){
	if((IO0PIN & sw1) == 0){
		IO0SET |= led1;
	}else{
		IO0CLR |= led1;
	}
	if((IO0PIN & sw2) == 0){
		IO0SET |= led2;
	}else{
		IO0CLR |= led2;
	}
	}

}
