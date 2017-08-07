#include "include/state/maingamestate.h"

MainGameState::MainGameState(unsigned width, unsigned height, StateMachine *stateMachne, SDL_Renderer *ren) {

    this->stateMachine = stateMachne;
    this->width        = width;
    this->height       = height;
    winGame            = false;
    exitGame           = false;
    render             = new Render(ren);

    if (!player.Init(Vector2 <float> (width / 2 - 75 / 2, height - (height/10)), Vector2 <unsigned> (75, 25), "res/images/player.png", ren)) {

        std::cout << "Error: Cannot init Player." << std::endl;
        stateMachne->Change(stateType::mainMenuState);
    }

    if (!ball.Init(Vector2 <float> (width / 2 - 10, height - height / 6), 10, "res/images/ball.png", ren)) {

        std::cout << "Error: Cannot init Ball." << std::endl;
        stateMachne->Change(stateType::mainMenuState);
    }
    if (!scoreSystem.Init("res/config/score.txt")) {

        std::cout << "Error: Cannot init ScoreSystem." << std::endl;
        stateMachne->Change(stateType::mainMenuState);
    }

    mapBrick.Init(Vector2 <float> (10, 190), brickManager.GetBrickSize().x, brickManager.GetBrickSize().y, 1, 1);

    border.SetPositions(Vector2 <float> (10, 110), Vector2 <float> (630, 950));


    // Buttons

    // TODO move buttons error to ButtonManager class;
    if (!buttonManager.CreateButton("PauseIcon", Vector2 <int> (555, 15), Vector2 <unsigned> (65, 65), "res/buttons/buttonPauseIcon.png", render->GetRenderer())) {

        std::cout << "Cannot create \"Pause Icon\" button." << std::endl;
    }


    // Images
    if (!backgroungImage.SetTexture("res/images/background.png", ren)) {

        std::cout << "Error: cannor load res/images/background.png." << std::endl;
    }


    backgroungImage.SetPosition(Vector2 <float> (10, 100));
    backgroungImage.SetSize(Vector2 <unsigned> (620, 840));
    backgroungImage.SetClip();

    if (!baseBackgroungImage.SetTexture("res/images/base_background.png", ren)) {

        std::cout << "Error: cannor load res/images/background.png." << std::endl;
    }


    baseBackgroungImage.SetPosition(Vector2 <float> (0, 0));
    baseBackgroungImage.SetSize(Vector2 <unsigned> (640, 960));
    baseBackgroungImage.SetClip();


    if (!scoreboardImage.SetTexture("res/images/scoreboard.png", ren)) {

        std::cout << "Error: cannor load res/images/scoreboard.pngg." << std::endl;
    }


    scoreboardImage.SetPosition(Vector2 <float> (0, 0));
    scoreboardImage.SetSize(Vector2 <unsigned> (640, 90));
    scoreboardImage.SetClip();


    if (!pipeImage.SetTexture("res/images/pipe.png", ren)) {

        std::cout << "Error: cannor load res/images/pipe.png." << std::endl;
    }


    pipeImage.SetPosition(Vector2 <float> (0, 90));
    pipeImage.SetSize(Vector2 <unsigned> (640, 860));
    pipeImage.SetClip();

    // Maps
    currentMapNumber = 0;
    numbersOfMaps    = 5;

    pathsToMaps.push_back("res/maps/map1.txt");
    pathsToMaps.push_back("res/maps/map2.txt");
    pathsToMaps.push_back("res/maps/map3.txt");
    pathsToMaps.push_back("res/maps/map4.txt");
    pathsToMaps.push_back("res/maps/map5.txt");

    // Texts
    levelNumberText = std::unique_ptr <Text> (new Text(ren));
    levelNumberText->SetPosition(Vector2 <float> (20, 10));
    levelNumberText->SetSize(35);
    levelNumberText->SetColor(SDL_Color{255, 255, 255, 235});
    levelNumberText->SetText("LevelNumber 1");
    levelNumberText->SetFont("res/fonts/pixel.ttf");

    currentPointsText = std::unique_ptr <Text> (new Text(ren));
    currentPointsText->SetPosition(Vector2 <float> (20, 45));
    currentPointsText->SetSize(35);
    currentPointsText->SetColor(SDL_Color{255, 255, 255, 235});
    currentPointsText->SetText("Points 0");
    currentPointsText->SetFont("res/fonts/pixel.ttf");

    bestPointsText = std::unique_ptr <Text> (new Text(ren));
    bestPointsText->SetPosition(Vector2 <float> (200, 45));
    bestPointsText->SetSize(35);
    bestPointsText->SetColor(SDL_Color{255, 255, 255, 235});
    bestPointsText->SetText("Best score 0");
    bestPointsText->SetFont("res/fonts/pixel.ttf");
}

