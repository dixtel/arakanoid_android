#include "include/rectangle.h"

Rectangle::Rectangle() {

}

Rectangle::Rectangle(Vector2 <float> position, Vector2 <unsigned> size) {

    this->position = position;
    this->size     = size;

    clip.x = 0;
    clip.y = 0;
    clip.w = size.x;
    clip.h = size.y;

    UpdateDestination();
}

Rectangle::~Rectangle() {

    CleanUp(texture);
}

void Rectangle::UpdateDestination() {

    dst.x = position.x;
    dst.y = position.y;
    dst.w = size.x;
    dst.h = size.y;
}

void Rectangle::SetPosition(const Vector2 <float> position) {

    this->position = position;
    UpdateDestination();
}

void Rectangle::Move(const Vector2 <float> moveDistance) {

    this->position = Vector2 <float> (position.x + moveDistance.x, position.y + moveDistance.y);
    UpdateDestination();
}

void Rectangle::SetSize(const Vector2 <unsigned> size) {

    this->size = size;
    UpdateDestination();
}

void Rectangle::SetClip(Vector2 <int> position, Vector2 <unsigned> size) {

    clip.x = position.x;
    clip.y = position.y;
    clip.w = size.x;
    clip.h = size.y;
}

void Rectangle::SetClip() {

    clip.x = 0;
    clip.y = 0;
    clip.w = size.x;
    clip.h = size.y;
}

bool Rectangle::SetAlpha(u_int8_t a) {

   // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    if (SDL_SetTextureAlphaMod(texture, a) != 0) {

        PrintError("SDL_SetTextureAlphaMod alpha");
        return false;
    }

    return true;
}

bool Rectangle::SetTexture(const std::string texturePath, SDL_Renderer *ren) {

    if (texture != nullptr) {

        CleanUp(texture);
    }

    texture = IMG_LoadTexture(ren, texturePath.c_str());

    if (texture == nullptr) {

        PrintError("IMG_LoadTexture, path:" + texturePath);
        return false;
    }

    return true;
}

void Rectangle::SetTexture(SDL_Texture *texture) {

    if (this->texture != nullptr) {

        CleanUp(this->texture);
    }

    this->texture = texture;
}

Vector2 <float> Rectangle::GetPosition() {

    return position;
}

Vector2 <unsigned> Rectangle::GetSize() {

    return size;
}

SDL_Texture *Rectangle::GetTexture() {

    return texture;
}

SDL_Rect *Rectangle::GetDestination() {

    return &dst;
}

SDL_Rect *Rectangle::GetClip() {

    return &clip;
}
