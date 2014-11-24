#include "FishingLine.h"


FishingLine::FishingLine(int x,int y,int width,int height,b2World* world,SDL_Renderer* render)
{
	m_position.x = x;
	m_position.y = y;
	m_position.w = width;
	m_position.h = height;

	myColIdent = new CollisionIdentifier();
	myColIdent->baseClass = this;
	myColIdent->className = "FishingLine";

	
	//b2Vec2 position1;
	position1.x = m_position.x;
	position1.y = m_position.y + m_position.h/2 + 25;
	position1.w = 5;
	position1.h = 50;

	//b2Vec2 position2;
	position2.x = m_position.x;
	position2.y = position1.y + position1.h/2 + 17.5;
	position2.w = 60;
	position2.h = 35;

	createBody(world);
			tHang = m_tHang.loadPNG("images/square.png", render);
			tLine = m_tHang.loadPNG("images/Square.png", render);
			tHook = m_tHang.loadPNG("images/seesawBase.png", render);

	
}

void FishingLine::updatePosition(int x,int y,int width,int height,b2World*)
{
	lineLength.x = 0;
	
	m_position.x = x;
	m_position.y = y;
	m_position.w = width;
	m_position.h = height;

	//b2Vec2 position1;
	position1.x = m_position.x;
	position1.y = m_position.y + m_position.h/2 + 25;
	position1.w = 5;
	position1.h = 50;

	//b2Vec2 position2;
	position2.x = m_position.x;
	position2.y = position1.y + position1.h/2 + 17.5;
	position2.w = 60;
	position2.h = 35;


	m_bodyHang->SetTransform(b2Vec2(m_position.x, m_position.y),0);
	m_bodyHook->SetTransform(b2Vec2(m_position.x, m_bodyHook->GetPosition().y),0);
	m_bodyHook->ApplyLinearImpulse(b2Vec2(0,100), m_bodyHook->GetWorldCenter(), true);
	//m_bodyHook->SetTransform(b2Vec2(position2.x, position2.y),0);

}

SDL_Rect FishingLine::getPosition()
{
	return m_position;
}

b2Body* FishingLine::getLineBody()
{
	return m_bodyHang;
}

float FishingLine::radian_to_degree(double radians)
{
	double Pi = 3.14159265;
    float degrees = (radians * 180) / Pi;
    return degrees;
}

void FishingLine::createBody(b2World* world)
{
	m_bodyHang = BodyFactory::createBody(world, b2Vec2(m_position.x, m_position.y), b2Vec2(m_position.w, m_position.h), 1.0f, 1, false, false, false, myColIdent);	

	//m_bodyLine = BodyFactory::createBody(world, b2Vec2(position1.x, position1.y), b2Vec2(position1.w, position1.h), 1.0f, 1, true, false, true, myColIdent);

	m_bodyHook = BodyFactory::createBody(world, b2Vec2(position2.x, position2.y - 30), b2Vec2(position2.w, position2.h), 1.0f, 1, true, true, true, myColIdent);


	CreateDistanceJoint(world,m_bodyHang, m_bodyHook, b2Vec2(0,0), b2Vec2(0,0), true, 20, 0.5f, 20.0f);




}
void FishingLine::Render(SDL_Renderer* render)
{
	

	//-----------------

	m_position.x = m_bodyHang->GetPosition().x;
	m_position.y = m_bodyHang->GetPosition().y;
	SDL_Rect posImg = {50, 50, m_position.w,m_position.h};



	m_tHang.render(m_position.x - (m_position.w/2), m_position.y - (m_position.h/2), &posImg, 0, NULL, SDL_FLIP_NONE, render, tHang);

	//-------------------

	lineLength.y = m_bodyHook->GetPosition().y - m_bodyHang->GetPosition().y;

	SDL_Rect posImg1 = {50, 50, m_position.w ,lineLength.y };



    m_tLine.render(m_position.x - (m_position.w/2), m_position.y -  (m_position.h/2), &posImg1, 0, NULL, SDL_FLIP_NONE, render, tLine);

	//------------------

	position2.x = m_bodyHook->GetPosition().x;
	position2.y = m_bodyHook->GetPosition().y;

	float angle = radian_to_degree(m_bodyHook->GetAngle());

	SDL_Rect posImg2 = {0, 0, 60 ,35};

	m_tHook.render(position2.x - position2.w/2, position2.y - position2.h/2, &posImg2, angle, NULL, SDL_FLIP_NONE, render, tHook);


	
	
}

void FishingLine::CreateDistanceJoint(b2World *world, b2Body* body1,  b2Body* body2, b2Vec2 anchor1, b2Vec2 anchor2, bool collideConnected,
						               float length, float dampingRatio, float frequencyHz)
{
	b2DistanceJointDef* distanceJointDef = new b2DistanceJointDef();
    distanceJointDef->bodyA = body1;
	distanceJointDef->bodyB = body2;
	distanceJointDef->localAnchorA = anchor1;
	distanceJointDef->localAnchorB = anchor2;
	distanceJointDef->collideConnected = collideConnected;
	//dampingRatio typically from 0 ~ 1
	distanceJointDef->dampingRatio = dampingRatio;
	//frequencyHz typically less than 30
	distanceJointDef->frequencyHz = frequencyHz;

	distanceJointDef->length = length;

    //create the joint     
	m_distanceJoint = (b2DistanceJoint*)world->CreateJoint( distanceJointDef );
}

void FishingLine::Update(float timeElapsed, SDL_Renderer* render,b2World* world)
{

	
	if(KeyboardManager::instance()->IsKeyDown(KeyboardManager::DOWN)){

		m_distanceJoint->SetLength(500);
		m_bodyHook->ApplyLinearImpulse(b2Vec2(0,-100), m_bodyHook->GetWorldCenter(), true);
	}
	if(KeyboardManager::instance()->IsKeyDown(KeyboardManager::UP)){

		m_distanceJoint->SetLength(20);
		m_bodyHook->ApplyLinearImpulse(b2Vec2(0,100), m_bodyHook->GetWorldCenter(), true);
	}
    
	
}

