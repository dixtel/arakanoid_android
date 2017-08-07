#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "include/rectangle.h"
#include "include/vector2.h"
#include "include/logsdlerror.h"
#include "include/CleanUp.h"

#include <string>

//TODO Memory lost somewhere here.

class Text {

    Rectangle        rect;

    Vector2 <float>  position;
    std::string      text;
    std::string      pathToFont;
    unsigned         size;
    SDL_Color        color;
    TTF_Font        *font;
    SDL_Renderer    *ren;

    bool isChanged;

    void Update();
public:
    Text(SDL_Renderer *ren);
    ~Text();

    void SetPosition(Vector2 <float> position);
    void SetText(const std::string text);
    void SetSize(unsigned size);
    void SetColor(SDL_Color color);
    void SetFont(std::string pathToFont);

    Rectangle *Get();
};

#endif // TEXT_H
