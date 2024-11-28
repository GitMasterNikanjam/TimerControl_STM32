
// #################################################################################
// Include libraries:

#include "TimerControl.h"


TimerControl::TimerControl()
{
    parameters.INSTANCE = nullptr;
    parameters.PRESCALER = 0;
    parameters.CLOCKDIVISION = 0;
    parameters.RESOLUTION = 16;
}

bool TimerControl::init(void)
{
    if(_checkParameters() == false)
    {
        return false;
    }

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    _htim.Instance = parameters.INSTANCE;
    _htim.Init.Prescaler = parameters.PRESCALER;
    _htim.Init.CounterMode = TIM_COUNTERMODE_UP;

    switch(parameters.RESOLUTION)
    {
        case 16:
            _htim.Init.Period = 65535;
        break;
        case 32:
            _htim.Init.Period = 4294967295;
        break;
    }
    
    _htim.Init.ClockDivision = parameters.CLOCKDIVISION;
    _htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&_htim) != HAL_OK)
    {
        // Error_Handler();
        return false;
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&_htim, &sClockSourceConfig) != HAL_OK)
    {
        // Error_Handler();
        return false;
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&_htim, &sMasterConfig) != HAL_OK)
    {
        // Error_Handler();
        return false;
    }

    HAL_TIM_Base_Start(&_htim);  // Start the timer

    return true;
}

uint32_t TimerControl::micros(void)
{
    return __HAL_TIM_GET_COUNTER(&_htim);
}

uint32_t TimerControl::millis(void)
{
    return (float)micros() / 1000.0;
}

bool TimerControl::_checkParameters(void)
{
    bool state = ( (parameters.RESOLUTION == 16) || (parameters.RESOLUTION == 32) ) &&
                 (parameters.INSTANCE != nullptr);

    if(state == false)
    {
        return false;
    }

    return true;
}