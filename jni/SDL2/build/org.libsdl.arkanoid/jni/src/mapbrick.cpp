#include "include/mapbrick.h"

MapBrick::MapBrick() {

    brick_w = 0;
    brick_h = 0;
    space_w = 0;
    space_h = 0;
}

void MapBrick::CreatePatterns() {

    for (int y = 0; y < bricksMap.size(); ++y) {

        for (int x = 0; x < bricksMap[y].size(); ++x) {

            BrickPattern pattern;

            if (x == 0) {

                pattern.position = Vector2 <float> (startPosition.x + space_w, startPosition.y + space_h + (y * brick_h + y * (2 * space_h)));
                pattern.brickType = bricksMap[y][x];
                brickPatterns.push_back(pattern);

                continue;
            }

            pattern.position = Vector2 <float> (brickPatterns[brickPatterns.size() - 1].position.x + brick_w + (2 * space_w), brickPatterns[brickPatterns.size() - 1].position.y);
            pattern.brickType = bricksMap[y][x];
            brickPatterns.push_back(pattern);
        }
    }
}

void MapBrick::SetRow(std::vector<BrickType> rowBricks) {

    bricksMap.push_back(rowBricks);
}

void MapBrick::Init(Vector2 <float> startPosition, const int brick_w, const int brick_h, const int space_w, const int space_h) {

    this->startPosition = startPosition;
    this->brick_w = brick_w;
    this->brick_h = brick_h;
    this->space_w = space_w;
    this->space_h = space_h;
}

bool MapBrick::LoadMap(const std::string path) {

    std::ifstream file;
    file.open(path);

    if (!file.is_open()) {

        return false;
    }

    bricksMap.clear();
    brickPatterns.clear();

    std::string line;
    int type;
    while (std::getline(file, line)) {

        std::vector <BrickType> rowBricks;

        std::stringstream stream;
        stream << line;

        while (stream >> type) {

            switch (type) {
            case 1:

                rowBricks.push_back(BrickType::type1);
                break;
            case 2:

                rowBricks.push_back(BrickType::type2);
                break;
            case 3:

                rowBricks.push_back(BrickType::type3);
                break;
            default:

                std::cout << "Eroor: map " << path << " have unknow brick type." << std::endl;
                break;
            }
        }

        SetRow(rowBricks);
    }

    CreatePatterns();

    return true;
}

std::vector <BrickPattern> MapBrick::GetBricksPatterns() {

    return brickPatterns;
}
