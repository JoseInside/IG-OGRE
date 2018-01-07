#ifndef __SinbadMan_H__
#define __SinbadMan_H__
#include "ObjectMan.h"
class SinbadMan : public ObjectMan
{
public:
	SinbadMan(Ogre::SceneNode*n);
	virtual ~SinbadMan();

	bool mousePicking(const OgreBites::MouseButtonEvent& evt);
	
	void frameRendered(const Ogre::FrameEvent & evt);

	void WalkingAnimation();
	void WalkingToBombAnimation();

	void Die();
	void WaterDragAnimation();


protected:
	
	//OgreBites::InputListener* list =  new OgreBites::InputListener();
	//Ogre::SceneNode*node;
	Ogre::Entity* sinbad;
	Ogre::Entity* espadaL;
	Ogre::Entity* espadaR;
	Ogre::AnimationState* animStateWalking;		//ANDAR EN CUADRADO
	Ogre::AnimationState* animStateBase;		//MOVER PIERNAS
	Ogre::AnimationState* animStateTop;			//MOVER BRAZOS
	Ogre::AnimationState* animStateGoToBomb;	//ANDAR HACIA LA BOMBA
	Ogre::Animation* animationWalking;
	Ogre::Animation * animationWalkingBomb;

	Ogre::AnimationState* animStateWater;
	Ogre::Animation* animationStreamWater;
	Ogre::NodeAnimationTrack* track3;
	
	Ogre::NodeAnimationTrack * track;
	Ogre::NodeAnimationTrack * track2;
	float duracion = 4.0f;
	float tamDesplazamiento = 160.0f;
	Ogre::Real longitudPaso = duracion / 4.0;
	Ogre::Vector3 keyframePos;
	Ogre::Vector3 escalado;

	bool walk = true;
	bool goToBomb = false;
	bool dead = false;

};

#endif