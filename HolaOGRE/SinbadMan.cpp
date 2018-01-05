#include "SinbadMan.h"

using namespace Ogre;
SinbadMan::SinbadMan(Ogre::SceneNode*n) : ObjectMan(n)
{
	node = n;
	list = new OgreBites::InputListener();
	sinbad = n->getCreator()->createEntity("entSinbad", "Sinbad.mesh");

	// finally something to render
	node->setPosition(0, 25, 50); // es mejor mover a sinbad antes que mover el plano, ya que el reflejo se jode
	node->scale(5, 5, 5);
	node->attachObject(sinbad);
	
	//ESPADA MANO IZQUIERDA
	espadaL = node->getCreator()->createEntity("swordL", "Sword.mesh");
	sinbad->attachObjectToBone("Sheath.L", espadaL);

	//ESPADA MANO DERECHA
	espadaR = node->getCreator()->createEntity("swordR", "Sword.mesh");
	sinbad->attachObjectToBone("Handle.R", espadaR);
	sinbad->setQueryFlags(-1);

	animStateBase = sinbad->getAnimationState("RunBase");
	animStateBase->setLoop(true);
	animStateBase->setEnabled(true);

	animationWalking = node->getCreator()->createAnimation("animSinbadWalking", duracion);
	track = animationWalking->createNodeTrack(0);
	track->setAssociatedNode(node);

	animationWalkingBomb = node->getCreator()->createAnimation("animGoToBomb", duracion);//Duracion total de la animación
	track2 = animationWalkingBomb->createNodeTrack(0);//Camino 0
	track2->setAssociatedNode(node);

	animStateWalking = node->getCreator()->createAnimationState("animSinbadWalking");
	animStateWalking->setLoop(true);
	animStateWalking->setEnabled(true);

	animStateGoToBomb = node->getCreator()->createAnimationState("animGoToBomb");
	animStateGoToBomb->setEnabled(false);
	animStateGoToBomb->setLoop(false);
	
	
	
	WalkingAnimation();
}


SinbadMan::~SinbadMan()
{

}

void SinbadMan::frameRendered(const Ogre::FrameEvent & evt) {
	animStateBase->addTime(evt.timeSinceLastFrame);
	animStateWalking->addTime(evt.timeSinceLastFrame);
}


//EN CUADRADO
void SinbadMan::WalkingAnimation(){

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

//HACIA LA BOMBA
void SinbadMan::WalkingToBombAnimation(){

	animStateWalking->setEnabled(false);	
	animStateGoToBomb->setEnabled(true);

	sinbad->detachObjectFromBone(espadaL);
	sinbad->attachObjectToBone("Handle.L", espadaL);

	TransformKeyFrame * kf;
	SceneNode * bomba = node->getCreator()->getEntity("entBomb")->getParentSceneNode();	//CARGAR NODO BOMBA
	keyframePos = node->getPosition();	//PUNTO INICIO
	escalado = { 6, 6, 6 };
	Vector3* rot = new Vector3(bomba->getPosition().x - node->getPosition().x, 0, bomba->getPosition().z - node->getPosition().z);
	rot->normalise();

	kf = track2->createNodeKeyFrame(longitudPaso * 0);
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(rot);

	kf = track2->createNodeKeyFrame(longitudPaso * 1);
	keyframePos += (bomba->getPosition().x, 20, bomba->getPosition().z) * tamDesplazamiento;	//LUGAR DE LA BOMBA
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(rot);

}

//MUERTO UNA VEZ TOCADA LA BOMBA
void SinbadMan::Die(){

	animStateBase->setEnabled(false);
	animStateGoToBomb->setEnabled(false);

	node->rotate(Vector3(1.0f, 0.0f, 0.0f), Radian(3.14 / 2));
	node->rotate(Vector3(0.0f, 1.0f, 0.0f), Radian(3.14));
	node->translate(Vector3(0.0f, -20.0f, 0.0f));
}
bool SinbadMan::mousePicking(const OgreBites::MouseButtonEvent& evt){

	walk = !walk;
	animStateWalking->setEnabled(walk);
	animStateBase->setEnabled(walk);
	return true;
}