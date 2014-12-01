#ifndef ENEMY_H
#define ENEMY_H

#include "Box2D\Box2D.h"
#include "BaseObject.h"
#include "Player.h"
#include <SDL_dev/SDL2-2.0.3/include/SDL_thread.h>

class Enemy : BaseObject{
public:

	Enemy(b2World*, int, int, SDL_Texture* enemyTex, Player* play);

	b2Vec2 GetPosition();
	b2Fixture* GetFixture();
	void EnemyDeath(b2World*);
	void Reset(b2World*, SDL_Renderer*);
	void Draw(SDL_Renderer*, b2Vec2);

	void Update();

	bool attack;

	b2Body* GetBody();
private:
	b2BodyDef myBodyDef;
	b2Body* dynamicBody;
	b2Fixture* mFix;
	b2CircleShape circleShape;
	b2FixtureDef fixtureDef;
	b2Vec2 size;
	float m_angle;
	bool alive;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	float mJumpForce;
	float mSpeed;
	int direction;
	Player* player;

};

#endif