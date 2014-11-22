#include "Enemy.h"

Enemy::Enemy(b2World* world, int x, int y,SDL_Texture* enemyTex) : m_angle(0.0f){
	
	b2Vec2 pos = b2Vec2(x, y);
	size = b2Vec2(30, 30);
	mJumpForce = 2000;
	mSpeed = 0.2f;

	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className = "Enemy";

	dynamicBody = BodyFactory::createBody(world, pos, size, 1, 1, true, false, myColIdent);
	dynamicBody->SetLinearDamping(0.01);
	alive = true;

}
b2Body* Enemy::GetBody()
{
	return dynamicBody;
}
void Enemy::Update(b2Vec2 playerCentre)
{
	b2Vec2 pos = dynamicBody->GetPosition();
	if(pos.x >= playerCentre.x)
	{
		dynamicBody->SetLinearVelocity(b2Vec2(max(-3.0f,dynamicBody->GetLinearVelocity().x-0.1f),dynamicBody->GetLinearVelocity().y));
	}
	else
	{
		dynamicBody->SetLinearVelocity(b2Vec2(min(3.0f,dynamicBody->GetLinearVelocity().x+0.1f),dynamicBody->GetLinearVelocity().y));
	}


	if(playerCentre.y < pos.y - 50 && dynamicBody->GetContactList())
	{
		dynamicBody->ApplyLinearImpulse(b2Vec2(0, -mJumpForce), dynamicBody->GetPosition(), true);
	}
	
}


void Enemy::Draw(SDL_Renderer* gRenderer, b2Vec2 offset){

	SDL_Rect stretchRect;

	//Render to screen
	/*stretchRect.x = dynamicBody->GetWorldCenter().x-(100/2.0f);
	stretchRect.y = dynamicBody->GetWorldCenter().y-(100/2.0f);*/ 
	stretchRect.x = dynamicBody->GetWorldCenter().x+offset.x-(size.x/2.0f);
	stretchRect.y = dynamicBody->GetWorldCenter().y+offset.y-(size.y/2.0f);
	stretchRect.w = size.x; 
	stretchRect.h = size.y;

	//SDL_RenderCopy( gRenderer, , NULL, &stretchRect);


}


void Enemy::EnemyDeath(b2World* world)
{

	alive= false;
	dynamicBody->DestroyFixture(mFix);//all this removes and then re-initialises the Enemy
	world->DestroyBody(dynamicBody);
}

b2Vec2 Enemy::GetPosition() {
	return dynamicBody->GetPosition();
}

b2Fixture* Enemy::GetFixture() {
	return &dynamicBody->GetFixtureList()[0];
}

void Enemy::Reset(b2World* world, SDL_Renderer* gRenderer){
	if(alive){
		dynamicBody->DestroyFixture(mFix);//all this removes and then re-initialises the Enemy
		world->DestroyBody(dynamicBody);
	}    
	dynamicBody = world->CreateBody(&myBodyDef);
	mFix = dynamicBody->CreateFixture(&fixtureDef);
	alive = true;
}