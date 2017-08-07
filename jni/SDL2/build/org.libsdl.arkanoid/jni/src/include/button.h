#ifndef BUTTON_H
#define BUTTON_H

#include "include/rectangle.h"
#include "include/vector2.h"

class Button {

    Rectangle button;
    Vector2 <int> positionButton;
    Vector2 <unsigned> sizeButton;

    bool mouseLeftClick = false;
public:

    void SetPosition(Vector2 <int> newPosition);
    void SetSize(Vector2 <unsigned> newSize);
    bool SetTexture(std::string buttonTexturePath, SDL_Renderer *ren);

    void Update(Vector2 <int> mousePosition, bool mouseLeftClick);
    bool IsButtonLeftClick();

    Vector2 <int> GetPosition();
    Vector2 <unsigned> GetSize();
    Rectangle *GetButton();
};

#endif // BUTTON_H
