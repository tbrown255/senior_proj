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

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
void main(void)
{
    uint8_t adc_value,prev_value, output, sensor, mux;                 // variable to hold ADC conversion result in
    char mux1 = 0, mux2 = 0, i, j, channel;
    /* Configure the oscillator for the device */
    ConfigureOscillator();
    inittx();
    initmux();
   

    /* Initialize I/O and Peripherals for application */
    InitApp();
/*
 *
 *
    TRISAbits.TRISA0 = 0;               // set pin as output
    while(1)
    {
 
  for(j = 0; j < 4; j++){
        LATBbits.LATB0 = mux1;             // set pin LOW
        LATBbits.LATB1 = mux2;
  for(i = 3; i < 3; i++){
       mux = mux2 * 2 + mux1;
       sensor = mux + 10 * i;
  adc_value = adc_convert(i);     // preform A/D conversion on channel i
 
               while(TXSTA1bits.TRMT==0);

                TXREG = sensor;
   
              while(TXSTA1bits.TRMT==0);

                TXREG = adc_value;
  }
  if(j=0){
      mux1 = 1;
       mux2 = 0;
  }
  else if(j=1){
       mux1 = 0;
       mux2 = 1;
  } * else if(j=2){
       mux1 = 1;
       mux2 = 1;
  }
  }
 mux1 = 0;
 mux2 = 0;
          
}*/


   TRISCbits.TRISC6 = 0;
      while(1)
  {

	//Inputs Are Active Low

//********Button/Command Output Control************
//*************************************************
//If No Button Pressed, Send Command L0

           for(j = 0; j < 4; j++){         //Increment through 4 MUX states
        LATBbits.LATB0 = mux1;             //Set the MUX control bits
        LATBbits.LATB1 = mux2;

           for(i = 0; i < 4; i++){         //Increment through four ADCs
       mux = mux2 * 2 + mux1;              //Gives a variable for the MUX value
       sensor = mux + 10 * i;              //Gives the sensor being read an
       channel = i - 1;                                    //Identifier
     adc_value = adc_convert(i);           // preform A/D conversion on channel i

               while(TXSTA1bits.TRMT==0);  //wait for the register to be empty

                TXREG = sensor;            //Send the ADC identifier

              while(TXSTA1bits.TRMT==0);   //wait for the register to be empty

                TXREG = adc_value;         //send the sensor value
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