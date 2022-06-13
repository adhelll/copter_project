#include "low_level_conf.h"
#include "var.h"

static void SystemClock_Config(void);
static void init_serial(void);
static void init_tim1(void);


void init_low_level(void)
{
   HAL_Init();
   SystemClock_Config();
   init_tim1();
   init_serial();

}

/*!
  \brief Тактирование шин
  \attention Сформирована через CubeMX
*/
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }


}

static void init_serial(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    // UART1 RX
    GPIO_InitTypeDef serial_rx;
    serial_rx.Pin = GPIO_PIN_10;
    serial_rx.Mode = GPIO_MODE_INPUT;
    serial_rx.Pull = GPIO_NOPULL;
    serial_rx.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &serial_rx);

    // UART1 TX
    GPIO_InitTypeDef serial_tx;
    serial_tx.Pin = GPIO_PIN_9;
    serial_tx.Mode = GPIO_MODE_AF_PP;
    serial_tx.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &serial_tx);


    debug.Instance = USART1;
    debug.Init.BaudRate = 115200;
    debug.Init.WordLength = UART_WORDLENGTH_8B;
    debug.Init.StopBits = UART_STOPBITS_1;
    debug.Init.Parity = UART_PARITY_NONE;
    debug.Init.Mode = UART_MODE_TX_RX;
    debug.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    debug.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&debug);

}

static void init_tim1(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_TIM1_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();

    // TIM1_CH1 & TIM1_CH1N
    GPIO_InitTypeDef tim1_ch1;
    tim1_ch1.Pin = GPIO_PIN_8 | GPIO_PIN_7;
    tim1_ch1.Mode = GPIO_MODE_AF_PP;
    tim1_ch1.Pull = GPIO_NOPULL;
    tim1_ch1.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOA, &tim1_ch1);

    __HAL_AFIO_REMAP_TIM1_PARTIAL();

    tim1.Instance = TIM1;
    tim1.Init.Prescaler = 7199; // 10000 Гц
    tim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim1.Init.Period = 99; // 10000/100 = 100 Гц
    tim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    tim1.Init.RepetitionCounter = 0;
    tim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_PWM_Init(&tim1);

    TIM_OC_InitTypeDef tim1_conf;

    tim1_conf.OCMode = TIM_OCMODE_PWM1;
    tim1_conf.Pulse = 20;
    tim1_conf.OCPolarity = TIM_OCPOLARITY_HIGH;
    tim1_conf.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    tim1_conf.OCIdleState = TIM_OCIDLESTATE_RESET;
    tim1_conf.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    tim1_conf.OCFastMode = TIM_OCFAST_DISABLE;

    HAL_TIM_PWM_ConfigChannel(&tim1, &tim1_conf, TIM_CHANNEL_1);

    TIM_BreakDeadTimeConfigTypeDef dead_time_tim1_conf;

    dead_time_tim1_conf.OffStateRunMode = TIM_OSSR_DISABLE;
    dead_time_tim1_conf.OffStateIDLEMode = TIM_OSSI_DISABLE;
    dead_time_tim1_conf.LockLevel = TIM_LOCKLEVEL_OFF;
    dead_time_tim1_conf.DeadTime = 1; // 100 мкс
    dead_time_tim1_conf.BreakState = TIM_BREAK_DISABLE;
    dead_time_tim1_conf.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    dead_time_tim1_conf.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&tim1, &dead_time_tim1_conf);

    HAL_TIM_PWM_Start(&tim1, TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&tim1, TIM_CHANNEL_1);


}
