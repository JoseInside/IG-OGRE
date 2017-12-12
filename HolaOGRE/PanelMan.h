#ifndef __PanelMan_H__
#define __PanelMan_H__
#include "ObjectMan.h"
class PanelMan :
	public MyApplicationContext, public ObjectMan
{
public:
	PanelMan(Ogre::SceneNode*n, Ogre::TexturePtr r);
	virtual ~PanelMan(); 
	
	bool mousePicking(const OgreBites::MouseButtonEvent& evt) { return true; }
	void frameRendered(const Ogre::FrameEvent & evt) {  }
private:
	OgreBites::InputListener* list = new OgreBites::InputListener();
	Ogre::SceneNode*node;
	Ogre::Entity* ent;
	Ogre::Camera* camRef;
	Ogre::TexturePtr rttTex;
};
#endif
