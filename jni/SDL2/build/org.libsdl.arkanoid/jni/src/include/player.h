#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "include/rectangle.h"
#include "include/vector2.h"
#include "include/border.h"

#include <string>

class Player {

    friend class Collision;

    Vector2 <float>     startPosition;
    Vector2 <float>     position;
    Vector2 <unsigned>  size;
    float               velocity;
protected:

    Rectangle           player;
    float               speed;
    float               maxSpeed;
    float               friction;
    bool                init;
    bool                moveRight;
    bool                moveLeft;
public:

    Player();

    bool Init(Vector2 <float> position, Vector2 <unsigned> size, const std::string pathTexture, SDL_Renderer *ren);

    void UpdatePhysics(float delta);
    void UpdatePlayer();
    void MoveRight(bool move);
    void MoveLeft(bool move);
    void MoveX(float velocity);
    void SetPosition(Vector2 <float> position);
    void Reset();

    Rectangle *Get();
};

#endif // PLAYER_H
