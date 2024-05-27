/*
File    : main.c

*/

#include "main.h"
/******************************functions**********************************/


/*********************************main************************************/
int main(void) {
  //Values initial

  SystemInit();
  RCC_Init();
  // Clock BUS
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;

  //GPIO Initial
  GPIOE->MODER |= GPIO_MODER_MODE13_0|GPIO_MODER_MODE14_0|GPIO_MODER_MODE15_0;

  while(1){
    
  }
}

/*************************** End of file ****************************/
