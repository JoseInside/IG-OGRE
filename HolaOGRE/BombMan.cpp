#include "BombMan.h"


BombMan::BombMan(Ogre::SceneNode*n)
{
	node = n;
	list = new OgreBites::InputListener();
	bomb = n->getCreator()->createEntity("entBomb", "uv_sphere.mesh");

	node->setPosition(0, 0, 0); 
	node->scale(0.1, 0.1, 0.1);
	node->attachObject(bomb);


	MyApplicationContext::addInputListener(list);

	bomb->setQueryFlags(-1);

}


BombMan::~BombMan()
{
	MyApplicationContext::removeInputListener(list);
}
