#include "include/player.h"

Player::Player() {

    velocity    = 0;
    speed       = 230;
    maxSpeed    = 260;
    friction    = 195;

    init        = false;
    moveRight   = false;
    moveLeft    = false;
}

bool Player::Init(Vector2 <float> position, Vector2 <unsigned> size, const std::string pathTexture, SDL_Renderer *ren) {

    if (!player.SetTexture(pathTexture, ren)) {

        PrintError("SetTexture");
        return false;
    }

    player.SetPosition(position);
    player.SetSize(size);
    player.SetClip(Vector2 <int> (0, 0), size);

    startPosition  = position;
    this->position = position;
    this->size     = size;

    return true;
}

void Player::UpdatePhysics(float delta) {

    // Events
    if (moveRight) {

        velocity += speed * delta;
    }

    if (moveLeft) {

        velocity -= speed * delta;
    }

    // Friction
    if (velocity > 0) {

        velocity -= friction * delta;

        if (velocity < 0) velocity = 0;
    }
    else if (velocity < 0) {

        velocity += friction * delta;

        if (velocity > 0) velocity = 0;
    }

    // Max Speed
    if (velocity > maxSpeed) velocity = maxSpeed;
    else if (velocity < -maxSpeed) velocity = -maxSpeed;
}

void Player::UpdatePlayer() {

    MoveX(velocity);
}

void Player::MoveRight(bool move) {

    moveRight = move;
}

void Player::MoveLeft(bool move) {

    moveLeft = move;
}

void Player::MoveX(float velocity) {

    position.x += velocity;
    player.SetPosition(position);
}

void Player::SetPosition(Vector2 <float> position) {

    player.SetPosition(position);
}

void Player::Reset() {

    position = startPosition;
    velocity = 0;
}

Rectangle *Player::Get() {

    return &player;
}
