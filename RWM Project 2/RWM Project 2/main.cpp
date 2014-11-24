#include "SDL.h"
#include "Box2D\Box2D.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <ctime>
#include "Game.h"
#include "ContactListener.h"
#include "SDL_ttf.h"
#include "Enemy.h"
#include "Fish.h"
#include "FishingLine.h"

//Screen dimension constants 
//The window we'll be rendering to 
SDL_Window* window = NULL; 
//Event handler 
SDL_Event eHandler;
//The window renderer 
SDL_Renderer* renderer = NULL; 
//Current displayed texture 
bool createdWorld = false;
SDL_Rect stretchRect; 
Game game;


//Starts up SDL and creates window 
bool init(); 
//Loads media 
bool loadMedia(); 
//Frees media and shuts down SDL 
void close();
SDL_Texture* loadTexture( std::string path );

SDL_Event e;

SDL_Texture* waterTex;

SDL_Texture* enemyTexture;

SDL_Texture* fishTexture;

Water* water;
Enemy* enemy;
Enemy* enemy2;

b2Vec2 gravity =  b2Vec2(0.0f,0.50f);
b2World* world = new b2World(gravity);

b2Body *gFloor;
b2BodyDef gFloorDef;	
b2PolygonShape gFloorShape;
b2FixtureDef gFloorFixture;

Player* player;
SDL_Texture* playerTex;
SDL_Texture* loanTex;
FishingLine* fishingLine;

vector<Fish*> fishes;
using namespace std;
Mix_Music* music = NULL;

Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

bool init() 
{ 
	//Initialization flag 
	bool success = true; 

	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = Game::SCREEN_WIDTH; 
	stretchRect.h = Game::SCREEN_HEIGHT;

	string* name = new string("Ground");
	gFloorDef.userData = name;
	gFloorDef.position.Set(0,Game::SCREEN_HEIGHT);
	gFloorDef.type = b2_staticBody;	
	gFloor = world->CreateBody(&gFloorDef);
	gFloorShape.SetAsBox( Game::SCREEN_WIDTH, 2);
	gFloorFixture.friction=0;
	gFloorFixture.shape = &gFloorShape;
	gFloorFixture.density = 1;
	gFloor->CreateFixture(&gFloorFixture);

	srand(time(NULL));
	/*
	boxDef.userData = name;
	boxDef.position.Set(x, y);
	boxDef.type = type;	
	box = world->CreateBody(&boxDef);
	boxShape.SetAsBox( w / 2, h / 2);
	boxFixture.friction = friction;
	boxFixture.shape = &boxShape;
	//boxFixture.density = 1;
	box->CreateFixture(&boxFixture);
	*/

	//Initialize SDL 

	SDL_INIT_AUDIO;
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		success = false; 
	} 
	else 
	{  
		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
		}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		window = SDL_CreateWindow( "Extreme Fishing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() ); 
			success = false; 
		} 
		else 
		{ 
			//Create renderer for window 
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ); 
			if( renderer == NULL ) 
			{ 
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() ); 
				success = false;
			} 
			else 
			{ 
				//Initialize renderer color 
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
				//Initialize PNG loading 
				int imgFlags = IMG_INIT_PNG; 
				if( !( IMG_Init( imgFlags ) & imgFlags  ) ) 
				{ 
					string a = IMG_GetError();
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false; 
				} 
			} 
		}
	} 
	 if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
	}
	music = Mix_LoadMUS( "images/audio.wav" );
    if( music == NULL )
    {
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
    }
	
	//Play the music





	return success; 
}



SDL_Texture* loadTexture( std::string path ) 
{ 
	//The final texture 
	SDL_Texture* newTexture = NULL; 
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) 
	{ 
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} 
	else 
	{
		//Create texture from surface pixels 
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); 
		if( newTexture == NULL ) 
		{ 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); 
		} 
		//Get rid of old loaded surface 
		SDL_FreeSurface( loadedSurface ); 
	} 
	return newTexture; 
}


bool loadMedia() 
{ 
	//Loading success flag 
	bool success = true; 

	waterTex = loadTexture("images/waterTexture.png");

	enemyTexture =  loadTexture("images/sharkgreen.png");
	playerTex = loadTexture("images/fisherman.png");
	loanTex = loadTexture("images/loanshark.png");
	fishTexture = loadTexture("images/fish1pink.png");


	//Load splash image 
	return success; 
}






