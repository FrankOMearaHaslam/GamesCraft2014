#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class RenderTexture
{

private:

	SDL_Texture* m_texture; 
public:
	
    //Initializes variables
    RenderTexture();
    //Deallocates memory
    ~RenderTexture();

	SDL_Texture* loadPNG(std::string path, SDL_Renderer* gRenderer);
    ////Renders texture at given point
    void render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer, SDL_Texture* text );

};

