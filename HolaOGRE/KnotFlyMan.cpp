#include "KnotFlyMan.h"

using namespace Ogre;

KnotFlyMan::KnotFlyMan(Ogre::SceneNode*n) : ObjectMan(n)
{
	node = n;
	list = new OgreBites::InputListener();
	knotFly = n->getCreator()->createEntity("entKnotFly", "knot.mesh");
	knotFly->getSubEntity(0)->setMaterialName("KnotFly", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	/*knotFly->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0) ->
		createTextureUnitState("App/KnotFly/MtlPlat2.jpg");*/

	//EN RELACIÓN A SINBAD
	node->setPosition(1, 4, -2);
	node->scale(0.01, 0.01, 0.01);
	node->attachObject(knotFly);


	//MyApplicationContext::addInputListener(list);

	knotFly->setQueryFlags(-1);
}


KnotFlyMan::~KnotFlyMan()
{
	//MyApplicationContext::removeInputListener(list);
}

void KnotFlyMan::frameRendered(const Ogre::FrameEvent & evt) {
	//Rotación en el eje Y
	node->rotate(Vector3(0.0f, 1.0f, 0.0f), Radian(0.1f));
};