#include "include/ballmanager.h"

BallManager::BallManager() {

}

void BallManager::Init(float ballRadius, const std::string pathTexture, SDL_Renderer *ren) {

	this->ren               = ren;
	this->ballRadius        = ballRadius;
	this->pathToBallTexture = pathTexture;
}

void BallManager::UpdateBallsPhysics(float delta) {

	for (std::vector<Ball*>::iterator it = balls.begin(); it != balls.end(); ++it) {

		(*it)->UpdatePhysics(delta);
	}
}

void BallManager::UpdateBalls() {

	for (std::vector<Ball*>::iterator it = balls.begin(); it != balls.end(); ++it) {
		
		if ((*it) == nullptr) {

			it = balls.erase(it);

			UpdateBalls();

			break;
		}

		(*it)->UpdateBall();
	}
}

void BallManager::AddBall(Vector2 <float> pos) {

	Ball *ball = new Ball();

	if(!ball->Init(pos, ballRadius, pathToBallTexture, ren)) {

		delete ball;
		ball = nullptr;

		SDL_Log("Cannot init ball (BallManager) path: %s", pathToBallTexture.c_str());

		return;
	}

	balls.push_back(ball);
}

void BallManager::DeleteBall(Ball *ball) {

	std::vector<Ball*>::iterator it;
	it = std::find(balls.begin(), balls.end(), ball);
	
	if (it != balls.end()) {

		delete *it;
		*it = nullptr;

		return;
	}

	SDL_Log("Cannot find ball to delete (BallManager)");
}

void BallManager::DeleteBalls() {

	for (std::vector<Ball*>::iterator it = balls.begin(); it != balls.end(); ++it) {
		
		delete *it;
		*it = nullptr;

		balls.erase(it);
	}
}

void BallManager::ResetBalls() {

	for (std::vector<Ball*>::iterator it = balls.begin(); it != balls.end(); ++it) {
		
		if ((*it) != nullptr) {

			(*it)->Reset();
		}
	}
}

unsigned BallManager::GetBallNumber() {

	unsigned num = 0;

	for (std::vector<Ball*>::iterator it = balls.begin(); it != balls.end(); ++it) {
		
		if ((*it) != nullptr) {

			++num;
		}
	}

	return num;
}

Ball *BallManager::GetBall(unsigned ballNumber) {

	if (ballNumber > GetBallNumber() - 1) {

		return nullptr;
	}

	return balls[ballNumber];
}
