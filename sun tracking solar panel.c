#include <avr/io.h>
#include <util/delay.h>
#include <avr/lcd4.h>
#define F_CPU 1000000UL
int l1,l2;
void anticlockwise()
{
	//DDRC=0xff;
	PORTC=0x99;
	_delay_ms(1000);
	PORTC=0xcc;
	_delay_ms(1000);
	PORTC=0x66;
	_delay_ms(1000);
	PORTC=0x33;
	_delay_ms(1000);
}
void clockwise()
{
	//DDRC=0xff;
	PORTC=0x33;
	_delay_ms(1000);
	PORTC=0x66;
	_delay_ms(1000);
	PORTC=0xcc;
	_delay_ms(1000);
	PORTC=0x99;
	_delay_ms(1000);
}
void main()
{
	DDRB=0xff;
	lcdini();
	lcdcmd(0x01);
	lcdcmd(0x80);
	lcdstring("Initializing");
	_delay_ms(1000);
	lcdstring(".");
	_delay_ms(1000);
	lcdstring(".");
	_delay_ms(1000);
	lcdstring(".");
	_delay_ms(1000);
	lcdstring(".");
	lcdcmd(0x01);
	lcdcmd(0x80);
	lcdstring("Sun Tracker");
	DDRA=0x00;
	DDRC=0xff;
	PORTC=0x00;
	while(1)
	{
		ADCSRA=0x87;
		ADMUX=0xc0;//Right LDR to A0
		ADCSRA|=(1<<ADSC);
		while((ADCSRA&(1<<ADIF))==0);
		l1=ADC;//Right LDR
		ADCSRA=0x87;
		ADMUX=0xc1;//Left LDR to A1
		ADCSRA|=(1<<ADSC);
		while((ADCSRA&(1<<ADIF))==0);
		l2=ADC;//Left LDR
		if(l1>l2)
		anticlockwise();
		if(l1<l2)
		clockwise();
		if(l1==l2)
		PORTC=0x00;
		else
		PORTC=0x00;
	}
}