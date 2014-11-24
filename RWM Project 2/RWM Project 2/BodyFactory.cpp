#include "BodyFactory.h"


BodyFactory::BodyFactory(void)
{
}


BodyFactory::~BodyFactory(void)
{
}


b2Body* BodyFactory::createBody(b2World* world, float x, float y,float width,float height,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent)
{
	b2BodyDef BodyDef;
	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}
	BodyDef.position.Set(x,  y);
	if(!rotatable)
	{
		BodyDef.fixedRotation = true;
	}
	BodyDef.userData = ColIdent;
	b2Body* body = world->CreateBody(&BodyDef);
	b2PolygonShape Box;
	//sets box with position centered and given width and height in each direction(hence /2)
	Box.SetAsBox(width/2.0f, height/2.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &Box;
	if(dynamic)
	{
		fixtureDef.density = density;
		fixtureDef.friction = friction;
	}
	body->CreateFixture(&fixtureDef);
	return body;
}


b2Body* BodyFactory::createBody(b2World* world, b2Vec2 pos,float width,float height,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent)
{
	b2BodyDef BodyDef;
	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}
	BodyDef.position.Set(pos.x,  pos.y);
	if(!rotatable)
	{
		BodyDef.fixedRotation = true;
	}
	BodyDef.userData = ColIdent;
	b2Body* body = world->CreateBody(&BodyDef);
	b2PolygonShape Box;
	//sets box with position centered and given width and height in each direction(hence /2)
	Box.SetAsBox(width/2.0f, height/2.0f);
	b2FixtureDef fixtureDef;
	
	fixtureDef.shape = &Box;
	if(dynamic)
	{
		fixtureDef.density = density;
		fixtureDef.friction = friction;
	}
	body->CreateFixture(&fixtureDef);
	return body;
}


b2Body* BodyFactory::createBody(b2World* world, b2Vec2 pos,b2Vec2 size,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent)
{
	b2BodyDef BodyDef;
	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}
	BodyDef.position.Set(pos.x,  pos.y);
	if(!rotatable)
	{
		BodyDef.fixedRotation = true;
	}
	BodyDef.userData = ColIdent;
	b2Body* body = world->CreateBody(&BodyDef);
	b2PolygonShape Box;
	//sets box with position centered and given width and height in each direction(hence /2)
	Box.SetAsBox(size.x/2.0f, size.y/2.0f);
	b2FixtureDef fixtureDef;

	fixtureDef.shape = &Box;
	if(dynamic)
	{
		fixtureDef.density = density;
		fixtureDef.friction = friction;
	}
	body->CreateFixture(&fixtureDef);


	return body;
}

b2Body* BodyFactory::createBody(b2World* world, b2Vec2 pos,b2Vec2 size,float density, float friction,
								bool dynamic,bool sensor, bool rotatable, CollisionIdentifier* ColIdent)
{
	b2BodyDef BodyDef;


	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}
	
	BodyDef.position.Set(pos.x,  pos.y);
	if(!rotatable)
	{
		BodyDef.fixedRotation = true;
	}
	BodyDef.userData = ColIdent;
	b2Body* body = world->CreateBody(&BodyDef);
	b2PolygonShape Box;
	//sets box with
	//position centered and given width and height in each direction(hence /2)
	Box.SetAsBox(size.x/2.0f, size.y/2.0f);
	b2FixtureDef fixtureDef;
	if(sensor)
	{

		fixtureDef.isSensor = true;
		fixtureDef.density = density;
	}
	
	fixtureDef.shape = &Box;
	if(dynamic)
	{
		fixtureDef.density = density;
		fixtureDef.friction = friction;
	}
	body->CreateFixture(&fixtureDef);
	return body;
}

b2Body* BodyFactory::createEnemy(b2World* world, b2Vec2 pos,b2Vec2 size,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent)
{
	b2BodyDef BodyDef;


	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}
	
	BodyDef.position.Set(pos.x,  pos.y);
	if(!rotatable)
	{
		BodyDef.fixedRotation = true;
	}
	BodyDef.userData = ColIdent;
	b2Body* body = world->CreateBody(&BodyDef);
	b2PolygonShape Box;
	//sets box with
	//position centered and given width and height in each direction(hence /2)
	Box.SetAsBox(size.x/2.0f, size.y/2.0f);
	b2FixtureDef fixtureDef;
	
	fixtureDef.shape = &Box;
	if(dynamic)
	{
		fixtureDef.density = density;
		fixtureDef.friction = friction;
	}
	body->CreateFixture(&fixtureDef);

	b2Filter f;
	f.groupIndex =-1;
	body->GetFixtureList()[0].SetFilterData(f);

	return body;
}
b2Body* BodyFactory::createFish(b2World* world, b2Vec2 pos,b2Vec2 size,float density, float friction,
								bool dynamic,bool sensor, bool rotatable, CollisionIdentifier* ColIdent)
{
	b2BodyDef BodyDef;


	if(dynamic)
	{
		BodyDef.type = b2_dynamicBody;
	}
	
	BodyDef.position.Set(pos.x,  pos.y);
	if(!rotatable)
	{
		BodyDef.fixedRotation = true;
	}
	BodyDef.userData = ColIdent;
	b2Body* body = world->CreateBody(&BodyDef);
	b2PolygonShape Box;
	//sets box with
	//position centered and given width and height in each direction(hence /2)
	Box.SetAsBox(size.x/2.0f, size.y/2.0f);
	b2FixtureDef fixtureDef;
	if(sensor)
	{

		fixtureDef.isSensor = true;
		fixtureDef.density = density;
	}
	
	fixtureDef.shape = &Box;
	if(dynamic)
	{
		fixtureDef.density = density;
		fixtureDef.friction = friction;
	}
	body->CreateFixture(&fixtureDef);


	return body;
}