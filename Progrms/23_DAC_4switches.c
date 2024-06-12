#include <LPC214X.H>
int i;

void delay(int time){
	int i,j;
	for(i=0;i<time;i++){
		for(j=0;j<500;j++);
	}
}

void triangular(){
	for(i=0x00;i<=0x3ff;i++){
		DACR=i<<6;
	}
	for(i=0x3ff;i>=0x00;i--){
		DACR=i<<6;
	}
}

void square(){
	DACR=0x00<<6;
	delay(10);
	DACR=0x3ff<<6;
	delay(10);
}

void swatooth(){
		for(i=0x00;i<=0x3ff;i++){
			DACR=i<<6;
		}
}


int sin_wave[42]={512,591,665,742,808,873,926,968,998,1017,1023,1017,998,968,926,873,808,
									742,665,591,512,436,359,282,216,211,151,97,55,25,6,0,6,25,55,97,151,211,216,282,359,436 };
void sine(){
	for(i=0;i<42;i++){
			DACR = sin_wave[i] << 6;
	}	
}


int main(){
	PINSEL1=0x00080000;
	IODIR0=0x0200000;
	
	while(1){
		
		if(!(IO0PIN & 1)){
			triangular();
		}
		else if(!(IO0PIN & 1<<1)){
			square();
		
		}
		else if(!(IO0PIN & 1<<2)){
			swatooth();
		
		}
		else if(!(IO0PIN & 1<<3)){
			sine();
		
		}
		else{
			DACR=0x00<<6;
		}
	}
}

