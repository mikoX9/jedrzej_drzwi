#include <avr/io.h>
#include <util/delay.h>


#define OPEN 1
#define CLOSE 0


#define UBRRVAL 51

void usart_init(void);
void sendbyte(unsigned char MSG);
unsigned char receivebyte(void);




int main(void)
{
    usart_init();
    
    // selenoid:
    DDRD |=(1<<PD7);
    
    unsigned char msg;

    while(1)
    {
        msg = receivebyte();
        switch(msg)
        {
            case OPEN:
                
                PORTD |=(1<<PD7);
                _delay_ms(10000);
                PORTD &=~(1<<PD7);
                break;
            case CLOSE:
                
                break;
            default:
                break;
        }   
    }
}


void usart_init(void){
	UBRR0H= (unsigned char)(UBRRVAL>>8);   //high byte
    UBRR0L=(unsigned char)UBRRVAL;     			//low byte
    UCSR0B |= (1<<TXEN0) | (1<<RXEN0);		//Enable Transmitter and Receiver
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00); 	//Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size
}

void sendbyte(unsigned char MSG){
    while((UCSR0A&(1<<UDRE0)) == 0);     // Wait if a byte is being transmitted
    UDR0 = MSG; 
}

void sendstr(unsigned char *s){
	unsigned char i = 0;
	while(s[i] != '\0'){
	 sendbyte(s[i]);
	 i++;
	 }
}

unsigned char receivebyte(void){
	while(!(UCSR0A & (1<<RXC0)));
		return UDR0;
}