#include "include/state/pausestate.h"

PauseState::PauseState(unsigned width, unsigned height, StateMachine *stateMachne, SDL_Renderer *ren) {

    this->stateMachine = stateMachne;
    this->width        = width;
    this->height       = height;
    touchClick         = false;
    render             = new Render(ren);

    if (!buttonManager.CreateButton("Resume", Vector2 <int> (80, 480), Vector2 <unsigned> (500, 100), "res/buttons/buttonResume.png", render->GetRenderer())) {

        std::cout << "Cannot create \"Resume button\"." << std::endl;
    }

    if (!buttonManager.CreateButton("Menu", Vector2 <int> (80, 630), Vector2 <unsigned> (500, 100), "res/buttons/buttonMenu.png", render->GetRenderer())) {

        std::cout << "Cannot create \"Menu\" button." << std::endl;
    }


    if (!baseBackgroundImage.SetTexture("res/images/base_background.png", ren)) {

        std::cout << "Error: cannor load res/images/background.png." << std::endl;
    }


    baseBackgroundImage.SetPosition(Vector2 <float> (0, 0));
    baseBackgroundImage.SetSize(Vector2 <unsigned> (640, 960));
    baseBackgroundImage.SetClip();


    pauseText = std::unique_ptr <Text> (new Text(ren));
    pauseText->SetPosition(Vector2 <float> (200, 100));
    pauseText->SetSize(90);
    pauseText->SetColor(SDL_Color{255, 255, 255, 255});
    pauseText->SetText("Pause");
    pauseText->SetFont("res/fonts/pixel.ttf");


}

PauseState::~PauseState() {

    delete render;
    render = nullptr;
}

void PauseState::HandleEvent() {

    touchClick = false;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_FINGERMOTION) {

            touchPosition.x = event.tfinger.x * width;
            touchPosition.y = event.tfinger.y * height;
        }

        if (event.type == SDL_FINGERDOWN) {

            touchPosition.x = event.tfinger.x * width;
            touchPosition.y = event.tfinger.y * height;

            touchClick = true;
        }
    }
}

void PauseState::Update(float elapsedTime) {

    HandleEvent();

    buttonManager.Update(touchPosition, touchClick);

    if (buttonManager.IsLeftClick("Resume")) {

        stateMachine->Change(stateType::mainGameState);
    }
    else if (buttonManager.IsLeftClick("Menu")) {

        stateMachine->Change(stateType::mainMenuState);
    }

}

void PauseState::RenderScene() {

    render->Clear();
    render->Draw(&baseBackgroundImage);
    render->Draw(buttonManager.GetButtons());
    render->Draw(pauseText->Get());
    render->Display();
}

void PauseState::OnEnter() {

    std::cout << "Enter to Pause State" << std::endl;
}

void PauseState::OnExit() {

    std::cout << "Exit from Pause State" << std::endl;
}
