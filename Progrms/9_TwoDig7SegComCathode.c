#include <LPC214X.H>
#define unit (1<<8)
#define tens (1<<9)

int main(){
	int i,u,t,delay = 300;
	int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	IODIR0 = 0x3ff;
	
	while(1){
		for(t=0; t<10; t++){
			for(u=0; u<10; u++){				
				for(i=0; i<delay*50; i++){
					IOSET0 |= (arr[u] | unit);
					IOCLR0 |= (arr[u] | unit);
					IOSET0 |= (arr[t] | tens);
					IOCLR0 |= (arr[t] | tens);
				}
			}	
		} 
	}
}
