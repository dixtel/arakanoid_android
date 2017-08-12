#include "include/text.h"

Text::Text(SDL_Renderer *ren) {

    this->ren = ren;
    font      = nullptr;
    isChanged = false;
}

Text::~Text() {

    if (font != nullptr) {

        TTF_CloseFont(font);
    }

    ren = nullptr;
}

void Text::Update() {

    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, surface);

    int widthSurface, heightSurface;
    SDL_QueryTexture(texture, NULL, NULL, &widthSurface, &heightSurface);

    rect.SetTexture(texture);
    rect.SetPosition(position);
    rect.SetSize(Vector2 <unsigned> (widthSurface, heightSurface));
    rect.SetClip();

    CleanUp(surface);
}

void Text::SetPosition(Vector2 <float> position) {

    this->position = position;
    isChanged = true;
}

void Text::SetText(const std::string text) {

    this->text = text;
    isChanged = true;
}

void Text::SetSize(unsigned size) {

    this->size = size;

    if (font != nullptr) {

        TTF_CloseFont(font);
    }

    font = TTF_OpenFont(pathToFont.c_str(), size);

    if (font == nullptr) {

        PrintError("TTF_OpenFont");
        return;
    }
}

void Text::SetColor(SDL_Color color) {

    this->color = color;
    isChanged = true;
}

void Text::SetFont(std::string pathToFont) {

    this->pathToFont = pathToFont;

    if (font != nullptr) {

        TTF_CloseFont(font);
    }

    font = TTF_OpenFont(pathToFont.c_str(), size);

    if (font == nullptr) {

        PrintError("TTF_OpenFont");
        return;
    }

    Update();
}

Rectangle *Text::Get() {

    if (isChanged) {

        Update();
        isChanged = false;
    }

    return &rect;
}
