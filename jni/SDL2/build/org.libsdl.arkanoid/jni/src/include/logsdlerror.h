#ifndef LOGSDLERROR_H
#define LOGSDLERROR_H

#include <SDL2/SDL.h>

#include <iostream>


inline void LogSDLError(std::ostream &os, const std::string &msg) {

    os << msg << " error " << SDL_GetError() << std::endl;
}

#endif // LOGSDLERROR_H
