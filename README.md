# TimerControl for STM32 Library

- This library can be used as a timer for general time management, e.g., control system time, delays, and more.
- TimerControl is the main class for timer management.
- This library can be used for STM32F1, STM32F4, STM32H7 MCU family series.
- It should define the MCU family series in the .h file.

## Public Member Variables For TimerControl Class

```cpp
/// @brief Stores the last error message encountered by the object.
std::string errorMessage;
```

## Public Member Functions For TimerControl Class

```cpp
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
```

-----------------------------------------------------------------------------------