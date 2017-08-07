#ifndef TIME_H
#define TIME_H

#include <SDL.h>

#include <cstdint>


class Time {

    u_int32_t startTicks;
public:

    Time();

    void StartTicks();
    float GetTicks();
};

#endif // TIME_H
