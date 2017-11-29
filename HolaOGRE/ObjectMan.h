#pragma once
#include <Ogre.h>
#include <OgreTrays.h>
class ObjectMan
{
public:

	ObjectMan(Ogre::SceneNode* sn = nullptr){ nodo = sn; };
	virtual ~ObjectMan();

	bool mousePressed(const OgreBites::MouseButtonEvent& evt){ return true; }
	void frameRendered(const Ogre::FrameEvent & evt){}

	Ogre::SceneNode* nodo; // nodo->getCreator() 

};