void close() 
{ 
	//Free loaded image 
	//Destroy window 
	SDL_DestroyRenderer( renderer ); 
	SDL_DestroyWindow( window ); 
	window = NULL; 
	renderer = NULL; 
	//Quit SDL subsystems 
	IMG_Quit(); 
	SDL_Quit();
}

int random()
{
	int randomGen = (rand() % 1000) + 1;
	return randomGen;
}



int main( int argc, char* args[] ) 
{ 
	
	bool QUIT = false;
	if( !init() )
	{ 
		printf( "Failed to initialize!\n" ); 
	} 
	else 
	{ 
		//Load media 
		if( !loadMedia() )	
		{
			printf( "Failed to load media!\n" );
		}
		else
		{

			//b2Vec2 gravity =  b2Vec2(0.0f,0.0f);
			//b2Vec2 gravity =  b2Vec2(0.0f,0.50f);
			//b2Vec2 gravity =  b2Vec2(0.0f,0.0f);
			bool doSleep = true;
			//b2World* world = new b2World(gravity);

			world->SetContactListener(ContactListener::createListener());
			ContactListener::createListener()->setWorld(world);
			game = Game(renderer,world);
			ContactListener::createListener()->setGame(&game);

			//ObjectManager::getManager()->Initialise(world,&game);
			createdWorld = true;
			
			Mix_PlayMusic( music, -1 );

			enemy = new Enemy(world,100,600,enemyTexture);
			enemy2 = new Enemy(world, 1200, 600, loanTex);
			water = new Water(Game::SCREEN_WIDTH/2,(Game::SCREEN_HEIGHT-Game::SCREEN_HEIGHT/3),Game::SCREEN_WIDTH,Game::SCREEN_HEIGHT-(Game::SCREEN_HEIGHT/3),world,waterTex);

			for (int i = 0; i < 3; i++)
			{
				fishes.push_back(new Fish(600*i,water->getBody()->GetPosition().y - Game::SCREEN_HEIGHT/4 + 120 + 80*i,100,100,world,fishTexture,1, i));
			}
			player = new Player(world, playerTex);

			fishingLine = new FishingLine(player->GetBody()->GetPosition().x + 225, player->GetBody()->GetPosition().y - 75, 10, 10, world,renderer);

			std::clock_t mClock;
			mClock = std::clock();
			while(!QUIT)
			{
				if(((std::clock()-mClock)/(double)CLOCKS_PER_SEC) >= 1.0/480.0)
				{
					SDL_RenderClear(renderer);

					enemy->Update(player->GetBody()->GetPosition());//b2Vec2(0,0));

					enemy2->Update(player->GetBody()->GetPosition());

					player->Update(std::clock()-mClock);
					for (int i = 0; i < 3; i++)
					{
						fishes[i]->Update();
						ContactListener::me->fishStep(fishes[i],fishingLine->m_bodyHook);
					}

					fishingLine->updatePosition(player->GetBody()->GetPosition().x + 225, player->GetBody()->GetPosition().y - 75, 10, 10, world);
					fishingLine->Render(renderer);
					fishingLine->Update(std::clock()-mClock, renderer, world);

					player->Draw(renderer);
					water->Render(renderer);

					if(random() == 2)
					{
						if(enemy->GetPosition().y > 800)
						{
							if(enemy->attack == false)
							{
							
								enemy->attack = true;
							
							}
						}

					}
					else if(random() == 68)
					{
						if(enemy2->GetPosition().y > 800)
						{
							if(enemy2->attack == false)
							{
							
								enemy2->attack = true;
							
							}
						}

					}

					enemy->Draw(renderer,b2Vec2(0,0));
					enemy2->Draw(renderer,b2Vec2(0,0));
					for (int i = 0; i < 3; i++)
					{
						fishes[i]->Draw(renderer);
					}
					//enemy->Update();
					//KeyPresses::Update(e);
					game.Update(std::clock()-mClock);
					ContactListener::me->WaterStep(water);
					mClock = std::clock();
				}

				SDL_RenderPresent(renderer);
			}

			
		}
	}
	close();
	return 0;
}

