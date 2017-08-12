#ifndef MAPBRICK_H
#define MAPBRICK_H

#include <SDL.h>

#include "include/vector2.h"
#include "include/brickmanager.h"
#include "include/logerror.h"
#include "include/file.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>


class MapBrick {

    Vector2 <float> startPosition;
    int brick_w;
    int brick_h;
    int space_w;
    int space_h;

    std::vector <BrickPattern> brickPatterns;
    std::vector <std::vector <BrickType>> bricksMap;

    void CreatePatterns();
    void SetRow(std::vector<BrickType> rowBricks);
public:

    MapBrick();

    void Init(Vector2 <float> startPosition, const int brick_w, const int brick_h, const int space_w, const int space_h);
    void Clear();
    bool LoadMap(const std::string path);

    std::vector <BrickPattern> GetBricksPatterns();
};

#endif // MAPBRICK_H
