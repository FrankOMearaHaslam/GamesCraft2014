#pragma once

#include "Box2D\Box2D.h"
#include "BaseObject.h"

class Fish : BaseObject 
{
public:
	Fish(int x,int y, int w, int h,b2World* world,SDL_Texture* texture, int dir);
	~Fish(void);

	void Update();
	void Draw(SDL_Renderer* gRenderer);
	b2Body *GetBody();
	b2Vec2 size;
private:
	b2Body* body;
	SDL_Texture* m_texture; 
	int dirVel;
};

