#pragma once

#ifdef _WIN32
    #ifdef CITRUS_EXPORTS
        #define CITRUS_API __declspec(dllexport)
    #else
        #define CITRUS_API __declspec(dllimport)
    #endif
#else
    #define CITRUS_API
#endif