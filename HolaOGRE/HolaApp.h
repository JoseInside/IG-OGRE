#ifndef __HolaApp_H__
#define __HolaApp_H__

#include "MyApplicationContext.h"
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "OgreRenderTargetListener.h"
#include "ObjectMan.h"

class HolaApp :
	public MyApplicationContext, public OgreBites::InputListener, public Ogre::RenderTargetListener
{
public:
  explicit HolaApp() : MyApplicationContext("HolaApp") { };
  virtual ~HolaApp(){ };   // delete ... los elementos creado con métodos factoria (create...) se destruyen automáticamente 
  
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupInput();
  virtual void setupScene();
  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
  virtual bool mousePressed(const OgreBites::MouseButtonEvent &  evt);
  virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
  virtual void frameRendered(const Ogre::FrameEvent &  evt);
  virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
  // ocultar el panel y poner luz ambiente
  virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
  // restablecer los cambios


  static const Ogre::uint32 SELECCIONABLE = 1; // << 0;
  static const Ogre::uint32 NO_SELECCIONABLE = 0;

  Ogre::SceneManager* scnMgr = nullptr;
  OgreBites::TrayManager* trayMgr = nullptr;
  OgreBites::CameraMan* cameraMgr = nullptr;
  Ogre::SceneNode* lightNode = nullptr;
  Ogre::SceneNode* camNode = nullptr;
  Ogre::RaySceneQuery* rayScnQuery = nullptr;
  Ogre::Camera* cam;

  std::vector<ObjectMan*> objectMan;
};


#endif
