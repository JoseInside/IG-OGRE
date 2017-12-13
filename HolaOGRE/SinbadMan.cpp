#include "SinbadMan.h"

using namespace Ogre;
SinbadMan::SinbadMan(Ogre::SceneNode*n)
{
	node = n;

	ent = n->getCreator()->createEntity("entSinbad", "Sinbad.mesh");

	// finally something to render
	//node->setPosition(0, 50, 0);
	node->scale(5, 5, 5);
	//node->showBoundingBox(true);
	//node->roll(Ogre::Degree(-45));
	node->attachObject(ent);
	MyApplicationContext::addInputListener(list);

	ent->setQueryFlags(-1);
	animState = ent->getAnimationState("RunBase");
	//animState = ent->getAnimationState("animKnot");
	animState->setLoop(true);
	animState->setEnabled(true);



	//PARA PRACTICAR
	//ent2 = n->getCreator()->createEntity("foot1", "Sinbad.mesh");
	//ent->attachObjectToBone("Foot.L", ent2);
	//ent3 = n->getCreator()->createEntity("foot2", "Sinbad.mesh");
	//ent->attachObjectToBone("Foot.R", ent3);
}


SinbadMan::~SinbadMan()
{
	MyApplicationContext::removeInputListener(list);
	
}

void SinbadMan::frameRendered(const Ogre::FrameEvent & evt) {
	animState->addTime(evt.timeSinceLastFrame);
}


void SinbadMan::WalkingAnimation(){



}