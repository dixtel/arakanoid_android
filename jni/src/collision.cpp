#include "include/collision.h"

Vector2 <float> GetIntersectPosition(Vector2 <float> A1, Vector2 <float> A2, Vector2 <float> B1, Vector2 <float> B2) {
    Vector2 <float> s1, s2;
    s1.x = A2.x - A1.x;
    s1.y = A2.y - A1.y;
    s2.x = B2.x - B1.x;
    s2.y = B2.y - B1.y;

    float s, t;
    s = (-s1.y * (A1.x - B1.x) + s1.x * (A1.y - B1.y)) / (-s2.x * s1.y + s1.x * s2.y);
    t = ( s2.x * (A1.y - B1.y) - s2.y * (A1.x - B1.x)) / (-s2.x * s1.y + s1.x * s2.y);

    if(s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // Collision detected

        float x = A1.x + (t * s1.x);
        float y = A1.y + (t * s1.y);

        return Vector2 <float> (x, y);
    }

    return Vector2 <float> (0, 0);
}

bool Collision::IsCollising(Player *player, Border *border) {

    if (player->position.x + player->size.x > border->corner2.x ||
        player->position.x < border->corner1.x) {

        return true;
    }

    return false;
}

bool Collision::IsCollising(Ball *ball, Border *border) {

    if ((ball->position.x + (2 * ball->radius)) > border->corner2.x || ball->position.x < border->corner1.x ||
        (ball->position.y + (2 * ball->radius)) > border->corner2.y || ball->position.y < border->corner1.y) {

        return true;
    }

    return false;
}

bool Collision::IsCollising(Ball *ball, Player *player) {

    if (ball->currentCenterPos.x > player->position.x - ball->radius && ball->currentCenterPos.x < player->position.x + player->size.x + ball->radius &&
        ball->currentCenterPos.y > player->position.y - ball->radius && ball->currentCenterPos.y < player->position.y + player->size.y + ball->radius) {

        return true;
    }

    return false;
}

bool Collision::IsCollising(Ball *ball, std::vector <Brick*> &bricks) {

    for (int i = 0; i < bricks.size(); ++i) {

        Vector2 <float> brickLeftCorrner = bricks[i]->position - ball->radius;
        Vector2 <float> brickRightCorrner = bricks[i]->position + Vector2 <float> (bricks[i]->size.x + ball->radius, bricks[i]->size.y + ball->radius);

        if (ball->currentCenterPos.x > brickLeftCorrner.x && ball->currentCenterPos.x < brickRightCorrner.x &&
            ball->currentCenterPos.y > brickLeftCorrner.y && ball->currentCenterPos.y < brickRightCorrner.y) {

            return true;
        }
    }

    return false;
}

bool Collision::IsCollising(Ball *ball, Line line) {

    if (GetIntersectPosition(ball->oldCenterPos + Vector2 <float> (-ball->radius, ball->radius), ball->currentCenterPos + Vector2 <float> (-ball->radius, ball->radius), line.start, line.end) != Vector2 <float> (0, 0)) {

        return true;
    }
    else if (GetIntersectPosition(ball->oldCenterPos + Vector2 <float> (ball->radius, ball->radius), ball->currentCenterPos + Vector2 <float> (ball->radius, ball->radius), line.start, line.end) != Vector2 <float> (0, 0)) {

        return true;
    }

    return false;
}

void Collision::SetCollision(Player *player, Border *border) {

    if (player->position.x + player->size.x > border->corner2.x) {

        player->position.x = border->corner2.x - player->size.x ;
        player->velocity = 0;
    }
    else if (player->position.x < border->corner1.x) {

        player->position.x = border->corner1.x;
        player->velocity = 0;
    }
}

void Collision::SetCollision(Ball *ball, Border *border) {

   if (ball->position.x + 2 * ball->radius > border->corner2.x) {

       ball->position.x = border->corner2.x - 2 * ball->radius - 1;
       ball->velocity = Vector2 <float> (0, ball->velocity.y);
       ball->InvertXVelocity();
   }

   if (ball->position.x < border->corner1.x) {

       ball->position.x = border->corner1.x + 1;
       ball->velocity = Vector2 <float> (0, ball->velocity.y);
       ball->InvertXVelocity();
   }

   if (ball->position.y + 2 * ball->radius > border->corner2.y) {

       ball->position.y = border->corner2.y - 2 * ball->radius;
       ball->velocity = Vector2 <float> (ball->velocity.x, 0);
       ball->InvertYVelocity();
   }

   if (ball->position.y < border->corner1.y) {

       ball->position.y = border->corner1.y;
       ball->velocity = Vector2 <float> (ball->velocity.x, 0);
       ball->InvertYVelocity();
   }
}

