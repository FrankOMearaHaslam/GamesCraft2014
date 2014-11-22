#include "Player.h"


Player::Player(b2World * world)
{
	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className = "Player";
	size = b2Vec2(64,64);
	mBody = BodyFactory::createBody(world,b2Vec2(0,0),size,1,2,true,false,myColIdent);
	mBody->SetLinearDamping(0.01);

	myMass=new b2MassData();
	mBody->GetMassData(myMass);

}


Player::~Player(void)
{
}

void Player::Update(float timeElapsed)
{
	
}

void Player::Draw(SDL_Renderer* gRenderer, b2Vec2 offset)
{
	SDL_Rect stretchRect;
	stretchRect.x =  mBody->GetPosition().x+offset.x-(size.x/2.0f);//centre of the screen//mBody->GetWorldCenter().x;
	stretchRect.y =  mBody->GetPosition().y+offset.y-(size.y/2.0f);//centre of the screen// mBody->GetWorldCenter().y;
	stretchRect.w = (size.x/1.0f);
	stretchRect.h = (size.y/1.0f);
	if(Left)
	{
		//SDL_RenderCopy ( gRenderer, TextureManager::getManager()->playerLeftTexture, NULL, &stretchRect);
	}
	else
	{
		//SDL_RenderCopy ( gRenderer, TextureManager::getManager()->playerTexture, NULL, &stretchRect);
	}

}

b2Body* Player::GetBody()
{
	return mBody;
}


