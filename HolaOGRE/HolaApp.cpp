#include "HolaApp.h"

/*
	PRACTICA 3 - OGRE
*/

using namespace Ogre;

void HolaApp::frameRendered(const FrameEvent &  evt)
{

	for (int i = 0; i < vecObjMan.size(); ++i){
		vecObjMan[i]->frameRendered(evt);
	}

}

bool HolaApp::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  
    mRoot->queueEndRendering();
  
 
  return true;
}

bool HolaApp::mousePressed(const OgreBites::MouseButtonEvent &  evt)
{
	rayScnQuery->setRay(cam->getCameraToViewportRay(
		evt.x / (Real)mWindow->getViewport(0)->getActualWidth(),
		evt.y / (Real)cam->getViewport()->getActualHeight()));
	// coordenadas normalizadas en [0,1]
	RaySceneQueryResult& qryResult = rayScnQuery->execute();
	RaySceneQueryResult::iterator it = qryResult.begin();
	
	if (it != qryResult.end()) {

			box = !box;
			it->movable->getParentSceneNode()->showBoundingBox(box);
	}

  return true;
}

bool HolaApp::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
  trayMgr->mouseMoved(evt);
  
  return true;
}

void HolaApp::setupInput()
{
  // do not forget to call the base first
  MyApplicationContext::setupInput(); 
  // register for input events
  addInputListener(this);
}

void HolaApp::shutdown()
{
	for (int i = 0; i<vecObjMan.size(); ++i)
	{
		delete vecObjMan[i];
	}
  //scnMgr->removeRenderQueueListener(mOverlaySystem);
  delete trayMgr;  trayMgr = nullptr;
  // do not forget to call the base 
  MyApplicationContext::shutdown();
}

void HolaApp::setup(void)
{
  // do not forget to call the base first
  MyApplicationContext::setup();

  scnMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(scnMgr);

  scnMgr->addRenderQueueListener(mOverlaySystem);

  trayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow);
  trayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);

  rayScnQuery = scnMgr->createRayQuery(Ray());
  setupScene();
}

void HolaApp::setupScene(void)
{
  // without light we would just get a black screen    
  Light* light = scnMgr->createLight("Light");
  light->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y); // !!! opngl <-> direcci�n a la fuente de luz
  lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  lightNode->setPosition(0, 100, 0);
  lightNode->attachObject(light);

  // also need to tell where we are
  camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
  camNode->setPosition(0, 0, 100);
  camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_WORLD);

  // create the camera
  cam = scnMgr->createCamera("Cam");

  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);


  //cam->setPolygonMode(Ogre::PM_WIREFRAME);  // en material
  camNode->attachObject(cam);

  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);

  camMng = new OgreBites::CameraMan(camNode);
  addInputListener(camMng);
  camMng->setStyle(OgreBites::CS_ORBIT);


  //Sinbad
  Ogre::SceneNode*node = scnMgr->getRootSceneNode()->createChildSceneNode("nSinbad");
  SinbadMan* aux = new SinbadMan(node);
  vecObjMan.push_back(aux);
  /*
  float duracion = 4.0f;
  Ogre::Vector3 keyframePos = { 0, 0, 0 };
  float tamDesplazamiento = 2.0f;
  
  //WalkingAnimation
  Animation * animation = scnMgr->createAnimation("animKnot", duracion);
  NodeAnimationTrack * track = animation->createNodeTrack(0);
  track->setAssociatedNode(node);

  Real longitudPaso = duracion / 4.0;


  TransformKeyFrame * kf;; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
  kf = track->createNodeKeyFrame(longitudPaso * 0); // Keyframe 0: origen.
  kf->setTranslate(keyframePos); // Origen: Vector3

  kf = track->createNodeKeyFrame(longitudPaso * 1); // Keyframe 1: arriba.
  keyframePos += Ogre::Vector3::UNIT_Y * tamDesplazamiento;
  kf->setTranslate(keyframePos); // Arriba
  // Keyframe 2: origen. �.
  kf = track->createNodeKeyFrame(longitudPaso * 3); // Keyframe 3: abajo.
  keyframePos += Ogre::Vector3::UNIT_Y * tamDesplazamiento * -2;
  kf->setTranslate(keyframePos); // Abajo
  kf = track->createNodeKeyFrame(longitudPaso * 4); // Keyframe 4: origen.
  keyframePos += Ogre::Vector3::UNIT_Y * tamDesplazamiento;
  kf->setTranslate(keyframePos); // Origen.

  AnimationState * animationState = scnMgr->createAnimationState("animKnot");
  animationState->setLoop(true);
  animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
  animationState->setEnabled(true);
  */


  //Textura del plano (reflejo)
  TexturePtr rttTex = TextureManager::getSingleton().createManual(
	  "texRtt",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  TEX_TYPE_2D,
	  (Real)mWindow->getViewport(0)->getActualWidth(),
	  (Real)cam->getViewport()->getActualHeight(),
	  0, PF_R8G8B8, TU_RENDERTARGET);

  //plano
  Ogre::SceneNode* nodePlane = scnMgr->getRootSceneNode()->createChildSceneNode("nPlane");
  MeshPtr plane = MeshManager::getSingleton().createPlane("mFondo",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  Plane(Vector3::UNIT_Z, 0),
	  (Real)mWindow->getViewport(0)->getActualWidth(),
	  (Real)cam->getViewport()->getActualHeight(),
	  10, 10, true, 1, 1.0, 1.0, Vector3::UNIT_Y);
  PanelMan* aux2 = new PanelMan(nodePlane, rttTex);
  vecObjMan.push_back(aux2);


  // scene queries
  rayScnQuery ->setQueryTypeMask(SceneManager::ENTITY_TYPE_MASK);
  rayScnQuery->setQueryMask(MY_QUERY_MASK);
  rayScnQuery->setSortByDistance(true);

  


}


void HolaApp::WalkingAnimation(){

	

}