void Collision::SetCollision(Ball *ball, Player *player) {

    Vector2 <float> playerPointA = player->position - ball->radius;
    Vector2 <float> playerPointB = player->position + Vector2 <float> (player->size.x + ball->radius, -ball->radius) ;
    Vector2 <float> playerPointC = player->position + Vector2 <float> (player->size.x + ball->radius, player->size.y + ball->radius);
    Vector2 <float> playerPointD = player->position + Vector2 <float> (-ball->radius, player->size.y + ball->radius);

    if (GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, playerPointA, playerPointB) != Vector2 <float> (0, 0)) {

        Vector2 <float> intersectPos = GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, playerPointA, playerPointB);
        ball->position = intersectPos - ball->radius;
        ball->velocity = Vector2 <float> (ball->velocity.x, 0);

        float centerBallX = playerPointB.x - (playerPointB.x - ball->position.x);
        float playerDistanceToLeftCorr = centerBallX - playerPointA.x;
        float playerDistanceToRightCorr = playerPointB.x - centerBallX;

        ball->InvertYByPlayer(playerDistanceToLeftCorr, playerDistanceToRightCorr);

    }
    else if (GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, playerPointB, playerPointC) != Vector2 <float> (0, 0)) {

        Vector2 <float> intersectPos = GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, playerPointB, playerPointC);
        ball->position = intersectPos - ball->radius;
        ball->velocity = Vector2 <float> (0, ball->velocity.y);
        ball->InvertXVelocity();
    }
    else if (GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, playerPointC, playerPointD) != Vector2 <float> (0, 0)) {

        Vector2 <float> intersectPos = GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, playerPointC, playerPointD);
        ball->position = intersectPos - ball->radius;
        ball->velocity = Vector2 <float> (ball->velocity.x, 0);

        ball->InvertYVelocity();

    }
    else if (GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, playerPointD, playerPointA) != Vector2 <float> (0, 0)) {

        Vector2 <float> intersectPos = GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, playerPointD, playerPointA);
        ball->position = intersectPos - ball->radius;
        ball->velocity = Vector2 <float> (0, ball->velocity.y);
        ball->InvertXVelocity();
    }
}

void Collision::SetCollision(Ball *ball, std::vector <Brick*> &bricks) {

    int collisingCounter = 0;

    for (int i = 0; i < bricks.size(); ++i) {

        Vector2 <float> brickPointA = bricks[i]->position - ball->radius;
        Vector2 <float> brickPointB = bricks[i]->position + Vector2 <float> (bricks[i]->size.x + ball->radius, -ball->radius);
        Vector2 <float> brickPointC = bricks[i]->position + Vector2 <float> (bricks[i]->size.x + ball->radius, bricks[i]->size.y + ball->radius);
        Vector2 <float> brickPointD = bricks[i]->position + Vector2 <float> (-ball->radius, bricks[i]->size.y + ball->radius);

        if (GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, brickPointA, brickPointB) !=  Vector2 <float> (0 ,0)) {

            bricks[i]->DecreaseHealth(ball->GetHitPower());

            if (collisingCounter >= 1) {

                continue;
            }

            Vector2 <float> intersectPos = GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, brickPointA, brickPointB);
            ball->position = intersectPos - ball->radius;
            ball->velocity = Vector2 <float> (ball->velocity.x, 0);
            ball->InvertYVelocity();

            collisingCounter++;
        }
        else if (GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, brickPointB, brickPointC) !=  Vector2 <float> (0 ,0)) {

            bricks[i]->DecreaseHealth(ball->GetHitPower());

            if (collisingCounter >= 1) {

                continue;
            }

            Vector2 <float> intersectPos = GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, brickPointB, brickPointC);
            ball->position = intersectPos - ball->radius;
            ball->velocity = Vector2 <float> (0, ball->velocity.y);
            ball->InvertXVelocity();

            collisingCounter++;
        }
        else if (GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, brickPointC, brickPointD) !=  Vector2 <float> (0 ,0)) {

            bricks[i]->DecreaseHealth(ball->GetHitPower());

            if (collisingCounter >= 1) {

                continue;
            }

            Vector2 <float> intersectPos = GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, brickPointC, brickPointD);
            ball->position = intersectPos - ball->radius;
            ball->velocity = Vector2 <float> (ball->velocity.x, 0);
            ball->InvertYVelocity();

            collisingCounter++;
        }
        else if (GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, brickPointD, brickPointA) !=  Vector2 <float> (0 ,0)) {

            bricks[i]->DecreaseHealth(ball->GetHitPower());

            if (collisingCounter >= 1) {

                continue;
            }

            Vector2 <float> intersectPos = GetIntersectPosition(ball->oldCenterPos, ball->currentCenterPos, brickPointD, brickPointA);  
            ball->position = intersectPos - ball->radius;
            ball->velocity = Vector2 <float> (0, ball->velocity.y);
            ball->InvertXVelocity();

            collisingCounter++;
        }
    }
}

