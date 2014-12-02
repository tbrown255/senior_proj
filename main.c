/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include <string.h>
#include <stdio.h>
#include <math.h>
/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    uint8_t prev_value, output, sensor, mux, go = 0;                 // variable to hold ADC conversion result in
    uint16_t adc_value;
    uint8_t tx_val, tx_int;
    float new_value;
    char mux1 = 0, mux2 = 0, i, j, channel;
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    inittx();
    initmux();
   

    /* Initialize I/O and Peripherals for application */
    InitApp();




      while(1)
  {

	//Inputs Are Active Low

//********Button/Command Output Control************
//*************************************************
//If No Button Pressed, Send Command L0

          //RCSTA1bits.CREN     = 0b1;
      //    while(go != 73){
          //wait_ms(10);

        //  go = RCREG;
         
          //              }
          
          //RCSTA1bits.CREN     = 0b0;
          go = 0;
           for(j = 0; j < 4; j++){         //Increment through 4 MUX states
        wait_ms(3);
        LATBbits.LATB0 = mux1;             //Set the MUX control bits
        LATBbits.LATB1 = mux2;

           for(i = 0; i < 4; i++){         //Increment through four ADCs              //Gives the sensor being read an
       channel = i - 1; //Identifier
       
       wait_ms(3);
      adc_value  = adc_convert(i);           // preform A/D conversion on channel i
      adc_value += adc_convert(i);
      adc_value += adc_convert(i);
      adc_value += adc_convert(i);
      adc_value += adc_convert(i);
      adc_value += adc_convert(i);
      adc_value += adc_convert(i);
      adc_value += adc_convert(i);
      adc_value += adc_convert(i);
      adc_value += adc_convert(i);
      adc_value = adc_value/10;
      new_value = adc_value *.003226;
      new_value = new_value*36.8257-65.81;
      new_value = 10 * new_value;
      if(new_value <0 ){new_value = 0; }
      //if(new_value >300 ){new_value = 0; }
      new_value    = trunc(new_value);
      
      tx_int       = new_value;
      tx_val       = tx_int;
     wait_ms(3);
              while(TXSTA1bits.TRMT==0);   //wait for the register to be empty

                TXREG = tx_val;         //send the sensor value
  }
  if(j==0){
       mux1 = 1;
       mux2 = 0;
  }
  else if(j==1){
       mux1 = 0;
       mux2 = 1;
  }
  else if(j==2){
       mux1 = 1;
       mux2 = 1;
  }
  
   else{
               mux1 = 0;
               mux2 = 0;
           }
           }
         
                  while(TXSTA1bits.TRMT==0);   //wait for the register to be empty

                TXREG = 255;
      }


 /*        if(PORTAbits.RA0 == 1){

	adc_value = adc_convert(1);
            if(adc_value != prev_value){

                prev_value= adc_value;

                while(TXSTA1bits.TRMT==0);

                TXREG = adc_value;
            }
	}
         else{
             while(TXSTA1bits.TRMT==0);
             TXREG = 0;}

  }*/
}