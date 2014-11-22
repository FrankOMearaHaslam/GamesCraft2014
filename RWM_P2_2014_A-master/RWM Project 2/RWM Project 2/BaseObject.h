#pragma once
#include "CollisionIdentifier.h"
#include "BodyFactory.h"

class BaseObject
{
public:
	CollisionIdentifier* myColIdent;
	BaseObject(void);
	~BaseObject(void);
};

