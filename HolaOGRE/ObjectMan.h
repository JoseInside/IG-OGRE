#ifndef __ObjectMan_H__
#define __ObjectMan_H__

#include "MyApplicationContext.h"
#include <OgreTrays.h>
#include <OgreCameraMan.h>
class ObjectMan
{
public:

	ObjectMan(Ogre::SceneNode* sn = nullptr){ nodo = sn; };
	virtual ~ObjectMan(){};

	virtual bool mousePicking(const OgreBites::MouseButtonEvent& evt) = 0;
	virtual void frameRendered(const Ogre::FrameEvent & evt) = 0;
protected:
	Ogre::SceneNode* nodo; // nodo->getCreator() 
	Ogre::RenderTexture* renderTexture;
};

#endif