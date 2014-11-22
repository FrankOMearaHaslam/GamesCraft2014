#include "Game.h"


//int Game::SCREEN_WIDTH = 640; 
//int Game::SCREEN_HEIGHT = 480;

Game::Game(){}

Game::Game(SDL_Renderer* renderer,b2World* world)
{
	mRenderer = renderer;
	mWorld = world;
	



}

Game::~Game(void)
{
}


void Game::Update(std::clock_t timeElapsed)
{
	
	float32 timeStep = 0.1f / loopIterations;
	//float32 timeStep = 1.0f / 5.0f;

	int32 velocityIterations = 6;

	int32 positionIterations = 2;

	for(int i = 0; i < loopIterations; i++)
	{
		mWorld->Step(timeStep, velocityIterations, positionIterations);
		
	}
	
	//DestroyObjects();
	//ObjectManager::getManager()->Render(mRenderer);

	
}

