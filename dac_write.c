
#include <pic16f1459.h>

void dac_write (unsigned char addr_byte, unsigned char control_byte, unsigned char hi_data_byte, unsigned char lo_data_byte)
{
    SSPCON2bits.SEN = 1;
    while(SEN);
    PIR1bits.SSP1IF = 0;
    
    SSPBUF = addr_byte;
    while(!SSP1IF);
    PIR1bits.SSP1IF = 0;
    if(SSPCON2bits.ACKSTAT)
    {
        SSPCON2bits.PEN = 1;
        while(PEN);
        return;
    }
    
    SSPBUF = control_byte;
    while(!SSP1IF);
    PIR1bits.SSP1IF = 0;
    if(SSPCON2bits.ACKSTAT)
    {
        SSPCON2bits.PEN = 1;
        while(PEN);
        return;
    }
    
    SSPBUF = hi_data_byte;
    while(!SSP1IF);
    PIR1bits.SSP1IF = 0;
    if(SSPCON2bits.ACKSTAT)
    {
        SSPCON2bits.PEN = 1;
        while(PEN);
        return;
    }
    
    SSPBUF = lo_data_byte;
    while(!SSP1IF);
    PIR1bits.SSP1IF = 0;
    SSPCON2bits.PEN = 1;
    while(PEN);
}
