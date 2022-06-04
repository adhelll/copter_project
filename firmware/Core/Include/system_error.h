#ifndef COPTER_PROJECT_LOW_LEVEL_ERROR_H
#define COPTER_PROJECT_LOW_LEVEL_ERROR_H

#include "include.h"

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void Error_Handler (void);

void errorHandler (void);


#endif /* _IT_H_ */
