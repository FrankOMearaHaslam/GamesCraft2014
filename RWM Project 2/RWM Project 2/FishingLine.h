#pragma once

#include "BaseObject.h"
#include <vector>
#include <set>
#include "RenderTexture.h"
#include "KeyboardManager.h"

class FishingLine: BaseObject
{

private:

	SDL_Rect m_position; 
	b2Body* m_bodyHang;
	b2Body* m_bodyLine;
	
	SDL_Texture* m_texture;

	RenderTexture m_tHang;
	RenderTexture m_tLine;
	RenderTexture m_tHook;

	
	//b2Vec2 size;
	SDL_Rect position1;
	SDL_Rect position2;

	b2DistanceJoint* m_distanceJoint;
	b2Vec2 lineLength;

	

public:
	SDL_Texture* tHang;
	SDL_Texture* tLine;
	SDL_Texture* tHook;
	b2Body* m_bodyHook;
	float m_impulse;

public:
	FishingLine(int x,int y,int width,int height,b2World*,SDL_Renderer*, SDL_Texture* hang, SDL_Texture* line, SDL_Texture* hook);

	void updatePosition(int x,int y,int width,int height,b2World*);

	void Update(float timeElapsed);

	SDL_Rect getPosition();

	b2Body* getBody();

	float radian_to_degree(double radians);

	void createBody(b2World* world);

	void Render(SDL_Renderer* render);


	void CreateDistanceJoint(b2World *world, b2Body* body1,  b2Body* body2, b2Vec2 anchor1, b2Vec2 anchor2, bool collideConnected,
						               float length, float dampingRatio, float frequencyHz);

};