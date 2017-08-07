#include "include/brickmanager.h"

BrickManager::BrickManager() {

    BrickInfo type_brick_1 = {1, "res/images/brick_green.png"};
    BrickInfo type_brick_2 = {2, "res/images/brick_yellow.png"};
    BrickInfo type_brick_3 = {3, "res/images/brick_red.png"};

    brickInfo.push_back(type_brick_1);
    brickInfo.push_back(type_brick_2);
    brickInfo.push_back(type_brick_3);

    brickSize.x = 60;
    brickSize.y = 20;
}

BrickManager::~BrickManager() {

    ClearBricks();
}

void BrickManager::ClearBricks() {

    for (int i = 0; i < bricks.size(); ++i) {

        delete bricks[i];
        bricks[i] = nullptr;
    }

    bricks.clear();
}

void BrickManager::RemoveBrick(std::vector <Brick*>::iterator &it) {

    delete *it;
    *it = nullptr;
    bricks.erase(it);
}

void BrickManager::Update(ScoreSystem &scoreSystem) {

    for (std::vector <Brick*>::iterator it = bricks.begin(); it != bricks.end(); ++it) {

        if ((*it)->GetHelath() <= 0) {

            scoreSystem.IncreaseCurrentScore((*it)->GetType());
            RemoveBrick(it);
            Update(scoreSystem);

            break;
        }
    }
}

bool BrickManager::SetBricks(std::vector <BrickPattern> bricksPatterns, SDL_Renderer *ren) {

    ClearBricks();

    for (int i = 0; i < bricksPatterns.size(); ++i) {

        Vector2 <float> brickPosition = bricksPatterns[i].position;
        BrickType brickType = bricksPatterns[i].brickType;

        bricks.push_back(new Brick());

        if (!bricks[bricks.size() - 1]->Init(brickPosition, brickSize, brickInfo[brickType].health, brickInfo[brickType].pathTexture, brickType, ren)) {

            std::cout << "Cannot set brick. (BrickManager)" << std::endl;

            std::vector <Brick*>::iterator it = bricks.end();
            RemoveBrick(it);

            return false;
        }
    }

    return true;
}

std::vector <Rectangle*> &BrickManager::GetBricksRect() {

    static std::vector <Rectangle*> rectangle_bricks;

    rectangle_bricks.clear();

    for (int i = 0; i < bricks.size(); ++i) {

        rectangle_bricks.push_back(bricks[i]->Get());
    }

    return rectangle_bricks;
}

std::vector <Brick*> &BrickManager::GetBricks() {

    return bricks;
}

Vector2 <unsigned> BrickManager::GetBrickSize() {

    return brickSize;
}

unsigned BrickManager::GetBricksNumber() {

    return bricks.size();
}
