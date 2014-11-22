#ifndef ENEMY_H
#define ENEMY_H

#include "Box2D\Box2D.h"
#include "BaseObject.h"

class Enemy : BaseObject{
public:
	Enemy(b2World*, int, int, SDL_Texture* enemyTex);
	b2Vec2 GetPosition();
	b2Fixture* GetFixture();
	void EnemyDeath(b2World*);
	void Reset(b2World*, SDL_Renderer*);
	void Draw(SDL_Renderer*, b2Vec2);
	void Update();//b2Vec2 playerCentre);
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

};

#endif