#ifndef __ObjectMan_H__
#define __ObjectMan_H__

#include "MyApplicationContext.h"
#include <OgreTrays.h>
#include <OgreCameraMan.h>

#include "MyApplicationContext.h"

class ObjectMan; // declaración adelantada

class UserControl { // clase recubridora
public:
	ObjectMan* getControl() { return object; };
	friend class ObjectMan;
protected:
	UserControl(ObjectMan * obj) : object(obj) { };
	~UserControl() { };
	ObjectMan * object; // ObjectMan: clase raíz de una jerarquía
};

class ObjectMan
{
public:

	ObjectMan(Ogre::SceneNode* scnNode) : node(scnNode)
	{
		control = new UserControl(this);
	};

	virtual ~ObjectMan(){
		UserControl* pCtrl = Ogre::any_cast<UserControl*>(
			node->getAttachedObject(0)->//Suponemos que solo puede tener controlador el primer objeto adjunto a un nodo
			getUserObjectBindings().getUserAny());
		delete pCtrl;
	};

	virtual bool mousePicking(const OgreBites::MouseButtonEvent& evt){ return true; };
	virtual void frameRendered(const Ogre::FrameEvent & evt){};
	virtual void setObjMan(Ogre::MovableObject* mObj)
		{

			if (node->getAttachedObjects().size() == 0)
			{
				node->attachObject(mObj);
				node->getAttachedObject(0)->getUserObjectBindings().setUserAny(Ogre::Any(control));
			}
		};

protected:


	Ogre::SceneNode* node = nullptr; // nodo->getCreator() 
	UserControl* control = nullptr;
	Ogre::RenderTexture* renderTexture;
	OgreBites::InputListener* list;


};



#endif