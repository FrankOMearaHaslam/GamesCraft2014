#pragma once

#include "Box2D\Box2D.h"
#include "BaseObject.h"
#include <vector>

class Fish : BaseObject 
{
public:
	Fish(int x,int y, int w, int h,b2World* world,SDL_Texture* texture, int dir, int ident);
	~Fish(void);
	void catchFish();
	void Update();
	void Draw(SDL_Renderer* gRenderer);
	
	b2Vec2 size;
	bool inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p);
	b2Vec2 intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e);
	bool findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, vector<b2Vec2>& outputVertices);
	b2Body* body;
private:
	int id;
	bool caught;

	SDL_Texture* m_texture; 
	int dirVel;
};

