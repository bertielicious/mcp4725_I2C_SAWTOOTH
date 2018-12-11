/*
 * File:   main.c
 * Author: Phil Glazzard
 *
 * Created on 27 November 2018, 14:08
 */

#include "config.h"
#include <xc.h>
#include "stdio.h"
#include "main.h"
#include "init_ports.h"
#include "config_osc.h"
#include "set_usart.h"
#include "putch.h"
#include "dac_write.h"

void main(void) 
{
    unsigned char x, y = 0;
    init_ports();
    config_osc();
    set_usart();
    printf("MCP4725 12-bit DAC controlled over i2c\n");
    
    TRISBbits.TRISB4 = 1;   // SDA is an input 
    TRISBbits.TRISB6 = 1;   // SCL is an input
    SDA = 1;                // bus idle condition
    SCL = 1;
    
    RED_LED = 1;            // RED LED lit shows that code is running
    
    /*Enable i2c master mode, SCL = FOSC/(4 * (SPPADD + 1))*/
    SSPCON1bits.SSPEN = 1;       // enables i2c SDA and SCL pins
    SSPCON1bits.SSP1M3 = 1;
    SSPCON1bits.SSP1M2 = 0;
    SSPCON1bits.SSP1M1 = 0;
    SSPCON1bits.SSP1M0 = 0;
    SSPADD = 0x09;              // SCL = 100kHz, Fosc = 4MHz
                                // SSPADD = (Fosc/(4 * SCL)) - 1
    
    PIR1bits.SSP1IF = 0;    // clear the SSP interrupt flag 
        
    
    while(1)
    {
        RED_LED = ~RED_LED;                 // diagnostic LED to show code is running
       // dac_write(0xC0,0x40,0xf0,0xF0);
      /*  for (x = 0; x <=255; x++)
        {
            dac_write(0xC0,0x40,x,0x00);
            x++;
        }
        x = 0;*/
        while(x <254)
        {
           // printf("%d\n", x);
            dac_write(0xC0,0x40,x,0x00);
            x++;
        }
        while(x > 0)
        {
          //  printf("%d\n", x);
            dac_write(0xC0,0x40,x,0x00);
            x--;
        }
        
        
     /*   SSPCON2bits.SEN = 1;                // i2c start condition initiated
        while(!PIR1bits.SSP1IF);            // wait for the start condition to finish, indicated by SSPIF going high
      
        PIR1bits.SSP1IF = 0;                // clear the SSP interrupt flag
        SSP1BUF = 0xC0;                     // load address byte of MCP4725 (0x60) and the R/W bit which is write = 0 wgich is 0xC0
        while(!SSPSTATbits.BF);             // wait for all 8 bits to be transmitted
        while(SSPCON2bits.ACKSTAT == 1);    // wait for ACK bit to be received by the uC
        while(!PIR1bits.SSP1IF);            // wait for SSPIF bit to be set at end of 9th clock cycle
        PIR1bits.SSP1IF = 0;                // clear the SSP interrupt flag
        SSPBUF = 0x40;                      // load com_pdm byte (communication_power down mode bits )
        while(!SSPSTATbits.BF);             // wait for all 8 bits to be transmitted
        while(SSPCON2bits.ACKSTAT == 1);    // wait for ACK bit to be received by the uC
        while(!PIR1bits.SSP1IF);            // wait for SSPIF bit to be set at end of 9th clock cycle
        PIR1bits.SSP1IF = 0;                // clear the SSP interrupt flag
        SSPBUF = 0xFF;                      // load dac_register_hi byte (bits 12 to 4 of 12 bit data )
        while(!SSPSTATbits.BF);             // wait for all 8 bits to be transmitted
        while(SSPCON2bits.ACKSTAT == 1);    // wait for ACK bit to be received by the uC
        while(!PIR1bits.SSP1IF);            // wait for SSPIF bit to be set at end of 9th clock cycle
        PIR1bits.SSP1IF = 0;                // clear the SSP interrupt flag
        SSPBUF = 0xF0;                      // load dac_register_lo byte (bits 3 to 0 of 12 bit data )
        while(!SSPSTATbits.BF);             // wait for all 8 bits to be transmitted
        while(SSPCON2bits.ACKSTAT == 1);    // wait for ACK bit to be received by the uC
        while(!PIR1bits.SSP1IF);            // wait for SSPIF bit to be set at end of 9th clock cycle
        PIR1bits.SSP1IF = 0;                // clear the SSP interrupt flag
        SSPCON2bits.RSEN = 1;                // issue stop condition
        while(SSPCON2bits.RSEN = 1);         // wait for stop condition to complete*/
    }
    
    
}
