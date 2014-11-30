#pragma once

#include <string>
using namespace std;
class BaseObject;
class CollisionIdentifier
{
public:
	string className;
	BaseObject* baseClass;
	CollisionIdentifier(void);
	~CollisionIdentifier(void);

	
};


#include "BaseObject.h"

