#pragma once

// Define the target MCU family here
// Uncomment the desired MCU family definition below:

// #define STM32F4
#define STM32F1
// #define STM32H7

// ##################################################################################
// Include libraries:

#if defined(STM32F1)
#include "stm32f1xx_hal.h"      // HAL library for STM32F1 series
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"      // HAL library for STM32F4 series
#elif defined(STM32H7)
#include "stm32h7xx_hal.h"      // HAL library for STM32H7 series
#else
#error "Unsupported MCU family. Please define a valid target (e.g., STM32F1, STM32F4, STM32H7)."
#endif

#include <string>       // Include the standard string library for error handling and messages

// ##################################################################################

/**
 * @class TimerControl
 */
class TimerControl
{
    public:

        /// @brief Stores the last error message encountered by the object.
		std::string errorMessage;

        /**
         * @brief Constructor to initialize the TimerControl object.
         * @param HANDLE A pointer to the HAL timer handle to associate with this instance.
         */
        TimerControl(TIM_HandleTypeDef *HANDLE);

        /**
         * @brief Set the clock frequency for the timer.
         * @param frq clock frequency in Hz.
         */
        void setClockFrequency(uint32_t frq);

        /**
         * @brief Initialize the timer with calculated parameters and validate settings.
         * @return True if the initialization is successful, false otherwise.
         */
        bool init(void);

        /**
         * @brief Start the timer.
         * @return True if the timer starts successfully, false otherwise.
         */
        bool start(void);

        /**
         * @brief Reset the timer's counters and internal state.
         */
        void reset(void);

        /**
         * @brief Stop the timer.
         * @return True if the timer stops successfully, false otherwise.
         */
        bool stop(void);

        /**
         * @brief Callback function called when the timer period elapses.
         * @note This function should be used in the void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) function.
         */
        void PeriodElapsedCallback(void);

        /**
         * @brief Get the elapsed time in microseconds since the timer started.
         * @return Elapsed time in microseconds.
         */
        uint64_t micros(void);

        /**
         * @brief Get the elapsed time in milliseconds since the timer started.
         * @return Elapsed time in milliseconds.
         */
        uint64_t millis(void);

        /**
         * @brief Delay the program execution for a specified time in milliseconds.
         * @param value Time to delay in milliseconds.
         */
        void delay(uint32_t value);

        /**
         * @brief Delay the program execution for a specified time in microseconds.
         * @param value Time to delay in microseconds.
         */
        void delayMicroseconds(uint32_t value);

    private:

        /// @brief Pointer to the HAL timer handle associated with this instance.
        TIM_HandleTypeDef *_htim;

        /// @brief Tracks the elapsed time in microseconds.
        volatile uint64_t _tMicros;

        /// @brief Tracks the elapsed time in milliseconds.
        volatile uint64_t _tMillis;

        /// @brief Counter for the number of times the timer period has elapsed.
        volatile uint32_t _periodElapsedCounter;

        /**
         * @brief Specifies the period value to be loaded into the active 
         * Auto-Reload Register at the next update event. [us]
         */
        double _period;

        /// @brief Frequency of the timer in Hz.
        double _frq;

        /// @brief Clock frequency driving the timer in Hz.
        uint32_t _clockFrq;

        /// @brief Flag indicating whether the timer has been initialized.
        bool _initFlag;

        /**
         * @brief Validate the timer parameters to ensure correct operation.
         * @return True if parameters are valid, false otherwise.
         */
        bool _checkParameters(void);

};









