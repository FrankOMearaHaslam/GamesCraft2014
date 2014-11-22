#pragma once
#include "BaseObject.h"
#include <math.h>
using namespace std;
class Player : BaseObject
{
public:
	Player(b2World * world);
	~Player(void);
	void Update(float timeElapsed);
	void Draw(SDL_Renderer* gRenderer, b2Vec2 offset);
	b2Body *GetBody();
	void Shoot();
	
	b2Vec2 size;
	bool Left;
private:
	b2Body* mBody;
	b2MassData* myMass;
};

