#include "SinbadMan.h"

using namespace Ogre;
SinbadMan::SinbadMan(Ogre::SceneNode*n)
{
	node = n;

	ent = n->getCreator()->createEntity("entSinbad", "Sinbad.mesh");

	// finally something to render
	node->setPosition(0, 25, 50); // es mejor mover a sinbad antes que mover el plano, ya que el reflejo se jode
	node->scale(5, 5, 5);
	//node->showBoundingBox(true);
	//node->roll(Ogre::Degree(-45));
	node->attachObject(ent);
	MyApplicationContext::addInputListener(list);
	
	ent2 = n->getCreator()->createEntity("sword", "Sword.mesh");
	ent->attachObjectToBone("Handle.L", ent2);
	ent->setQueryFlags(-1);
	
	animState = ent->getAnimationState("RunBase");
	animState->setLoop(true);
	animState->setEnabled(true);

	animation = n->getCreator()->createAnimation("animKnot", duracion);
	NodeAnimationTrack * track = animation->createNodeTrack(0);
	track->setAssociatedNode(node);

	WalkingAnimation(track);

	animState2 = n->getCreator()->createAnimationState("animKnot");
	animState2->setLoop(true);
	animState2->setEnabled(true);
}


SinbadMan::~SinbadMan()
{
	MyApplicationContext::removeInputListener(list);
	
}

void SinbadMan::frameRendered(const Ogre::FrameEvent & evt) {
	animState->addTime(evt.timeSinceLastFrame);
	animState2->addTime(evt.timeSinceLastFrame);
}


void SinbadMan::WalkingAnimation(NodeAnimationTrack* track){

	TransformKeyFrame * kf;
	keyframePos = { -90, 30, 80 };	//PUNTO INICIO
	escalado = { 6, 6, 6 };

	kf = track->createNodeKeyFrame(longitudPaso * 0); 
	keyframePos += Ogre::Vector3::UNIT_X* tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(-1, 0, 0)));

	kf = track->createNodeKeyFrame(longitudPaso * 1); 
	keyframePos -= Ogre::Vector3::UNIT_X * tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(-1, 0, 0)));


	kf = track->createNodeKeyFrame(longitudPaso * 1);
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, -1)));

	kf = track->createNodeKeyFrame(longitudPaso * 2);
	keyframePos -= Ogre::Vector3::UNIT_Z * tamDesplazamiento;
	kf->setTranslate(keyframePos); 
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, -1)));

	kf = track->createNodeKeyFrame(longitudPaso * 2);
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(1, 0, 0)));

	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::UNIT_X * tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(1, 0, 0)));


	kf = track->createNodeKeyFrame(longitudPaso * 3);
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);

	kf = track->createNodeKeyFrame(longitudPaso * 4);
	keyframePos += Ogre::Vector3::UNIT_Z * tamDesplazamiento;
	kf->setTranslate(keyframePos); 
	kf->setScale(escalado);

}