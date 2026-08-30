#pragma once

// DLL export macro
#ifdef _WIN32
    #ifdef DEKI_STM32_HAL_EXPORTS
        #define DEKI_STM32_HAL_API __declspec(dllexport)
    #else
        #define DEKI_STM32_HAL_API __declspec(dllimport)
    #endif
#else
    #define DEKI_STM32_HAL_API __attribute__((visibility("default")))
#endif
