#include "RenderTexture.h"
//Texture wrapper class


RenderTexture::RenderTexture()
{

}

//Deallocates memory
RenderTexture::~RenderTexture()
{

}

SDL_Texture* RenderTexture::loadPNG(std::string path, SDL_Renderer* gRenderer)
{
	////The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
	    SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return newTexture;
}
			   
		
//Renders texture at given point
void RenderTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip, SDL_Renderer* gRenderer, SDL_Texture* text) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad;
 	renderQuad.x = x;
	renderQuad.y = y;

	//Set clip rendering dimensions
	if( clip != 0 ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	else{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
 
	//Render to screen
	SDL_RenderCopyEx( gRenderer, text, clip, &renderQuad, angle, center, flip );
}


