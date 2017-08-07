#include "include/state/mainmenustate.h"

MainMenuState::MainMenuState(unsigned width, unsigned height, StateMachine *stateMachne, SDL_Renderer *ren) {

    render = new Render(ren);
    this->stateMachine = stateMachne;

    this->width    = width;
    this->height   = height;
    exitGame       = false;
    mouseLeftClick = false;

    if (!baseBackgroungImage.SetTexture("res/images/base_background.png", ren)) {

        std::cout << "Error: cannor load res/images/background.png." << std::endl;
    }


    baseBackgroungImage.SetPosition(Vector2 <float> (0, 0));
    baseBackgroungImage.SetSize(Vector2 <unsigned> (640, 960));
    baseBackgroungImage.SetClip();

    welcomeText = std::unique_ptr <Text> (new Text(ren));
    welcomeText->SetPosition(Vector2 <float> (110, 100));
    welcomeText->SetSize(90);
    welcomeText->SetColor(SDL_Color{255, 215, 0, 255});
    welcomeText->SetText("Start play!");
    welcomeText->SetFont("res/fonts/pixel.ttf");
}

MainMenuState::~MainMenuState() {

    delete render;
    render = nullptr;
}

void MainMenuState::HandleEvent() {

    mouseLeftClick = false;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {

            exitGame = true;
        }

        if (event.type == SDL_MOUSEMOTION) {

            SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
        }

        if (event.type == SDL_MOUSEBUTTONDOWN) {

            if (event.button.button == SDL_BUTTON_LEFT) {

                mouseLeftClick = true;
            }
        }

    }

}

void MainMenuState::Update(float elapsedTime) {

    HandleEvent();

    buttonManager.Update(mousePosition, mouseLeftClick);

    if (buttonManager.IsLeftClick("Start")) {

        stateMachine->Change(stateType::mainGameState);
    }
    else if (buttonManager.IsLeftClick("Exit")) {

        exitGame = true;
    }

}

void MainMenuState::RenderScene() {

    render->Clear();
    render->Draw(&baseBackgroungImage);
    render->Draw(buttonManager.GetButtons());
    render->Draw(welcomeText->Get());
    render->Display();
}

void MainMenuState::OnEnter() {

    std::cout << "Enter to Main Menu State" << std::endl;

    if (!buttonManager.CreateButton("Start", Vector2 <int> (80, 480), Vector2 <unsigned> (500, 100), "res/buttons/buttonStart.png", render->GetRenderer())) {

        std::cout << "Cannot create Start button." << std::endl;
    }

    if (!buttonManager.CreateButton("Exit", Vector2 <int> (80, 630), Vector2 <unsigned> (500, 100), "res/buttons/buttonExit.png", render->GetRenderer())) {

        std::cout << "Cannot create Exit button." << std::endl;
    }
}

void MainMenuState::OnExit() {

    std::cout << "Exit from Main Menu State" << std::endl;
}

bool MainMenuState::IsGameExit() {

    return exitGame;
}
