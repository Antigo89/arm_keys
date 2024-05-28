/*
File    : main.c

*/

#include "main.h"
/*********************************main************************************/
int main(void) {
  //Values initial

  SystemInit();
  RCC_Init();
  // Clock BUS
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
  #ifdef TASK3
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  #endif
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI10_PE|SYSCFG_EXTICR3_EXTI11_PE;
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PE;
  
  __enable_irq();
  //GPIO Initial
  GPIOE->MODER |= GPIO_MODER_MODE13_0|GPIO_MODER_MODE14_0|GPIO_MODER_MODE15_0;
  GPIOE->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11|GPIO_MODER_MODE12);
  #ifdef TASK3 
  GPIOB->MODER |= GPIO_MODER_MODE0_0;
  GPIOB->MODER &= ~(GPIO_MODER_MODE1);
  GPIOB->BSRR |= GPIO_BSRR_BR0;
  GPIOB->PUPDR |= GPIO_PUPDR_PUPD1_1;
  #endif 
  //Interrupts
  EXTI->PR |= EXTI_PR_PR10|EXTI_PR_PR11|EXTI_PR_PR12;
  EXTI->FTSR |= EXTI_FTSR_TR10|EXTI_FTSR_TR11|EXTI_FTSR_TR12;
  #ifndef TASK3
  EXTI->IMR |= EXTI_IMR_IM10|EXTI_IMR_IM11|EXTI_IMR_IM12; //S1 & S3 & S3
  #else
  EXTI->IMR |= EXTI_IMR_IM10; //only S1
  #endif
  NVIC_EnableIRQ(EXTI15_10_IRQn);
  //LED turn off
  GPIOE->BSRR |= GPIO_BSRR_BS13|GPIO_BSRR_BS14|GPIO_BSRR_BS15;

  while(1){
    __NOP();
  }
}
/***********************interrupts function**************************/
void EXTI15_10_IRQHandler(void){
  //TASK1
  #ifdef TASK1
  if((EXTI->PR & EXTI_PR_PR10) != 0){
    GPIOE->BSRR |= GPIO_BSRR_BR13|GPIO_BSRR_BS14|GPIO_BSRR_BS15;
  }
  if((EXTI->PR & EXTI_PR_PR11) != 0){
    GPIOE->BSRR |= GPIO_BSRR_BR14|GPIO_BSRR_BS13|GPIO_BSRR_BS15;
  }
  if((EXTI->PR & EXTI_PR_PR12) != 0){
    GPIOE->BSRR |= GPIO_BSRR_BR15|GPIO_BSRR_BS13|GPIO_BSRR_BS14;
  }
  EXTI->PR |= EXTI_PR_PR10|EXTI_PR_PR11|EXTI_PR_PR12;
  #endif
  //TASK2
  #ifdef TASK2
  switch(EXTI->PR & (EXTI_PR_PR10|EXTI_PR_PR11|EXTI_PR_PR12)){
    case EXTI_PR_PR10:
      GPIOE->BSRR |= GPIO_BSRR_BR13|GPIO_BSRR_BS14|GPIO_BSRR_BS15;
      break;
    case EXTI_PR_PR11:
      GPIOE->BSRR |= GPIO_BSRR_BR14|GPIO_BSRR_BS13|GPIO_BSRR_BS15;
      break;
    case EXTI_PR_PR12:
      GPIOE->BSRR |= GPIO_BSRR_BR15|GPIO_BSRR_BS13|GPIO_BSRR_BS14;
      break;
  }
  EXTI->PR |= EXTI_PR_PR10|EXTI_PR_PR11|EXTI_PR_PR12;
  #endif
  //TASK3
  #ifdef TASK3
  GPIOB->BSRR |= GPIO_BSRR_BS0;
  if(GPIOB->IDR & GPIO_IDR_ID1){
    GPIOE->BSRR |= GPIO_BSRR_BR13|GPIO_BSRR_BR14;
  }else{
    GPIOE->BSRR |= GPIO_BSRR_BS13|GPIO_BSRR_BS14;
  }
  EXTI->PR |= EXTI_PR_PR10;
  #endif
}
/*************************** End of file ****************************/
