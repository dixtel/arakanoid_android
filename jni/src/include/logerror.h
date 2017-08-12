#ifndef LOGERROR_H
#define LOGERROR_H

#include <SDL.h>

#include <iostream>
#include <string>


inline void PrintError(std::string msg) {

	msg.append(" ");
	msg.append(SDL_GetError());

    SDL_Log(msg.c_str(), "%s");
}

#endif // LOGERROR_H
