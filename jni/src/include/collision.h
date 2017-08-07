#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>

#include "include/player.h"
#include "include/ball.h"
#include "include/border.h"
#include "include/vector2.h"
#include "include/brick.h"
#include "include/line.h"

#include <iostream>
#include <vector>


class Collision {

public:

    bool IsCollising(Player *player, Border *border);
    bool IsCollising(Ball *ball, Border *border);
    bool IsCollising(Ball *ball, Player *player);
    bool IsCollising(Ball *ball, std::vector <Brick*> &bricks);
    bool IsCollising(Ball *ball, Line line);
    void SetCollision(Player *player, Border *border);
    void SetCollision(Ball *ball, Border *border);
    void SetCollision(Ball *ball, Player *player);
    void SetCollision(Ball *ball, std::vector <Brick*> &bricks);
};

#endif // COLLISION_H
