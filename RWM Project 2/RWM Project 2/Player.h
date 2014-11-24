#pragma once
#include "BaseObject.h"
#include "KeyboardManager.h"
#include <math.h>
using namespace std;
class Player : BaseObject
{
public:

	Player(b2World * world, SDL_Texture*);
	~Player(void);
	void Update(float timeElapsed);
	void Draw(SDL_Renderer* gRenderer);

	b2Body *GetBody();
	void Shoot();
	
	b2Vec2 size;
	bool Left;

private:
	
	b2Body* mBody;
	b2MassData* myMass;
	SDL_Texture* m_texture;

};

