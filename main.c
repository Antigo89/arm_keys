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
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PE|SYSCFG_EXTICR3_EXTI11_PE;
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PE;
  
  __enable_irq();
  //GPIO Initial
  GPIOE->MODER |= GPIO_MODER_MODE13_0|GPIO_MODER_MODE14_0|GPIO_MODER_MODE15_0;
  GPIOE->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11|GPIO_MODER_MODE12);  
  //Interrupts
  EXTI->PR |= EXTI_PR_PR10;
  EXTI->FTSR |= EXTI_FTSR_TR10|EXTI_FTSR_TR11|EXTI_FTSR_TR12;
  EXTI->IMR |= EXTI_IMR_IM10|EXTI_IMR_IM11|EXTI_IMR_IM12;
  NVIC_EnableIRQ(EXTI15_10_IRQn);

  #ifndef TASK1

  #endif

  while(1){
    
  }
}

void EXTI15_10_IRQHandler(void){
  //GPIOE->BSRR |= GPIO_BSRR_BS13;
  GPIOE->ODR ^= (1<<GPIO_ODR_OD13_Pos);
}
/*************************** End of file ****************************/
