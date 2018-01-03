#ifndef __BombMan_H__
#define __BombMan_H__
#include "ObjectMan.h"
#include "SinbadMan.h"

class BombMan :
	public MyApplicationContext, public ObjectMan
{
public:
	BombMan(Ogre::SceneNode*n, SinbadMan* sinbad);
	virtual ~BombMan();

	virtual bool mousePicking(const OgreBites::MouseButtonEvent& evt);
	virtual void frameRendered(const Ogre::FrameEvent & evt);


private:
	bool activated;	//Trigger de la bomba
	SinbadMan* _sinbad;
	Ogre::Entity* bomb;
	Ogre::ParticleSystem* smoke;
	Ogre::Vector3 keyframePos;
	Ogre::Vector3 escalado;
	float duracion = 4.0f;
	float tamDesplazamiento = 6.0f;
	Ogre::Real longitudPaso = duracion / 4.0;

	Ogre::AnimationState* BombAnimState;

	void smokeAnimation(Ogre::NodeAnimationTrack * track);
};

#endif