#ifndef __SinbadMan_H__
#define __SinbadMan_H__
#include "ObjectMan.h"
class SinbadMan :
	public MyApplicationContext,public ObjectMan
{
public:
	SinbadMan(Ogre::SceneNode*n);
	virtual ~SinbadMan();

	bool mousePicking(const OgreBites::MouseButtonEvent& evt) { return true; }
	void frameRendered(const Ogre::FrameEvent & evt);
private:
	
	OgreBites::InputListener* list = new OgreBites::InputListener();
	Ogre::SceneNode*node;
	Ogre::Entity* ent;
	Ogre::Entity* ent2;
	Ogre::AnimationState* animState;	//MOVER PIERNAS
	Ogre::AnimationState* animState2;	//ANDAR
	Ogre::Animation* animation;
	
	void WalkingAnimation(Ogre::NodeAnimationTrack * track);
	
	float duracion = 4.0f;
	float tamDesplazamiento = 160.0f;
	Ogre::Real longitudPaso = duracion / 4.0;
	Ogre::Vector3 keyframePos;
	Ogre::Vector3 escalado;
};

#endif