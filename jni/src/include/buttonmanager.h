#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H

#include <SDL.h>

#include "include/button.h"
#include "include/vector2.h"
#include "include/logsdlerror.h"

#include <map>
#include <utility>
#include <vector>
#include <iostream>


class ButtonManager {

    std::map <std::string, Button*> buttons;
public:

    ~ButtonManager();

    void Update(Vector2 <int> mousePosition, bool mouseLeftClick);
    bool CreateButton(std::string nameButton, Vector2 <int> positionButton, Vector2 <unsigned> sizeButton, std::string buttonTexture, SDL_Renderer *ren);
    bool IsLeftClick(std::string nameButton);
    void ChangeButtonPosition(std::string nameButton, Vector2 <int> position);
    void RemoveButton(std::string nameButton);

    std::vector <Rectangle*> &GetButtons();
};

#endif // BUTTONMANAGER_H
