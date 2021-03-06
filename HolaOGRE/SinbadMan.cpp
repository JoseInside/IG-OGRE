#include "SinbadMan.h"

using namespace Ogre;
SinbadMan::SinbadMan(Ogre::SceneNode*n) : ObjectMan(n)
{
	node = n;
	//list = new OgreBites::InputListener();
	sinbad = n->getCreator()->createEntity("entSinbad", "Sinbad.mesh");
	setObjMan(sinbad);
	// finally something to render
	node->setPosition(0, 25, 50); // es mejor mover a sinbad antes que mover el plano, ya que el reflejo se jode
	node->scale(5, 5, 5);
	//node->attachObject(sinbad);
	sinbad->setQueryFlags(1);
	
	//ESPADA MANO IZQUIERDA
	espadaL = node->getCreator()->createEntity("swordL", "Sword.mesh");
	sinbad->attachObjectToBone("Sheath.L", espadaL);

	//ESPADA MANO DERECHA
	espadaR = node->getCreator()->createEntity("swordR", "Sword.mesh");
	sinbad->attachObjectToBone("Handle.R", espadaR);
	
	
	//MOVER PIERNAS
	animStateBase = sinbad->getAnimationState("RunBase");
	animStateBase->setLoop(true);
	animStateBase->setEnabled(true);
	//MOVER BRAZOS
	animStateTop = sinbad->getAnimationState("RunTop");
	animStateTop->setLoop(true);
	animStateTop->setEnabled(true);



	WalkingAnimation();
	
	animStateWalking = node->getCreator()->createAnimationState("animSinbadWalking");
	animStateWalking->setLoop(true);
	animStateWalking->setEnabled(true);

	

	
}


SinbadMan::~SinbadMan()
{

}

void SinbadMan::frameRendered(const Ogre::FrameEvent & evt) {
	if (goToBomb){
		if (!animStateGoToBomb->hasEnded()){
			animStateGoToBomb->addTime(evt.timeSinceLastFrame);
			animStateBase->addTime(evt.timeSinceLastFrame);
		}
		else
			Die();
	}
	else if (walk){
		animStateTop->addTime(evt.timeSinceLastFrame);
		animStateBase->addTime(evt.timeSinceLastFrame);
		animStateWalking->addTime(evt.timeSinceLastFrame);
	}
	else if (dead)
		animStateWater->addTime(evt.timeSinceLastFrame);

}


//EN CUADRADO
void SinbadMan::WalkingAnimation(){

	animationWalking = node->getCreator()->createAnimation("animSinbadWalking", duracion);
	track = animationWalking->createNodeTrack(0);
	track->setAssociatedNode(node);

	TransformKeyFrame * kf;
	keyframePos = { -90, 30, 80 };	//PUNTO INICIO
	escalado = { 6, 6, 6 };

	kf = track->createNodeKeyFrame(longitudPaso * 0); 
	keyframePos += Ogre::Vector3::UNIT_X* tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(-1, 0, 0)));

	kf = track->createNodeKeyFrame(longitudPaso * 1); 
	keyframePos -= Ogre::Vector3::UNIT_X * tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(-1, 0, 0)));


	kf = track->createNodeKeyFrame(longitudPaso * 1);
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, -1)));

	kf = track->createNodeKeyFrame(longitudPaso * 2);
	keyframePos -= Ogre::Vector3::UNIT_Z * tamDesplazamiento;
	kf->setTranslate(keyframePos); 
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(0, 0, -1)));

	kf = track->createNodeKeyFrame(longitudPaso * 2);
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(1, 0, 0)));

	kf = track->createNodeKeyFrame(longitudPaso * 3);
	keyframePos += Ogre::Vector3::UNIT_X * tamDesplazamiento;
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(Vector3(0, 0, 1).getRotationTo(Vector3(1, 0, 0)));


	kf = track->createNodeKeyFrame(longitudPaso * 3);
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);

	kf = track->createNodeKeyFrame(longitudPaso * 4);
	keyframePos += Ogre::Vector3::UNIT_Z * tamDesplazamiento;
	kf->setTranslate(keyframePos); 
	kf->setScale(escalado);

}

