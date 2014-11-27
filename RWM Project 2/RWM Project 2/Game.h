#pragma once

#include "Enemy.h"
#include <ctime>

using namespace std;
class Game
{
public:
	static const int SCREEN_WIDTH = 1600; 
	static const int SCREEN_HEIGHT = 900;
	static const int loopIterations = 1;
	Game();
	Game(SDL_Renderer* renderer,b2World* world);
	~Game(void);
	b2World* mWorld;
	SDL_Renderer* mRenderer;
	void Update(std::clock_t timeElapsed);
	
	

private:
	float shotTime;
};

