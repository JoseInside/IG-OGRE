#include "BombMan.h"

using namespace Ogre;

BombMan::BombMan(Ogre::SceneNode*n, SinbadMan* sinbad)
{

	_sinbad = sinbad;
	node = n;
	list = new OgreBites::InputListener();
	bomb = n->getCreator()->createEntity("entBomb", "uv_sphere.mesh");
	bomb->getSubEntity(0)->setMaterialName("KnotFly", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

	node->setPosition(0, 5, 0); 
	node->scale(0.03, 0.03, 0.03);
	node->attachObject(bomb);

	activated = false;
	MyApplicationContext::addInputListener(list);

	bomb->setQueryFlags(1);	//SELECCIONABLE

	smoke = node->getCreator()->createParticleSystem("smokeSys", "Smoke");
	node->attachObject(smoke);
	smoke->setEmitting(false);

	Animation * animation = node->getCreator()->createAnimation("animBomb", duracion);//Duracion total de la animación
	NodeAnimationTrack * track = animation->createNodeTrack(0);//Camino 0
	track->setAssociatedNode(node);

	BombAnimState = n->getCreator()->createAnimationState("animBomb");
	BombAnimState->setLoop(true);
	BombAnimState->setEnabled(true);

	smokeAnimation(track);

}


BombMan::~BombMan()
{
	MyApplicationContext::removeInputListener(list);
}

bool BombMan::mousePicking(const OgreBites::MouseButtonEvent& evt){
	if (!activated)
	{
		smoke->setEmitting(true);
		_sinbad->WalkingToBombAnimation();
		
		activated = true;
	}
		return true;

	
}

void BombMan::frameRendered(const Ogre::FrameEvent & evt){
	BombAnimState->addTime(evt.timeSinceLastFrame);
}

//HAY QUE ADAPTAR LA DE SINBAD A LA DE KNOT
void BombMan::smokeAnimation(Ogre::NodeAnimationTrack * track){
	
	TransformKeyFrame * kf;
	keyframePos = { 0, 7, 0 };	//PUNTO INICIO
	escalado = { 0.03f, 0.03f, 0.03f };

	kf = track->createNodeKeyFrame(longitudPaso * 0);
	keyframePos += Ogre::Vector3::UNIT_Y* tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	
	kf = track->createNodeKeyFrame(longitudPaso * 1);
	keyframePos -= Ogre::Vector3::UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);

	kf = track->createNodeKeyFrame(longitudPaso * 2);
	keyframePos -= Ogre::Vector3::UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);


	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::UNIT_Y * tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);

}
