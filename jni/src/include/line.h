#ifndef LINE_H
#define LINE_H

#include "include/vector2.h"

struct Line {

    Vector2 <float> start;
    Vector2 <float> end;

    Line() {}

    Line(Vector2 <float> start, Vector2 <float> end) {

        this->start = start;
        this->end   = end;
    }
};

#endif // LINE_H
