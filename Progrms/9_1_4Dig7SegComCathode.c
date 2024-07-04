#include <LPC214X.H>
#include<math.h>
#define unit (1<<8)
#define tens (1<<9)
#define hunderd (1<<10)
#define thousand (1<<11)
#define x 3
#define y 100

void delay(int delay){
	int i,j;
	for(i=0;i<=delay;i++)
		for(j=0;j<=10;j++);
}


void display_4Digit_no(int n,int delay1){
	int i;
	int s1,s2,s3,s4;
	int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
		
	s1 = n%10;
	n = n/10;
	s2 = n%10;
	n = n/10;
	s3 = n%10;
	n = n/10;
	s4 = n%10;
	IO0SET |= 0xf00;		
	for(i=0;i<delay1*20;i++){

			IO0CLR |= 0x0ff;
		
			IO0SET |= thousand;
			IOCLR0 |= unit;
			IO0SET=arr[s1];
			delay(x);
			IO0CLR=arr[s1];
			
			IO0SET |= unit;
			IOCLR0 |= tens;
			IO0SET=arr[s2];
			delay(x);
			IO0CLR=arr[s2];
			
			IO0SET |= tens;
			IOCLR0 |= hunderd;
			IO0SET=arr[s3];
			delay(x);
			IO0CLR=arr[s3];
			
			IO0SET |= hunderd;
			IOCLR0 |= thousand;
			IO0SET=arr[s4];
			delay(x);
			IO0CLR=arr[s4];
	}
	//IO0CLR |= 0xf00;
}


/*
int fun(int n){
	int arr[4],size=0,i;
	volatile int sum=0;	
	while(n!=0){
		arr[size] = n%10;
		n=n/10;
		size++;
	}
	for(i=0;i<size;i++){
		sum=sum + pow(arr[i],size);
	}
	return sum;
}
*/

int main(){
	int i,arr[100],count=0;
	IODIR0 = 0xfff;
	count=0;
	/*
	for(i=0;i<1000;i++){
		if(fun(i)==i){
			arr[count]=i;
			count++;
		}	
	}
*/
	while(1){
		for(i=0;i<=100;i++){//count;i++){
				display_4Digit_no(i,y);//arr[i],y);
		}
	}
}
