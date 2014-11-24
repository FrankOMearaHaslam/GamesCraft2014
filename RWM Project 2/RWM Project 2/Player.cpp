#include "Player.h"


Player::Player(b2World * world, SDL_Texture* tex){

	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className = "Player";
	size = b2Vec2(300,150);
	mBody = BodyFactory::createBody(world,b2Vec2(200,250),size,0.2,2,true,true,myColIdent);
	mBody->SetLinearDamping(0.01);
	m_texture = tex;
	myMass=new b2MassData();
	mBody->GetMassData(myMass);
	Left=false;
}


Player::~Player(void)
{
}

void Player::Update(float timeElapsed){
	if(KeyboardManager::instance()->IsKeyDown(KeyboardManager::LEFT)){
		mBody->ApplyLinearImpulse(b2Vec2(-400,0),mBody->GetPosition(),true);
		mBody->ApplyLinearImpulse(b2Vec2(0,30),mBody->GetPosition(),true);
	}
	if(KeyboardManager::instance()->IsKeyDown(KeyboardManager::RIGHT)){
		mBody->ApplyLinearImpulse(b2Vec2(400,0),mBody->GetPosition(),true);
		mBody->ApplyLinearImpulse(b2Vec2(0,30),mBody->GetPosition(),true);
	}
}

void Player::Draw(SDL_Renderer* gRenderer){
	SDL_Rect stretchRect;
	stretchRect.x =  mBody->GetPosition().x-(size.x/2.0f);//centre of the screen//mBody->GetWorldCenter().x;
	stretchRect.y =  mBody->GetPosition().y-(size.y/2.0f);//centre of the screen// mBody->GetWorldCenter().y;
	stretchRect.w = (size.x/1.0f);
	stretchRect.h = (size.y/1.0f);
	if(Left){
		//SDL_RenderCopy ( gRenderer, TextureManager::getManager()->playerLeftTexture, NULL, &stretchRect);
	}
	else{
		//SDL_RenderCopy ( gRenderer, TextureManager::getManager()->playerTexture, NULL, &stretchRect);
	}

	double pi = 3.14159265358979323;
	float angleInDegrees = mBody->GetAngle()*(180/pi);
	SDL_RenderCopyEx(gRenderer,m_texture,NULL,&stretchRect,angleInDegrees, NULL, SDL_FLIP_NONE);

}

b2Body* Player::GetBody(){

	return mBody;
}



