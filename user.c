/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */
void init_adc(void)
{   // set pin as input
    TRISAbits.TRISA1    = 0b1;  //AN1
    TRISAbits.TRISA0    = 0b1;  //AN0 as a digital input
    TRISAbits.TRISA3    = 0b1;  //AN3
    TRISAbits.TRISA5    = 0b1;  //AN4

    TRISBbits.TRISB0    = 0b1;  //AN12
    TRISBbits.TRISB1    = 0b1;  //AN10
    TRISBbits.TRISB2    = 0b1;  //AN8
    TRISBbits.TRISB3    = 0b1;  //AN9
    TRISBbits.TRISB4    = 0b1;  //TX BIT

    TRISBbits.TRISB5    = 0b1;  //AN13

    TRISCbits.TRISC2    = 0b1;  //AN14
    TRISCbits.TRISC3    = 0b1;  //AN15
    TRISCbits.TRISC4    = 0b1;  //AN16
    TRISCbits.TRISC5    = 0b1;  //AN17
    TRISCbits.TRISC6    = 0b0;  //TX1 transmission pin
    TRISCbits.TRISC7    = 0b1;  //AN20


    ANSELAbits.ANSA0    = 0b0;
    ANSELB              = 0b00111111;
    ANSELCbits.ANSC6    = 0b0;
    TXSTA1bits.SYNC     = 0b0; //clear the sync bit
    RCSTA1bits.SPEN     = 0b1; //enable EUSART to automatically set TX1 to an
                             //output
    TXSTA1bits.TXEN     = 0b1; //Enables transmitter circuitry
    TXSTA1bits.BRGH     = 0b0;
    BAUDCON1bits.BRG16  = 0b0;
    SPBRGH1bits.SPBRGH  = 0b00000000;
    SPBRG1bits.SPBRG    = 0b00011001;

    //ANSELAbits.ANSA0    = 0b1;  // set pin as analog
    //ANSELAbits.ANSA1    = 0b1;



    ADCON1bits.PVCFG    = 0b00; // set v+ reference to Vdd
    ADCON1bits.NVCFG    = 0b0;  // set v- reference to GND
    ADCON1bits.CHSN3     = 0b000;// set negative input to GND
    ADCON2bits.ADFM     = 0b1;  // right justify the output
    ADCON2bits.ACQT     = 0b110;// 16 TAD
    ADCON2bits.ADCS     = 0b101;// use Fosc/16 for clock source
    ADCON0bits.ADON     = 0b1;  // turn on the ADC

}
/**
 * Preform an analog to digital conversion.
 * @param channel The ADC input channel to use.
 * @return The value of the conversion.
 */
uint16_t adc_convert(uint8_t channel)
{
    ADCON0bits.CHS      = channel;  // select the given channel
    ADCON0bits.GO       = 0b1;      // start the conversion
    while(ADCON0bits.DONE);         // wait for the conversion to finish
    return (ADRESH<<8)|ADRESL;      // return the result
}
void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */
    init_adc();
    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

