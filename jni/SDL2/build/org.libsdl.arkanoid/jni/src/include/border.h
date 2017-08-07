#ifndef BORDER_H
#define BORDER_H

#include <SDL2/SDL.h>

#include "include/vector2.h"
#include "include/line.h"


class Border {

    friend class Collision;

    Vector2 <float> corner1; // Left top.
    Vector2 <float> corner2; // Right down.

public:

    Border();

    void SetPositions(Vector2 <float> corner1, Vector2 <float> corner2);

    Line GetDownLine();
};

#endif // BORDER_H
