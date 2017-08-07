#ifndef BRICKMANAGER_H
#define BRICKMANAGER_H

#include <SDL.h>

#include "include/brick.h"
#include "include/rectangle.h"
#include "include/vector2.h"
#include "include/scoresysytem.h"

#include <vector>

struct BrickInfo {

    int         health;
    std::string pathTexture;
};

struct BrickPattern {
    Vector2 <float> position;
    BrickType       brickType;
};

class BrickManager {

    Vector2 <unsigned>      brickSize;
    std::vector <Brick*>    bricks;
    std::vector <BrickInfo> brickInfo;

    void ClearBricks();
    void RemoveBrick(std::vector <Brick*>::iterator &it);
public:

    BrickManager();
    ~BrickManager();

    void Update(ScoreSystem &scoreSystem);
    bool SetBricks(std::vector <BrickPattern> bricksPatterns, SDL_Renderer *ren);

    std::vector <Rectangle*> &GetBricksRect();
    std::vector <Brick*> &GetBricks();
    Vector2 <unsigned> GetBrickSize();
    unsigned GetBricksNumber();

};

#endif // BRICKMANAGER_H
