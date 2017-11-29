#pragma once
#include <Ogre.h>
#include "OgreRenderTargetListener.h"

class RenderTargetListener : public Ogre::RenderTargetListener
{
public:
	RenderTargetListener(Ogre::SceneNode* scnNode);
	~RenderTargetListener();
	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
	virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

};

