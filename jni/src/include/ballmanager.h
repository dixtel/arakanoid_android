#ifndef BALLMANAGER_H
#define BALLMANAGER_H

#include <SDL.h>

#include "include/ball.h"
#include "include/vector2.h"

#include <vector>
#include <algorithm>


class BallManager {

	SDL_Renderer      *ren = nullptr;

	std::vector<Ball*> balls;
	std::string        pathToBallTexture;
	float              ballRadius;
public:

	BallManager();

	void Init(float ballRadius, const std::string pathTexture, SDL_Renderer *ren);
	void UpdateBallsPhysics(float delta);
	void UpdateBalls();
	void AddBall(Vector2 <float> pos);
	void DeleteBall(Ball *ball);
	void DeleteBalls();
	void ResetBalls();

	unsigned GetBallNumber();
	Ball *GetBall(unsigned ballNumber);
};

#endif // BALLMANAGER_H