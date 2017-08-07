#include "include/buttonmanager.h"

ButtonManager::~ButtonManager() {

    for (std::map <std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {

        delete it->second;
        it->second = nullptr;
    }

    buttons.clear();
}

void ButtonManager::Update(Vector2 <int> mousePosition, bool mouseLeftClick) {

    for (std::map <std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {

        it->second->Update(mousePosition, mouseLeftClick);
    }
}

bool ButtonManager::CreateButton(std::string nameButton, Vector2 <int> positionButton, Vector2 <unsigned> sizeButton, std::string buttonTexture, SDL_Renderer *ren) {

    if (buttons.find(nameButton) != buttons.end()) {

        std::cout << "Button name: " << nameButton << " is already exists." << std::endl;
        return false;
    }


    Button *button = new Button;
    button->SetPosition(positionButton);
    button->SetSize(sizeButton);

    if (!button->SetTexture(buttonTexture, ren)) {

        LogSDLError(std::cout, "SetTexture");

        delete button;
        button = nullptr;

        return false;
    }


    buttons.insert(make_pair(nameButton, button));

    return true;
}

bool ButtonManager::IsLeftClick(std::string nameButton) {

    for (std::map <std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {

        if (it->first == nameButton) {

            return it->second->IsButtonLeftClick();
        }
    }

    std::cout << "Button name are not exists." << std::endl;
    return false;
}

void ButtonManager::ChangeButtonPosition(std::string nameButton, Vector2 <int> position) {

    for (std::map <std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {

        if (it->first == nameButton) {

            it->second->SetPosition(position);
            return;
        }
    }
}

void ButtonManager::RemoveButton(std::string nameButton) {

    for (std::map <std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {

        if (it->first == nameButton) {

            delete it->second;
            it->second = nullptr;

            buttons.erase(it);
            return;
        }
    }
}

std::vector <Rectangle*> &ButtonManager::GetButtons() {

    static std::vector <Rectangle*> bttns;

    if (!bttns.empty()) {

        bttns.clear();
    }

    for (std::map <std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it) {

        bttns.push_back(it->second->GetButton());
    }

    return bttns;
}

