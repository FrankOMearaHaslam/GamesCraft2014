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
Player* player;
SDL_Texture* playerTex;
Water* water;

using namespace std;

bool init() 
{ 
	//Initialization flag 
	bool success = true; 

	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = Game::SCREEN_WIDTH; 
	stretchRect.h = Game::SCREEN_HEIGHT;

	//Initialize SDL 
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
		window = SDL_CreateWindow( "Dr. Where", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, SDL_WINDOW_SHOWN ); 
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
	playerTex = loadTexture("images/seesawBase.png");

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

			b2Vec2 gravity =  b2Vec2(0.0f,0.50f);
			//b2Vec2 gravity =  b2Vec2(0.0f,0.0f);
			bool doSleep = true;
			b2World* world = new b2World(gravity);
			world->SetContactListener(ContactListener::createListener());
			ContactListener::createListener()->setWorld(world);
			game = Game(renderer,world);
			ContactListener::createListener()->setGame(&game);

			//ObjectManager::getManager()->Initialise(world,&game);
			createdWorld = true;
			
			water = new Water(400,400,200,200,world,waterTex);
			player = new Player(world, playerTex);
			std::clock_t mClock;
			mClock = std::clock();
			while(!QUIT)
			{
				if(((std::clock()-mClock)/(double)CLOCKS_PER_SEC) >= 1.0/480.0)
				{
					SDL_RenderClear(renderer);
					player->Draw(renderer);
					water->Render(renderer);
					game.Update(std::clock()-mClock);
					//ContactListener::me->WaterStep(new Water(400,400,200,200,world,waterTex));
					mClock = std::clock();
				}
				SDL_RenderPresent(renderer);
			}

			
		}
	}
	close();
	return 0;
}