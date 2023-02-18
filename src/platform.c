#include "platform.h"

#include <stddef.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#define PLATFORM_WIN
#endif

#if defined(PLATFORM_WIN)
#include <windows.h>
#else
#include <sys/time.h>
#endif

double wall_clock() {
#ifdef PLATFORM_WIN
    static double freq = 0;
    if (freq == 0) {
        LARGE_INTEGER freq_long;
        if (!QueryPerformanceFrequency(&freq_long)) {
            return 0;
        }
        freq = freq_long.QuadPart;
    }
    LARGE_INTEGER time;
    if (!QueryPerformanceCounter(&time)) {
        return 0;
    }
    return time.QuadPart / freq;
#else
    struct timeval time;
    if (gettimeofday(&time, NULL) != 0) {
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * 1.0e-6;
#endif
}
