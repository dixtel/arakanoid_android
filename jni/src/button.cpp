#include "include/button.h"

void Button::SetPosition(Vector2 <int> newPosition) {

    Vector2 <float> position(newPosition.x, newPosition.y);
    positionButton = newPosition;
    button.SetPosition(position);
}

void Button::SetSize(Vector2 <unsigned> newSize) {

    sizeButton = newSize;
    button.SetSize(newSize);
    button.SetClip(Vector2 <int> (0, 0), newSize);
}

bool Button::SetTexture(std::string buttonTexturePath, SDL_Renderer *ren) {

    return button.SetTexture(buttonTexturePath, ren);
}

void Button::Update(Vector2 <int> mousePosition, bool mouseLeftClick) {

    if ((mousePosition.x >= positionButton.x) && (mousePosition.x <= (positionButton.x + sizeButton.x)) &&
        (mousePosition.y >= positionButton.y) && (mousePosition.y <= (positionButton.y + sizeButton.y))) {

        if (mouseLeftClick) {

            this->mouseLeftClick = true;
            button.SetAlpha(255);
            return;
        }

        this->mouseLeftClick = false;
        button.SetAlpha(230);
        return;
    }

    button.SetAlpha(200);
    this->mouseLeftClick = false;
}

bool Button::IsButtonLeftClick() {

    return mouseLeftClick;
}

Vector2 <int> Button::GetPosition() {

    return positionButton;
}

Vector2 <unsigned> Button::GetSize() {

    return sizeButton;
}

Rectangle *Button::GetButton() {

    return &button;
}
