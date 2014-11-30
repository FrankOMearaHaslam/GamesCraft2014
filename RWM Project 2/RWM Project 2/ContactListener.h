#pragma once
#include "Box2D\Box2D.h"
#include <windows.system.h>
#include "CollisionIdentifier.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"
#include "Water.h"
#include "Fish.h"
using namespace std;
class ContactListener: public b2ContactListener
{
public:
	Game* bGame;
	typedef std::pair<b2Fixture*, b2Fixture*> fixturePair;
	std::set<fixturePair> m_fixturePairs;

	void WaterStep(Water* water);
	b2World* bWorld;
	static ContactListener* me;
	static ContactListener* createListener();
	void initialize();
	void setWorld(b2World* world);
	void setGame(Game* game);
	ContactListener(void);
	~ContactListener(void);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	void fishStep(Fish* water,b2Body*);

   
	SDL_sem* gDataLock;
	
	


private:
	void checkObject(CollisionIdentifier*);
	
	b2Body* platBody;
	Player* player;
	b2Body* conveyorBody;
	Enemy* enemy;
	Water* water;
	
};
