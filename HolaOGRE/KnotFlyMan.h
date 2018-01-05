#ifndef __KnotFlyMan_H__
#define __KnotFlyMan_H__
#include "ObjectMan.h"

class KnotFlyMan : public ObjectMan
{
public:
	KnotFlyMan(Ogre::SceneNode*n);
	virtual ~KnotFlyMan();

	bool mousePicking(const OgreBites::MouseButtonEvent& evt) { return true; }
	void frameRendered(const Ogre::FrameEvent & evt);


private:

	Ogre::Entity* knotFly;
};

#endif