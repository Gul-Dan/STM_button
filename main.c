#include "iostm8l152c6.h"

#define STRINGVECTOR(x) #x
 #define ISR( a, b )  \
 _Pragma( STRINGVECTOR( vector = (b) ) )        \
 __interrupt void (a)( void )


ISR(Pin1_interrupt, EXTI1_vector)
{
  if(PC_ODR_bit.ODR7)
  {
    PC_ODR_bit.ODR7 = 0;
    PE_ODR_bit.ODR7 = 1;
  }
  else
  {
    PC_ODR_bit.ODR7 = 1;
    PE_ODR_bit.ODR7 = 0;
  }
  EXTI_SR1_bit.P1F=1;
}

int main( void )
{ 
  //blue LED
  PC_DDR_bit.DDR7 = 1;
  PC_CR1_bit.C17 = 1;
  
  //green LED
  PE_DDR_bit.DDR7 = 1;
  PE_CR1_bit.C17 = 1;
  
  //button
  //PC_DDR_bit.DDR1 =0;
  PC_CR1_bit.C11=1;
  PC_CR2_bit.C21=1;
  EXTI_CR1_bit.P1IS=2; //why not CR2?
  //ITC_SPR1_bit.VECT1SPR=1;
  
  asm("RIM");
  
  PC_ODR_bit.ODR7 = 1;
  
  while (1)
  {
    asm("WFI");
  };
}