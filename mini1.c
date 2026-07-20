#include<LPC21XX.H>
#define led0 1<<4
#define led1 1<<3
void uart0_conf(void);
unsigned char uart0_rx(void);
void uart0_tx(unsigned char);
int main()
{
char ch;
IODIR0=led0|led1;
uart0_conf();
 while(1)
 {
 ch=uart0_rx();
 uart0_tx(ch);
 if(ch=='1')
 {
 IOCLR0=led0;
 }
 else if(ch=='2')
 {
 IOCLR0=led1;
 }
 else
 {
 IOSET0=led0|led1;
 }
 }
}
void uart0_conf(void)
{
PINSEL0=0X05;
U0LCR=0X83;
U0DLL=97;
U0LCR=0X03;
}
unsigned char uart0_rx(void)
{
while(((U0LSR&(1<<0))==0));
return U0RBR;
}
void uart0_tx(unsigned char d)
{											   
while(((U0LSR&(1<<5))==0));
U0THR=d;
}


