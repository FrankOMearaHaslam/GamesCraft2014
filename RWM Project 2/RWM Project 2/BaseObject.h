#pragma once
#include "CollisionIdentifier.h"
#include "BodyFactory.h"
#include <SDL_dev\SDL2-2.0.3\include\SDL.h>

class BaseObject
{
public:
	CollisionIdentifier* myColIdent;
	BaseObject(void);
	~BaseObject(void);
};

