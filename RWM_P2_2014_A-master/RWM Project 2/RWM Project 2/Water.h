#ifndef _WATER_h_
#define _WATER_h_


#include "BaseObject.h"
#include <vector>
#include <set>




class Water : BaseObject
{
private:
	SDL_Rect m_position; 
	b2Body* body;
	SDL_Texture* m_texture; 

	void Update(SDL_Event);
public:
	
	bool inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p);
	b2Vec2 intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e);

	Water::Water(int x,int y,int width,int height,b2World*);
	b2Body* getBody();
	SDL_Rect getPosition();
	void Render( SDL_Renderer* render,b2Vec2 offset);

	bool findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, vector<b2Vec2>& outputVertices);
	b2Vec2 ComputeCentroid(vector<b2Vec2> vs, float& area);
};

#endif 
