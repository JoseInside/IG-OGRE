#include "KnotFlyMan.h"


KnotFlyMan::KnotFlyMan(Ogre::SceneNode*n)
{
	node = n;
	list = new OgreBites::InputListener();
	knotFly = n->getCreator()->createEntity("entKnotFly", "knot.mesh");
	
	/*knotFly->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0) ->
		createTextureUnitState("App/KnotFly/MtlPlat2.jpg");*/

	node->setPosition(0, 5, 0); 
	node->scale(0.1, 0.1, 0.1);
	node->attachObject(knotFly);

	MyApplicationContext::addInputListener(list);

	knotFly->setQueryFlags(-1);
}


KnotFlyMan::~KnotFlyMan()
{
	MyApplicationContext::removeInputListener(list);
}
