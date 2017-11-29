#pragma once
#include "ObjectMan.h"

class SinbadMan : public ObjectMan
{
public:
	SinbadMan();
	~SinbadMan();

	bool mousePressed(const OgreBites::MouseButtonEvent& evt){ return true; }
	void frameRendered(const Ogre::FrameEvent & evt){}
};

