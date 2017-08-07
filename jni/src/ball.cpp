#include "include/ball.h"

Ball::Ball() {

    velocity  = Vector2 <float> (0, 0);
    speed     = Vector2 <float> (600, 600);
    angle     = GetStartAngle();
    slope     = 30;
    hitPower  = 1;
}

int Ball::GetStartAngle() {

    return 90 + GetRandomNumber(-30, 30);
}

bool Ball::Init(Vector2 <float> pos, float radius, const std::string pathTexture, SDL_Renderer *ren) {

    startPosition = pos;
    position = pos;
    this->radius = radius;

    if (!ball.SetTexture(pathTexture, ren)) {

        LogSDLError(std::cout, "SetTexture");
        return false;
    }

    ball.SetPosition(position);
    ball.SetSize(Vector2 <unsigned> (radius * 2, radius * 2));
    ball.SetClip();

    currentCenterPos = position + radius;


    return true;
}

void Ball::UpdatePhysics(float delta) {

    float x = cos(angle * PI / 180);
    float y = -sin(angle * PI / 180);

    velocity.x = (x * speed.x) * delta;
    velocity.y = (y * speed.y) * delta;
}

void Ball::UpdateBall() {

    position += velocity;
    oldCenterPos = currentCenterPos;
    currentCenterPos = position + radius;
    ball.SetPosition(position);
}

void Ball::InvertXVelocity() {

    if (angle < 90) {

        angle = 90 + (90 - angle);
    }
    else if (angle > 90 && angle < 180) {

        angle = 90 - (angle - 90);
    }
    else if (angle > 180 && angle < 270) {

        angle = 270 + (270 - angle);
    }
    else if (angle > 270 && angle < 360) {

        angle = 270 - (angle - 270);
    }

}

void Ball::InvertYVelocity() {

    if (angle < 180) {

        angle = 180 + (180 - angle);
    }
    else if (angle > 180) {

        angle = 180 - (180 - (360 - angle));
    }
}

void Ball::InvertYByPlayer(float leftDistance, float rightDistance) {

    int currentSlope = 0;

    if (leftDistance > rightDistance) {

        float halfDistance = (leftDistance + rightDistance) / 2;
        float procentSlopePower = (halfDistance - rightDistance) / halfDistance;
        float procentSlope = leftDistance / (leftDistance + rightDistance);
        procentSlope *= procentSlopePower;
        currentSlope = -(procentSlope * slope);
    }
    else if (leftDistance < rightDistance) {

        float halfDistance = (leftDistance + rightDistance) / 2;
        float procentSlopePower = (halfDistance - leftDistance) / halfDistance;
        float procentSlope = rightDistance / (leftDistance + rightDistance);
        procentSlope *= procentSlopePower;
        currentSlope = procentSlope * slope;
    }

    if (angle < 180) {

        angle = 180 + (180 - angle) + currentSlope;
    }
    else if (angle > 180) {

        angle = 180 - (180 - (360 - angle)) + currentSlope;
    }

}

void Ball::Reset() {

    position = startPosition;
    angle = GetStartAngle();
}

int Ball::GetHitPower() {

    return hitPower;
}

Rectangle *Ball::Get() {

    return &ball;
}


