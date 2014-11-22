#pragma once
#include "Box2D\Box2D.h"
#include "CollisionIdentifier.h"
//#include "Player.h"
//#include "Platform.h"
//#include "Grapple.h"
#include "ObjectManager.h"
#include "Game.h"
//#include "ConveyorBelt.h"
//#include "Seesaw.h"
//#include "Enemy.h"
using namespace std;
class ContactListener: public b2ContactListener
{
public:
	Game* bGame;
	typedef std::pair<b2Fixture*, b2Fixture*> fixturePair;
	std::set<fixturePair> m_fixturePairs;

	void WaterStep();
	b2World* bWorld;
	static ContactListener* me;
	static ContactListener* createListener();
	void setWorld(b2World* world);
	void setGame(Game* game);
	ContactListener(void);
	~ContactListener(void);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

private:
	void checkObject(CollisionIdentifier*);
	
	b2Body* platBody;
	Player* player;
	b2Body* conveyorBody;
	Enemy* enemy;
	Water* water;
	
};
