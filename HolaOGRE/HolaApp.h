#ifndef __HolaApp_H__
#define __HolaApp_H__

#include "MyApplicationContext.h"
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include "ObjectMan.h"
#include "SinbadMan.h"
#include "BombMan.h"
#include "KnotFlyMan.h"
#include "PanelMan.h"

class HolaApp :
  public MyApplicationContext, public OgreBites::InputListener
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

  Ogre::SceneManager* scnMgr = nullptr;
  OgreBites::TrayManager* trayMgr = nullptr;
  Ogre::SceneNode* lightNode = nullptr;
  Ogre::SceneNode* camNode = nullptr;
  OgreBites::CameraMan* camMng = nullptr;
  Ogre::RaySceneQuery* rayScnQuery = nullptr;
  Ogre::Camera *cam = nullptr;




  static const Ogre::uint32 MY_QUERY_MASK = 1; // << 0;
  static const Ogre::uint32 ZERO_QUERY_MASK = 0;

  std::vector<ObjectMan*> vecObjMan;
  bool box = false;
 

};


#endif
