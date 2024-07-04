#include <LPC214X.H>
#include<math.h>

#define unit (1<<8)
#define tens (1<<9)
#define hunderd (1<<10)
#define thousand (1<<11)
#define x 30
#define y 100

#define LED1 (1<<12)
#define LED2 (1<<13)

int j=0,arr1[100],count=8;
int i;
int s1=0,s2=0,s3=0,s4=0,no=0,n=0;
int arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void initPLL(){
	//12MHz to 30MHz
	PLL0CFG = 0x24; 	//set PSEL=2 and MSEL=5
	PLL0CON = 0x01; 	//PLL is active but not yet connect
	PLL0FEED = 0xAA;	//FEED sequence
	PLL0FEED = 0x55;	//FEED sequence
	
	while((PLL0STAT & 0x400)==0); //wait for FEED sequence to be inserted
	PLL0CON = 0x03;    						//PLL has been active and being connected
	PLL0FEED = 0xAA;							//FEED sequence
	PLL0FEED = 0x55;							//FEED sequence
	VPBDIV = 0x01;  							//set PCLK 60MHz
	
}

void delay(int delay){
	int i,j;
	for(i=0;i<=delay;i++)
		for(j=0;j<=10;j++);
}

__irq void T0_ISR(void){
	/*
	if(IO0SET & LED1){
		IO0CLR |= LED1;
	}else{
		IO0SET |= LED1;
	}
	*/
	if(no < count){
	no++;
	n= arr1[no];
	s1 = n%10;
	n = n/10;
	s2 = n%10;
	n = n/10;
	s3 = n%10;
	n = n/10;
	s4 = n%10;
	}
	T0IR = (T0IR | (0x01));
	VICVectAddr = 0x00;
	
}

void init_t0(){
	VICIntSelect &= ~(1<<14);		//select the irq mode
	VICVectCntl0 = 0x20 | 4; //4 is index of T0
	VICVectAddr0 = (unsigned long)T0_ISR;
	VICIntEnable |= (1<<4);  //Enable T0 to contribute for fiq/irq
	
	T0TCR = 0x02; //timer0 start
	T0CTCR = 0x00; //Config T0 as timer
	T0PR=59999; //1ms //1KHz
	
	T0MR0 = 500;  //for 4ms
	T0MCR = 0x03; //Interrupt generate & Reset the TC
	T0TCR = 0x01; 	//Enable TC & PC
}


__irq void T1_ISR(void){
			T1TCR = 0x02;
	
			IO0SET |= thousand;
			IO0SET=arr[s1];
			IOCLR0 |= unit;
			delay(x);
	
			IO0CLR=arr[s1];
			IO0SET |= unit;
			IO0SET=arr[s2];
			IOCLR0 |= tens;
			delay(x);
	
			IO0CLR=arr[s2];
			IO0SET |= tens;
			IO0SET = arr[s3];
			IOCLR0 |= hunderd;
			delay(x);
	
			IO0CLR=arr[s3];
			IO0SET |= hunderd;
			IO0SET=arr[s4];
			IOCLR0 |= thousand;
			delay(x);
			IO0CLR=arr[s4];
	
	//T1IR = (T1IR | (0x01));
	//VICVectAddr = 0x00;
	T1TC=0;
	T1TCR = 0x01;
}

void init_t1(){
	VICIntSelect &= ~(1<<15);		//select the irq mode
	VICVectCntl1 = 0x20 | 5; //5 is index of T1
	VICVectAddr1 = (unsigned long)T1_ISR;
	VICIntEnable |= (1<<5);  //Enable T0 to contribute for fiq/irq
	
	T1TCR = 0x02; //timer0 start
	T1CTCR = 0x00; //Config T1 as timer
	T1PR=1000; //1ms //1KHz
	
	T1MR0 = 7;  //for 4ms
	T1MCR = 0x03; //Interrupt generate & Reset the TC
	T1TCR = 0x01; 	//Enable TC & PC
}

int fun(int n){
	int arr[4],size=0,i;
	int sum=0;	
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


int main(){
	
	IODIR0 = 0xffff;
	init_t1();
	init_t0();
	
	IO0CLR |= 0x0ff;
	for(i=1;i<10000;i++){
			if(fun(i)==i){
				arr1[count]=i;
				count++;
			}	
	}
	while(1){
		if(no==count-1){
			no=0;
		}
		
	}
}
