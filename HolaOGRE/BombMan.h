#ifndef __BombMan_H__
#define __BombMan_H__
#include "ObjectMan.h"

class BombMan :
	public MyApplicationContext, public ObjectMan
{
public:
	BombMan(Ogre::SceneNode*n);
	virtual ~BombMan();

	bool mousePicking(const OgreBites::MouseButtonEvent& evt) { return true; }
	void frameRendered(const Ogre::FrameEvent & evt) {}


private:

	Ogre::Entity* bomb;
	Ogre::ParticleSystem* smoke;
	Ogre::Vector3 keyframePos;
	Ogre::Vector3 escalado;
	float duracion = 4.0f;
	float tamDesplazamiento = 160.0f;
	Ogre::Real longitudPaso = duracion / 4.0;

	void smokeAnimation(Ogre::NodeAnimationTrack * track);
};

#endif