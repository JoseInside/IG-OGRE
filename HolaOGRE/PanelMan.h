#pragma once
#include "ObjectMan.h"

class PanelMan : public ObjectMan
{
public:
	PanelMan();
	~PanelMan();

	bool mousePressed(const OgreBites::MouseButtonEvent& evt){ return true; }
	void frameRendered(const Ogre::FrameEvent & evt){}
};