MainGameState::~MainGameState() {

    delete render;
    render = nullptr;
}

void MainGameState::HandleEvent() {

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

        if (event.type == SDL_KEYDOWN) {

            if (event.key.keysym.sym == SDLK_RIGHT) {

                player.MoveRight(true);
            }

            if (event.key.keysym.sym == SDLK_LEFT) {

                player.MoveLeft(true);
            }
        }

        if (event.type == SDL_KEYUP) {

            if (event.key.keysym.sym == SDLK_RIGHT) {

                player.MoveRight(false);
            }

            if (event.key.keysym.sym == SDLK_LEFT) {

                player.MoveLeft(false);
            }
        }

    }
}

void MainGameState::Update(float elapsedTime) {

    HandleEvent();

    player.UpdatePhysics(elapsedTime);
    ball.UpdatePhysics(elapsedTime);
    buttonManager.Update(mousePosition, mouseLeftClick);

    if (buttonManager.IsLeftClick("PauseIcon")) {

        stateMachine->Change(stateType::pauseState);
    }

    // colision //

    if (collision.IsCollising(&player, &border)) {

        collision.SetCollision(&player, &border);
    }

    if (collision.IsCollising(&ball, &border)) {

        if (collision.IsCollising(&ball, border.GetDownLine())) {

            currentMapNumber = 0;
            mapBrick.LoadMap(pathsToMaps[currentMapNumber]);
            brickManager.SetBricks(mapBrick.GetBricksPatterns(), render->GetRenderer());
            ball.Reset();
            player.Reset();
            scoreSystem.ResetCurrentScore();
        }

        collision.SetCollision(&ball, &border);
    }

    if (collision.IsCollising(&ball, &player)) {

        collision.SetCollision(&ball, &player);
    }

    if (collision.IsCollising(&ball, brickManager.GetBricks())) {

        collision.SetCollision(&ball, brickManager.GetBricks());
    }

    if (brickManager.GetBricksNumber() <= 0) {

        currentMapNumber++;

        if (currentMapNumber >= numbersOfMaps) {

            winGame = true;
            currentMapNumber = 0;
        }


        mapBrick.LoadMap(pathsToMaps[currentMapNumber]);
        brickManager.SetBricks(mapBrick.GetBricksPatterns(), render->GetRenderer());
        ball.Reset();
        player.Reset();
    }


    levelNumberText->SetText("Level " + std::to_string(currentMapNumber + 1));
    currentPointsText->SetText("Points " + std::to_string(scoreSystem.GetCurrentScore()));
    bestPointsText->SetText("Best score " + std::to_string(scoreSystem.GetBestScore()));
    

    brickManager.Update(scoreSystem);
    player.UpdatePlayer();
    ball.UpdateBall();
}

void MainGameState::RenderScene() {

    render->Clear();
    render->Draw(&baseBackgroungImage);
    render->Draw(&backgroungImage);
    render->Draw(&scoreboardImage);
    render->Draw(&pipeImage);
    render->Draw(player.Get());
    render->Draw(ball.Get());
    render->Draw(brickManager.GetBricksRect());
    render->Draw(levelNumberText->Get());
    render->Draw(currentPointsText->Get());
    render->Draw(bestPointsText->Get());
    render->Draw(buttonManager.GetButtons());
    render->Display();
}

void MainGameState::OnEnter() {

    if (!mapBrick.LoadMap("res/maps/map1.txt")) {

        std::cout << "Error: load map res/maps/map1.txt" << std::endl;
        stateMachine->Change(stateType::mainMenuState);
    }

    brickManager.SetBricks(mapBrick.GetBricksPatterns(), render->GetRenderer());

    std::cout << "Main game state enter." << std::endl;
}

void MainGameState::OnExit() {

    std::cout << "Main game state on exit." << std::endl;

    scoreSystem.ResetCurrentScore();
    scoreSystem.Save();
}

bool MainGameState::IsGameExit() {

    return exitGame;
}
