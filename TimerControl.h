#pragma once

// Define the target MCU family here
#define STM32F4
// #define STM32F1
// #define STM32H7

// ##################################################################################
// Include libraries:

#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"
#endif

#include <string>

// ##################################################################################

/**
 * @class TimerControl
 */
class TimerControl
{
    public:

        /// @brief The last error occurred for the object.
		std::string errorMessage;

        /**
		 * @struct ParametersStructure
		 * @brief Parameters structure
		 */
        struct ParametersStructure
        {
            TIM_TypeDef *INSTANCE;

            /**
             * @brief Specifies the prescaler value used to divide the TIM clock.
             * @note This parameter can be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF.
             */
            uint32_t PRESCALER;       

            uint32_t RESOLUTION;           

            /**
             * @brief Specifies the clock division.
             * This parameter can be a value of TIM_ClockDivision
             * @note Prescaler for 10 kHz timer (84 MHz / 8400 = 10 kHz)
             *  */                                          
            uint32_t CLOCKDIVISION;    

        }parameters;

        /**
		 * @brief Default constructor. Init some variables and parameters.
		 */
        TimerControl();

        bool init(void);

        uint32_t micros(void);

        uint32_t millis(void);

    private:

        TIM_HandleTypeDef _htim;

        bool _checkParameters(void);

};







