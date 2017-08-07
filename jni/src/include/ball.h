#ifndef BALL_H
#define BALL_H

#include <SDL.h>

#include "include/rectangle.h"
#include "include/vector2.h"
#include "include/logsdlerror.h"
#include "include/randomnumber.h"

#include <string>
#include <vector>
#include <math.h>

#define PI 3.14159265

class Ball {

    friend class Collision;

    Vector2 <float>  startPosition;
    Vector2 <float>  position;
    Vector2 <float>  currentCenterPos;
    Vector2 <float>  oldCenterPos;
    float            radius;
protected:

    Rectangle        ball;
    Vector2 <float>  velocity;
    Vector2 <float>  speed;
    int              angle;
    int              slope;
    int              hitPower;

    int GetStartAngle();
public:

    Ball();

    bool Init(Vector2 <float> pos, float radisu, const std::string pathTexture, SDL_Renderer *ren);
    void UpdatePhysics(float delta);
    void UpdateBall();
    void InvertXVelocity();
    void InvertYVelocity();
    void InvertYByPlayer(float leftDistance, float rightDistance);
    void Reset();

    int GetHitPower();
    Rectangle *Get();
};

#endif // BALL_H
