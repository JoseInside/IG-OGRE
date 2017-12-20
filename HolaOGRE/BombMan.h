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
};

#endif