#include "include.h"

int main (void)
{
    init_low_level();

    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitTypeDef LED_PIN;

    LED_PIN.Pin = GPIO_PIN_13;
    LED_PIN.Pull = GPIO_NOPULL;
    LED_PIN.Mode = GPIO_MODE_OUTPUT_PP;
    LED_PIN.Speed = GPIO_SPEED_FREQ_MEDIUM;

    HAL_GPIO_Init(GPIOC, &LED_PIN);

  	while (1)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(1000);
    }

}
