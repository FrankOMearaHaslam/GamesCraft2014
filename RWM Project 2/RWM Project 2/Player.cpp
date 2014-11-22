#include "Player.h"


Player::Player(b2World * world, SDL_Texture* tex){

	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className = "Player";
	size = b2Vec2(64,64);
	mBody = BodyFactory::createBody(world,b2Vec2(200,50),size,0.01,2,true,false,myColIdent);
	mBody->SetLinearDamping(0.01);
	m_texture = tex;
	myMass=new b2MassData();
	mBody->GetMassData(myMass);

	Left=false;
}


Player::~Player(void){
}

void Player::Update(float timeElapsed){
	if(KeyboardManager::instance()->IsKeyDown(KeyboardManager::LEFT)){
		mBody->ApplyLinearImpulse(b2Vec2(-50,0),mBody->GetPosition(),true);
	}
	if(KeyboardManager::instance()->IsKeyDown(KeyboardManager::RIGHT)){
		mBody->ApplyLinearImpulse(b2Vec2(50,0),mBody->GetPosition(),true);
	}
}

void Player::Draw(SDL_Renderer* gRenderer){
	SDL_Rect stretchRect;
	stretchRect.x =  mBody->GetPosition().x;//-(size.x/2.0f);//centre of the screen//mBody->GetWorldCenter().x;
	stretchRect.y =  mBody->GetPosition().y;//-(size.y/2.0f);//centre of the screen// mBody->GetWorldCenter().y;
	stretchRect.w = (size.x/1.0f);
	stretchRect.h = (size.y/1.0f);
	if(Left){
		//SDL_RenderCopy ( gRenderer, TextureManager::getManager()->playerLeftTexture, NULL, &stretchRect);
	}
	else{
		//SDL_RenderCopy ( gRenderer, TextureManager::getManager()->playerTexture, NULL, &stretchRect);
	}
	
	SDL_RenderCopy(gRenderer,m_texture,NULL,&stretchRect);

}

b2Body* Player::GetBody(){

	return mBody;
}


