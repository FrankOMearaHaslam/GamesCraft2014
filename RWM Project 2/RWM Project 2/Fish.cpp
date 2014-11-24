#include "Fish.h"


Fish::Fish(int x,int y, int w, int h,b2World* world,SDL_Texture* texture, int dir, int ident)
{
		dirVel = dir;
		myColIdent = new CollisionIdentifier();
		myColIdent->baseClass = this;
		myColIdent->className = "Fish";

		b2Vec2 position;
		position.x = x;
		position.y = y;
		id = ident;
		size.x = w;
		size.y = h;

		m_texture = texture;
		caught = false;
		body = BodyFactory::createFish(world,position,size,1/14.0f,1,false,true,false,myColIdent);

}


Fish::~Fish(void)
{
}


void Fish::Update(){
	body->SetTransform(b2Vec2(body->GetPosition().x + dirVel, body->GetPosition().y),0);
	if((body->GetPosition().x + (size.x/2)) >= 1876){
		dirVel = -1;
	}
	if(body->GetPosition().x - (size.x/2) <= 0){
		dirVel = 1;
	}
}
void Fish::catchFish()
{
	caught = true;
}
void Fish::Draw(SDL_Renderer* gRenderer){
	if(caught == false)
	{
		b2Vec2 position;
		position.x = body->GetPosition().x;
		position.y = body->GetPosition().y;
		SDL_Rect posImg = {position.x - (size.x/2), position.y - (size.y/2),size.x,size.y};

		if(dirVel > 0)
		{
			SDL_RenderCopy(gRenderer,m_texture,NULL,&posImg);
		}
		else{
			SDL_RenderCopyEx(gRenderer,m_texture,NULL,&posImg,0,NULL,SDL_FLIP_HORIZONTAL);
		}
	}
	else
	{
		SDL_Rect posImg = {id * size.x, 10, size.x, size.y};
		SDL_RenderCopy(gRenderer, m_texture, NULL, &posImg);
	}
}

bool Fish::inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p) {
    return (cp2.x-cp1.x)*(p.y-cp1.y) > (cp2.y-cp1.y)*(p.x-cp1.x);
}
  
b2Vec2 Fish::intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e) {
    b2Vec2 dc( cp1.x - cp2.x, cp1.y - cp2.y );
    b2Vec2 dp( s.x - e.x, s.y - e.y );
    float n1 = cp1.x * cp2.y - cp1.y * cp2.x;
    float n2 = s.x * e.y - s.y * e.x;
    float n3 = 1.0 / (dc.x * dp.y - dc.y * dp.x);
    return b2Vec2( (n1*dp.x - n2*dc.x) * n3, (n1*dp.y - n2*dc.y) * n3);
}
  

bool Fish::findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, vector<b2Vec2>& outputVertices)
{
    //currently this only handles polygon vs polygon
    if ( fA->GetShape()->GetType() != b2Shape::e_polygon ||
        fB->GetShape()->GetType() != b2Shape::e_polygon )
        return false;
  
    b2PolygonShape* polyA = (b2PolygonShape*)fA->GetShape();
    b2PolygonShape* polyB = (b2PolygonShape*)fB->GetShape();
  
    //fill subject polygon from fixtureA polygon
    for (int i = 0; i < polyA->GetVertexCount(); i++)
        outputVertices.push_back( fA->GetBody()->GetWorldPoint( polyA->GetVertex(i) ) );
  
    //fill clip polygon from fixtureB polygon
    vector<b2Vec2> clipPolygon;
    for (int i = 0; i < polyB->GetVertexCount(); i++)
        clipPolygon.push_back( fB->GetBody()->GetWorldPoint( polyB->GetVertex(i) ) );
  
    b2Vec2 cp1 = clipPolygon[clipPolygon.size()-1];
    for (int j = 0; j < clipPolygon.size(); j++) {
        b2Vec2 cp2 = clipPolygon[j];
        if ( outputVertices.empty() )
            return false;
        vector<b2Vec2> inputList = outputVertices;
        outputVertices.clear();
        b2Vec2 s = inputList[inputList.size() - 1]; //last on the input list
        for (int i = 0; i < inputList.size(); i++) {
            b2Vec2 e = inputList[i];
            if (inside(cp1, cp2, e)) {
                if (!inside(cp1, cp2, s)) {
                    outputVertices.push_back( intersection(cp1, cp2, s, e) );
                }
                outputVertices.push_back(e);
            }
            else if (inside(cp1, cp2, s)) {
                outputVertices.push_back( intersection(cp1, cp2, s, e) );
            }
            s = e;
        }
        cp1 = cp2;
    }
  
    return !outputVertices.empty();
}