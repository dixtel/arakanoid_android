#ifndef LOGSDLERROR_H
#define LOGSDLERROR_H

#include <SDL.h>

#include <iostream>


inline void LogSDLError(std::ostream &os, const std::string &msg) {

    //os << msg << " error " << SDL_GetError() << std::endl;
    SDL_Log("SDL_Log test\n");
}

#endif // LOGSDLERROR_H
