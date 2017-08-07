#include "include/render.h"

Render::Render(SDL_Renderer *ren) {

    this->ren = ren;
}

SDL_Renderer *Render::GetRenderer() {

    return ren;
}

void Render::Draw(Rectangle *object) {

    if (SDL_RenderCopy(ren, object->GetTexture(), object->GetClip(), object->GetDestination()) != 0) {

        LogSDLError(std::cout, "SDL_RenderCopy");
    }
}

void Render::Draw(std::vector <Rectangle*> &objects) {

    for (int i = 0; i < objects.size(); ++i) {

        Draw(objects[i]);
    }
}

void Render::Clear(int8_t r, int8_t g, int8_t b, int8_t a) {

    if (SDL_SetRenderDrawColor(ren, r, g, b, a) != 0) {

        LogSDLError(std::cout, "SDL_SetRenderDrawColor");
    }
    SDL_RenderClear(ren);
}

void Render::Display() {

    SDL_RenderPresent(ren);
}
