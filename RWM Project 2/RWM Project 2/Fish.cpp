#include "Fish.h"


Fish::Fish(int x,int y, int w, int h,b2World* world,SDL_Texture* texture, int dir)
{
		dirVel = dir;
		myColIdent = new CollisionIdentifier();
		myColIdent->baseClass = this;
		myColIdent->className = "Fish";

		b2Vec2 position;
		position.x = x;
		position.y = y;

		size.x = w;
		size.y = h;

		m_texture = texture;

		body = BodyFactory::createBody(world,position,size,1/14.0f,1,false,true,false,myColIdent);

}


Fish::~Fish(void)
{
}


void Fish::Update(){
	body->SetTransform(b2Vec2(body->GetPosition().x + dirVel, body->GetPosition().y),0);
	if((body->GetPosition().x + (size.x/2)) >= 1280){
		dirVel = -1;
	}
	if(body->GetPosition().x - (size.x/2) <= 0){
		dirVel = 1;
	}
}

void Fish::Draw(SDL_Renderer* gRenderer){
	b2Vec2 position;
	position.x = body->GetPosition().x;
	position.y = body->GetPosition().y;
	SDL_Rect posImg = {position.x - (size.x/2), position.y - (size.y/2),size.x,size.y};

	SDL_RenderCopy(gRenderer,m_texture,NULL,&posImg);
}