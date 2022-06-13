#ifndef COPTER_PROJECT_VAR_H
#define COPTER_PROJECT_VAR_H

#ifdef MAIN

UART_HandleTypeDef debug;
TIM_HandleTypeDef tim1;

#else

extern UART_HandleTypeDef debug;
extern TIM_HandleTypeDef tim1;

#endif /* MAIN */

#endif //COPTER_PROJECT_VAR_H
