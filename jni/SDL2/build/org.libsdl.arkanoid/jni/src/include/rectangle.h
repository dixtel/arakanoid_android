#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "include/vector2.h"
#include "include/logsdlerror.h"
#include "include/CleanUp.h"


class Rectangle {

    SDL_Texture *texture = nullptr;
    SDL_Rect     dst;
    SDL_Rect     clip;

    Vector2 <float>    position;
    Vector2 <unsigned> size;

    void UpdateDestination();
public:

    Rectangle();
    Rectangle(Vector2 <float> position, Vector2 <unsigned> size);
    ~Rectangle();

    void SetPosition(const Vector2 <float> position);
    void Move(const Vector2 <float> moveDistance);
    void SetSize(const Vector2 <unsigned> size);
    void SetClip(Vector2 <int> position, Vector2 <unsigned> size);
    void SetClip();
    bool SetAlpha(u_int8_t a);
    bool SetTexture(const std::string texturePath, SDL_Renderer *ren);
    void SetTexture(SDL_Texture *texture);

    Vector2 <float> GetPosition();
    Vector2 <unsigned> GetSize();
    SDL_Texture *GetTexture();
    SDL_Rect *GetDestination();
    SDL_Rect *GetClip();
};

#endif // RECTANGLE_H
