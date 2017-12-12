#include "PanelMan.h"

using namespace Ogre;
PanelMan::PanelMan(Ogre::SceneNode*n, Ogre::TexturePtr r)
{
	node = n;
	rttTex = r;

	node->scale(0.3, 0.3, 0.3);
	node->pitch(Ogre::Degree(-90));
	node->setPosition(0, -25, -50);



	// camref
	camRef = n->getCreator()->createCamera("RefCam");

	camRef->enableReflection(Plane(Vector3::UNIT_Y, 0));
	camRef->enableCustomNearClipPlane(Plane(Vector3::UNIT_Y, 0));


	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(10000);
	camRef->setAutoAspectRatio(true);

	n->attachObject(camRef);
	//n->attachObject(n->getCreator()->getCamera("Cam"));




	 ent = n->getCreator()->createEntity("entFondo", "mFondo");
	
	 // material del plano
	MyApplicationContext::addInputListener(list);
	/*ent->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0) ->
		createTextureUnitState("RustedMetal.jpg");*/
	ent->getSubEntity(0)->setMaterialName("panel", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	node->attachObject(ent);

	// Añadimos un puerto de vista al RenderTarget con la nueva cámara
	RenderTexture* renderTexture = rttTex->getBuffer()->getRenderTarget();
	Viewport * v = renderTexture->addViewport(camRef);
	v->setClearEveryFrame(true);
	v->setBackgroundColour(ColourValue::Black);

	//setMaterialName("panel", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	// Añadimos la nueva textura (reflejo) al material del panel
	TextureUnitState* t = ent->getSubEntity(0)->getMaterial()->
		getTechnique(0)->getPass(0)->
		createTextureUnitState("texRtt");
	t->setColourOperation(LBO_ADD); // backgroundColour -> black
	// LBO_MODULATE / LBO_REPLACE / LBO_ALPHA_BLEND;
	t->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
	t->setProjectiveTexturing(true, camRef);

	ent->setQueryFlags(0);

}


PanelMan::~PanelMan()
{

	MyApplicationContext::removeInputListener(list);
}
