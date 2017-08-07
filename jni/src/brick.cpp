#include "include/brick.h"

Brick::Brick() {

    startHelath = 0;
    currentHelath = 0;
}

bool Brick::Init(Vector2 <float> position, Vector2 <unsigned> size, int health, const std::string pathTexture, BrickType type, SDL_Renderer *ren) {

    if (!brick.SetTexture(pathTexture, ren)) {

        std::cout << pathTexture << std::endl;
        LogSDLError(std::cout, "SetTexture");
        return false;
    }

    brick.SetPosition(position);
    brick.SetSize(size);
    brick.SetClip();

    this->position = position;
    this->size     = size;
    this->type     = type;
    startHelath    = health;
    currentHelath  = health;

    return true;
}

void Brick::DecreaseHealth(unsigned value) {

    currentHelath -= value;
}

int Brick::GetHelath() {

    return currentHelath;
}

BrickType Brick::GetType() {

    return type;
}

Rectangle *Brick::Get() {

    return &brick;
}
