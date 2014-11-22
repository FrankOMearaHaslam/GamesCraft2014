#pragma once
#include "Box2D\Box2D.h"
#include "CollisionIdentifier.h"
class BodyFactory
{
public:
	BodyFactory(void);
	~BodyFactory(void);
	static b2Body* createBody(b2World* world, float x, float y,float width,float height,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent);
	
	static b2Body* createBody(b2World* world, b2Vec2 pos,float width,float height,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent);
	
	static b2Body* createBody(b2World* world, b2Vec2 pos,b2Vec2 size,float density, float friction,
								bool dynamic, bool rotatable, CollisionIdentifier* ColIdent);

	static b2Body* createBody(b2World* world, b2Vec2 pos,b2Vec2 size,float density, float friction,
								bool dynamic, bool sensor, bool rotatable, CollisionIdentifier* ColIdent);

};

