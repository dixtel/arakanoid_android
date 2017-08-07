#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>

#include "include/rectangle.h"
#include "include/logsdlerror.h"


#include <vector>


class Render {

    SDL_Renderer *ren = nullptr;
public:

    Render(SDL_Renderer *ren);

    SDL_Renderer *GetRenderer();

    void Draw(Rectangle *object);
    void Draw(std::vector <Rectangle*> &objects);

    void Clear(int8_t r = 0, int8_t g = 0, int8_t b = 0, int8_t a = 255);

    void Display();
};

#endif // RENDER_H