//HACIA LA BOMBA
void SinbadMan::WalkingToBombAnimation(){
	
	animationWalkingBomb = node->getCreator()->createAnimation("animGoToBomb", duracion);//Duracion total de la animación
	track2 = animationWalkingBomb->createNodeTrack(0);//Camino 0
	track2->setAssociatedNode(node);
	
	goToBomb = true;
	animStateWalking->setEnabled(false);	
	animStateBase->setEnabled(true);
	animStateTop->setEnabled(false);
	Vector3 vistaSinbad(0, 0, 1);	//Eje hacia donde mira

	sinbad->detachObjectFromBone(espadaL);
	sinbad->attachObjectToBone("Handle.L", espadaL);

	TransformKeyFrame * kf;
	SceneNode * bomba = node->getCreator()->getEntity("entBomb")->getParentSceneNode();	//CARGAR NODO BOMBA
	keyframePos = node->getPosition();	//PUNTO INICIO
	Real initialYPos = node->getPosition().y;
	escalado = { 6, 6, 6 };
	Vector3* rot = new Vector3(bomba->getPosition().x - node->getPosition().x, 0, bomba->getPosition().z - node->getPosition().z);
	rot->normalise();
	Quaternion quat = vistaSinbad.getRotationTo(*rot);
	
	kf = track2->createNodeKeyFrame(0);
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(quat);

	kf = track2->createNodeKeyFrame(duracion);
	keyframePos = { bomba->getPosition().x, 25, bomba->getPosition().z };	//LUGAR DE LA BOMBA
	kf->setTranslate(keyframePos);
	kf->setScale(escalado);
	kf->setRotation(quat);

	animStateGoToBomb = node->getCreator()->createAnimationState("animGoToBomb");
	animStateGoToBomb->setEnabled(true);
	animStateGoToBomb->setLoop(false);
	
}

//MUERTO UNA VEZ TOCADA LA BOMBA
void SinbadMan::Die(){

	dead = true;//con esto no se volvera a mover una vez muerto si clickamos en el
	walk = false;
	goToBomb = false;
	animStateBase->setEnabled(false);
	animStateGoToBomb->setEnabled(false);
	float newDuracion = duracion * 2;
	//node->setPosition(node->getPosition().x, 1, node->getPosition().z);
	
	animationStreamWater = node->getCreator()->createAnimation("animDragSinbad", newDuracion);
	track3 = animationStreamWater->createNodeTrack(0);
	track3->setAssociatedNode(node);

	/*node->rotate(Vector3(1.0f, 0.0f, 0.0f), Radian(3.14 / 2));
	node->rotate(Vector3(0.0f, 1.0f, 0.0f), Radian(3.14));
	node->translate(Vector3(0.0f, 1.0f, 0.0f));*/

	Vector3 vistaSinbad(0, 0, 1);
	escalado = { 6, 6, 6 };
	Vector3* rot = new Vector3(0, 180, 0);
	rot->normalise();
	Quaternion quat = vistaSinbad.getRotationTo(*rot);


	TransformKeyFrame * kf;
	keyframePos = node->getPosition();
	keyframePos -= Ogre::Vector3::UNIT_Y * 25;

	kf = track3->createNodeKeyFrame(0);
	kf->setScale(escalado);
	kf->setTranslate(keyframePos);
	kf->setRotation(quat);

	kf = track3->createNodeKeyFrame(newDuracion);
	keyframePos += Vector3::UNIT_X* tamDesplazamiento;
	kf->setScale(escalado);
	kf->setTranslate(keyframePos);
	kf->setRotation(quat);

	animStateWater = node->getCreator()->createAnimationState("animDragSinbad");
	animStateWater->setEnabled(true);
	animStateWater->setLoop(false);
	
	
}
bool SinbadMan::mousePicking(const OgreBites::MouseButtonEvent& evt){

	if (!dead && !goToBomb){ 
		walk = !walk;
		animStateWalking->setEnabled(walk);
		animStateBase->setEnabled(walk);
	}

	return true;
}
void SinbadMan::WaterDragAnimation(){

	

	

}