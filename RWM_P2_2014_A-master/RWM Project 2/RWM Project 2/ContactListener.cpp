#include "ContactListener.h"


ContactListener* ContactListener::me;

ContactListener* ContactListener::createListener()
{
	if(me == NULL)
	{
		me = new ContactListener();
	}
	return me;
}

ContactListener::ContactListener(void)
{
}


ContactListener::~ContactListener(void)
{
}


void ContactListener::checkObject(CollisionIdentifier* ident)
{
	
	if(ident->className=="Player")
	{
		player=(Player*)ident->baseClass;
	}

	else if(ident->className=="Enemy")
	{
		enemy=(Enemy*)ident->baseClass;
	}
	else if(ident->className=="Water")
	{
		water=(Water*)ident->baseClass;
	}
	
}


void ContactListener::BeginContact(b2Contact* contact)
{
	bool looking = true;
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
    b2Body* body1 = fixtureA->GetBody();
    b2Body* body2 = fixtureB->GetBody();
	CollisionIdentifier* body1Ident = ((CollisionIdentifier*)body1->GetUserData());
	CollisionIdentifier* body2Ident = ((CollisionIdentifier*)body2->GetUserData());
	grapple = NULL;
	bullet = NULL;
	platform = NULL;
	platBody = NULL;
	player = NULL;
	conveyor = NULL;
	seesaw = NULL;
	enemy = NULL;
	water = NULL;
	conveyorBody=NULL;
	elevator=NULL;
	collectible = NULL;
	pulley = NULL;
	portal=NULL;

	if ( fixtureA->IsSensor() && fixtureB->GetBody()->GetType() == b2_dynamicBody )
        m_fixturePairs.insert( make_pair(fixtureA, fixtureB) );
    else if ( fixtureB->IsSensor() && fixtureA->GetBody()->GetType() == b2_dynamicBody )
        m_fixturePairs.insert( make_pair(fixtureB, fixtureA) );

	checkObject(body1Ident);

	checkObject(body2Ident);
	

	if(player!=NULL)
	{
		
		if(enemy!=NULL)
		{
			b2Vec2 dir = enemy->GetBody()->GetPosition()-player->GetBody()->GetPosition();
			dir.x*=5000;
			dir.y*=5000;
			enemy->GetBody()->ApplyForceToCenter(dir,true);
			player->ChangeBlood(-10);
		}
		else if(water!=NULL)
		{
			player->jumpable=true;
		}
	
	}
}
void ContactListener::EndContact(b2Contact* contact)
{
	 b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();
  
    if ( fixtureA->IsSensor() && fixtureB->GetBody()->GetType() == b2_dynamicBody )
        m_fixturePairs.erase( make_pair(fixtureA, fixtureB) );
    else if ( fixtureB->IsSensor() && fixtureA->GetBody()->GetType() == b2_dynamicBody )
        m_fixturePairs.erase( make_pair(fixtureB, fixtureA) );
}

void ContactListener::WaterStep()
{
	//inside Step(), loop through all currently overlapping fixture pairs
  set<fixturePair>::iterator it = m_fixturePairs.begin();
  set<fixturePair>::iterator end = m_fixturePairs.end();
  while (it != end) 
  {
      //fixtureA is the fluid
      b2Fixture* fixtureA = it->first;
      b2Fixture* fixtureB = it->second;
      
      float density = fixtureA->GetDensity();
  
      vector<b2Vec2> intersectionPoints;
	  vector<b2Vec2> intersectionPointsMushroom;
	  if(density < 50)
	  {
		  for(int i = 0; i < ObjectManager::getManager()->water.size(); i ++)
		  {
			  if( ObjectManager::getManager()->water.at(i)->getBody()->GetFixtureList()==fixtureA||ObjectManager::getManager()->water.at(i)->getBody()->GetFixtureList()==fixtureB)
			  if ( ObjectManager::getManager()->water.at(i)->findIntersectionOfFixtures(fixtureA, fixtureB, intersectionPoints) ) 
			  {
      
				  //find centroid
				  float area = 0;
				  b2Vec2 centroid = ObjectManager::getManager()->water.at(i)->ComputeCentroid( intersectionPoints, area);
          
				  //apply buoyancy stuff here...
				   b2Vec2 gravity( 0, -10 );
  
				  //apply buoyancy force (fixtureA is the fluid)
				  float displacedMass = fixtureA->GetDensity() * area;
				  b2Vec2 buoyancyForce = displacedMass * gravity;
				  fixtureB->GetBody()->ApplyForce( buoyancyForce, centroid,false/*unsure?*/);

			
					  //apply drag separately for each polygon edge
					  for (int i = 0; i < intersectionPoints.size(); i++) {
						  //the end points and mid-point of this edge 
						  b2Vec2 v0 = intersectionPoints[i];
						  b2Vec2 v1 = intersectionPoints[(i+1)%intersectionPoints.size()];
						  b2Vec2 midPoint = 0.5f * (v0+v1);
      
						  //find relative velocity between object and fluid at edge midpoint
						  b2Vec2 velDir = fixtureB->GetBody()->GetLinearVelocityFromWorldPoint( midPoint ) -
										  fixtureA->GetBody()->GetLinearVelocityFromWorldPoint( midPoint );
						  float vel = velDir.Normalize();
  
						  b2Vec2 edge = v1 - v0;
						  float edgeLength = edge.Normalize();
						  b2Vec2 normal = b2Cross(-1,edge); //gets perpendicular vector
      
						  float dragDot = b2Dot(normal, velDir);
						  if ( dragDot < 0 )
							  continue; //normal points backwards - this is not a leading edge
  
						  float dragMag = dragDot * edgeLength * density * vel * vel;
						  b2Vec2 dragForce = dragMag * -velDir;
						  fixtureB->GetBody()->ApplyForce( dragForce, midPoint,false);
					  }  
			  }
		}
		 
	  }
	 
      ++it;
  }

}


void ContactListener::setWorld(b2World* world)
{
	bWorld=world;
}

void ContactListener::setGame(Game* game)
{
	bGame=game;
}