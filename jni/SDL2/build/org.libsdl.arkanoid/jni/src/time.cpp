#include "include/time.h"

Time::Time() {

    startTicks = 0;
}

void Time::StartTicks() {

    startTicks = SDL_GetTicks();
}

float Time::GetTicks() {

    if (startTicks == 0) {

        return 0;
    }

    return SDL_GetTicks() - startTicks;
}
