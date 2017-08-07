#include "include/border.h"

Border::Border() {

}

void Border::SetPositions(Vector2 <float> corner1, Vector2 <float> corner2) {

    this->corner1 = corner1;
    this->corner2 = corner2;
}

Line Border::GetDownLine() {

    return Line(Vector2 <float> (corner1.x, corner2.y), corner2);
}
