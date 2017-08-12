#ifndef BRICK_H
#define BRICK_H

#include <SDL.h>

#include "include/rectangle.h"
#include "include/vector2.h"
#include "include/logerror.h"

#include <string>

enum BrickType {

    type1 = 0,
    type2 = 1,
    type3 = 2
};

class Brick {

    friend class Collision;

    Vector2 <float>    position;
    Vector2 <unsigned> size;
protected:

    Rectangle brick;
    BrickType type;
    int       startHelath;
    int       currentHelath;
public:

    Brick();
    bool Init(Vector2 <float> position, Vector2 <unsigned> size, int health, const std::string pathTexture, BrickType type, SDL_Renderer *ren);
    void DecreaseHealth(unsigned value);

    int GetHelath();
    BrickType GetType();
    Rectangle *Get();
};

#endif // BRICK_H
