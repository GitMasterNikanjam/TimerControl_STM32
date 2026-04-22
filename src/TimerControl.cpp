
// #################################################################################
// Include libraries:

#include "TimerControl.h"


TimerControl::TimerControl(TIM_HandleTypeDef *HANDLE)
{
    _htim = HANDLE;

    _clockFrq = 1000000;
    _period = 0;
    _frq = 1000000;
    _periodElapsedCounter = 0;
    _tMicros = 0;
    _tMillis = 0;
    _initFlag = false;
}

bool TimerControl::setClockFrequency(uint32_t frq)
{
    if (frq < 1000000U) 
    {
        return false;
    }

    _clockFrq = frq;

    return true;
}

bool TimerControl::init(void)
{
    _initFlag = false; 

    if(_htim->Instance == nullptr)
    {
        return false;
    }

    // if(_htim->Instance != nullptr)
    // {
    //     _htim->Instance->DIER |= TIM_DIER_UIE;  // Enable update interrupt
    // }
    
    // #ifdef TIM1
    // if(_htim->Instance == TIM1)
    // {
    //     __HAL_RCC_TIM1_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM2
    // else if(_htim->Instance == TIM2)
    // {
    //     __HAL_RCC_TIM2_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM3
    // else if(_htim->Instance == TIM3)
    // {
    //     __HAL_RCC_TIM3_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM4
    // else if(_htim->Instance == TIM4)
    // {
    //     __HAL_RCC_TIM4_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM5
    // else if(_htim->Instance == TIM5)
    // {
    //     __HAL_RCC_TIM5_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM6
    // else if(_htim->Instance == TIM6)
    // {
    //     __HAL_RCC_TIM6_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM7
    // else if(_htim->Instance == TIM7)
    // {
    //     __HAL_RCC_TIM7_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM8
    // else if(_htim->Instance == TIM8)
    // {
    //     __HAL_RCC_TIM8_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM9
    // else if(_htim->Instance == TIM9)
    // {
    //     __HAL_RCC_TIM9_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM10
    // else if(_htim->Instance == TIM10)
    // {
    //     __HAL_RCC_TIM10_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM11
    // else if(_htim->Instance == TIM11)
    // {
    //     __HAL_RCC_TIM11_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM12
    // else if(_htim->Instance == TIM12)
    // {
    //     __HAL_RCC_TIM12_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM13
    // else if(_htim->Instance == TIM13)
    // {
    //     __HAL_RCC_TIM13_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // #ifdef TIM14
    // else if(_htim->Instance == TIM14)
    // {
    //     __HAL_RCC_TIM14_CLK_ENABLE(); // Replace TIMx with the correct timer
    // }
    // #endif
    // else
    // {
    //     errorMessage = "Error TimerControl: The timer instance is not correct.";
    //     return false;
    // }
    

    if(_checkParameters() == false)
    {
        return false;
    }
    
    if (_clockFrq < 1000000U) 
    {
        return false;
    }

    _htim->Init.CounterMode = TIM_COUNTERMODE_UP;
    _htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    _htim->Init.Prescaler = (_clockFrq / 1000000) - 1;

    if (HAL_TIM_Base_Init(_htim) != HAL_OK)
    {
        errorMessage = "Error TimerControl: HAL_TIM_Base_Init() is failed.";
        return false;
    }

    _frq = _clockFrq / ( (_htim->Init.AutoReloadPreload + 1) * (_htim->Init.Prescaler + 1) );

    if(_frq == 0U) 
    {
        return false;
    }

   _period = (1000000.0 / _frq);

    _initFlag = true;
    return true;
}

bool TimerControl::start(void)
{
    if(_initFlag == false)
    {
        errorMessage = "Error TimerControl: Init is needed before start the timer.";
        return false;
    }

    if(HAL_TIM_Base_Start_IT(_htim) != HAL_OK) 
    {
        errorMessage = "Error TimerControl: HAL_TIM_Base_Start_IT() is failed.";
        return false;
    } 

    return true;
}

void TimerControl::reset(void)
{
    stop();
    _htim->Instance->CNT = 0;
    _periodElapsedCounter = 0; 
    start();
}

bool TimerControl::stop(void)
{
    if(_initFlag == false)
    {
        errorMessage = "Error TimerControl: Init is needed before stop the timer.";
        return false;
    }

    if(HAL_TIM_Base_Stop_IT(_htim) != HAL_OK) 
    {
        errorMessage = "Error TimerControl: HAL_TIM_Base_Stop_IT() is failed.";
        return false;
    } 

    return true; 
}

void TimerControl::PeriodElapsedCallback(void)
{
    _periodElapsedCounter++;
    _tMicros = _periodElapsedCounter * _period;
}

uint64_t TimerControl::micros(void)
{
    _tMicros = (uint64_t)_htim->Instance->CNT + (uint64_t)(_periodElapsedCounter * _period);
    return _tMicros;
}

uint64_t TimerControl::millis(void)
{
    _tMillis = micros() / 1000;
    return _tMillis;
}

void TimerControl::delay(uint32_t value)
{
    uint64_t startTime = millis();

    while((millis() - startTime) < value);
}

void TimerControl::delayMicroseconds(uint32_t value)
{
    uint64_t startTime = micros();

    while((micros() - startTime) < value);
}

bool TimerControl::getInitState(void)
{
    return _initFlag;
}

bool TimerControl::_checkParameters(void)
{
    // bool state = (_htim->Instance != nullptr) && (_htim->Init.CounterMode == TIM_COUNTERMODE_UP) &&
    //              (_htim->Init.Period > 0) && (_clockFrq > 0) && (__HAL_TIM_GET_IT_SOURCE(_htim, TIM_IT_UPDATE) == SET);

    bool state = (_htim->Instance != nullptr) && (_htim->Init.CounterMode == TIM_COUNTERMODE_UP) &&
                 (_htim->Init.Period > 0) && (_clockFrq > 0);

    if(state == false)
    {
        errorMessage = "Error TimerControl: One or some parameters are not correct.";
        return false;
    }

    return true;
}