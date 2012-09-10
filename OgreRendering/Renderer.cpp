/**
  * This file belongs to the Inertia project
  *
  * @see https://github.com/AnisB/Inertia
  * @author 2012-2013 Anis Benyoub <benyoub.anis@gmail.com>
  * @see The GNU Public License (GPL)
  */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */


#include "Renderer.h"
#include "OGRE/Ogre.h"



#include <iostream>
using namespace std;

Renderer::Renderer()
{
		Start();
}


Renderer::~Renderer()
{

}


void Renderer::Start()
{

	myLogManager = new  Ogre::LogManager();
	myLogManager->createLog("Ogre.log" , true, false, true);
	mPhysicsWorld = new Inertia::InternalPhysics();
	mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");

		//CHARGEMENT CONFIG & RESSOURCES
			InitMaterials();
			if (!InitConfigs())
			{
				return ;
			}
		//Creation de la scene principale
		mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "Fenetre Principale");

		//DEVICES
		mWindow = mRoot->initialise(true, "Inertia");



		//CREATION DE LA SCENE
		Scene4();

		//Creation de l'input listener
		CreateFrameListener();


		//----------------------------------------Phase moteur

		//DEBUT DE LA BOUCLE DE RENDU
		mRoot->startRendering();


		//-------------------------------------Phase destruction

		mRoot->destroySceneManager(mSceneMgr);
		delete mRoot;

}

void Renderer::InitMaterials()
{
	//Chargement des matériaux , des meshs et de tout ce qu'on a comme ressource
	Ogre::ConfigFile cf;
	cf.load("resources.cfg");
	Ogre::ConfigFile::SectionIterator sectionIter = cf.getSectionIterator();

				Ogre::String sectionName, typeName, dataName;
				Ogre::ConfigFile::SettingsMultiMap * settings;
				Ogre::ConfigFile::SettingsMultiMap::iterator i;
				while (sectionIter.hasMoreElements())
				{
					sectionName = sectionIter.peekNextKey();
					settings = sectionIter.getNext();

					for (i = settings->begin(); i != settings->end(); ++i)
					{
						typeName = i->first;
						dataName = i->second;

						Ogre::ResourceGroupManager::getSingleton().addResourceLocation(dataName, typeName, sectionName);
					}
				}

				Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	//fin chargement materials
}

bool Renderer::InitConfigs()
{
	if(!mRoot->restoreConfig())
	{
		if(!mRoot->showConfigDialog())
		{
			return false; //erreur de chargement config
		}
	}
	return true;
}


void Renderer::Scene1()
{

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));


		 Ogre::Light * light = mSceneMgr->createLight("Light");
		 light->setType(Ogre::Light::LT_POINT);
		 light->setDirection(Ogre::Vector3(1, -1, 0));
		 light->setDiffuseColour(0.8, 0.8, 0.8);
		 light->setSpecularColour(0.8, 0.5, 0.8);
		 light->setPosition(100, 250, 100);

		//Camera
		mCamera = mSceneMgr->createCamera("PlayerCamera");


		//Screens
		Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));


		// Parametrage du point de vue
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));




		Ogre::Vector3 pos1(50.0f,50.0f,50.0f);
		mSphere  = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos1);
		ObjectList.push_back(mSphere);
		mSphere->SetGravity();

		Ogre::Vector3 pos2(0.0f,0.0f,100.0f);
		OgreSphere * aSphere2 = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos2);
		aSphere2->SetGravity();
		ObjectList.push_back(aSphere2);

		Ogre::Vector3 pos3(0.0f,50.0f,200.0f);
		OgreSphere * aSphere3 = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos3);
		aSphere3->SetGravity();
		ObjectList.push_back(aSphere3);

		Ogre::Vector3 pos4(50.0f,0.0f,300.0f);
		OgreSphere * aSphere4 = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos4);
		aSphere4->SetGravity();
		ObjectList.push_back(aSphere4);

		Ogre::Vector3 pos5(80.0f,-80.0f,100.0f);
		OgreSphere * aSphere5= new OgreSphere(mPhysicsWorld ,mSceneMgr,pos5);
		aSphere5->SetGravity();
		ObjectList.push_back(aSphere5);

		Ogre::Vector3 pos6(40.0f,-80.0f,150.0f);
		OgreSphere * aSphere6= new OgreSphere(mPhysicsWorld ,mSceneMgr,pos6);
		aSphere6->SetGravity();
		ObjectList.push_back(aSphere6);

		Ogre::Vector3 pos7(80.0f,-840.0f,200.0f);
		OgreSphere * aSphere7= new OgreSphere(mPhysicsWorld ,mSceneMgr,pos7);
		aSphere7->SetGravity();
		ObjectList.push_back(aSphere7);


		Ogre::Vector3 p1(-100.0f,100.0f,0.0f);
		Ogre::Vector3 p2(100.0f,100.0f,0.0f);
		Ogre::Vector3 p3(100.0f,-100.0f,0.0f);
		OgrePlane * aPlane = new OgrePlane(mPhysicsWorld ,mSceneMgr,p1,p2,p3);
		ObjectList.push_back(aPlane);






}



void Renderer::Scene2()
{
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));


		 Ogre::Light * light = mSceneMgr->createLight("Light");
		 light->setType(Ogre::Light::LT_POINT);
		 light->setDirection(Ogre::Vector3(1, -1, 0));
		 light->setDiffuseColour(0.8, 0.8, 0.8);
		 light->setSpecularColour(0.8, 0.5, 0.8);
		 light->setPosition(100, 250, 100);

		//Camera
		mCamera = mSceneMgr->createCamera("PlayerCamera");


		//Screens
		Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

		// Parametrage du point de vue
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));




		Ogre::Vector3 pos1(0.0f,0.0f,70.0f);
		mSphere  = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos1);
		ObjectList.push_back(mSphere);
		mSphere->SetGravity();

		Ogre::Vector3 pos2(0.0f,0.0f,150.0f);
		OgreSphere * aSphere = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos2);
		aSphere->SetGravity();
		ObjectList.push_back(aSphere);

		Ogre::Vector3 pos3(0.0f,0.0f,200.0f);
		OgreSphere * aSphere2 = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos3);
		aSphere2->SetGravity();
		ObjectList.push_back(aSphere2);

		Ogre::Vector3 pos4(0.0f,0.0f,250.0f);
		OgreSphere * aSphere3 = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos4);
		aSphere3->SetGravity();
		ObjectList.push_back(aSphere3);

		Ogre::Vector3 p1(-100.0f,100.0f,0.0f);
		Ogre::Vector3 p2(100.0f,100.0f,0.0f);
		Ogre::Vector3 p3(100.0f,-100.0f,0.0f);
		OgrePlane * aPlane = new OgrePlane(mPhysicsWorld ,mSceneMgr,p1,p2,p3);
		ObjectList.push_back(aPlane);
		





}

void Renderer::Scene3()
{
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));


		 Ogre::Light * light = mSceneMgr->createLight("Light");
		 light->setType(Ogre::Light::LT_POINT);
		 light->setDirection(Ogre::Vector3(1, -1, 0));
		 light->setDiffuseColour(0.8, 0.8, 0.8);
		 light->setSpecularColour(0.8, 0.5, 0.8);
		 light->setPosition(100, 250, 100);

		//Camera
		mCamera = mSceneMgr->createCamera("PlayerCamera");


		//Screens
		Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

		// Parametrage du point de vue
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));




		Ogre::Vector3 pos1(0.0f,0.0f,50.0f);
		mSphere  = new OgreSphere(mPhysicsWorld ,mSceneMgr,pos1);
		ObjectList.push_back(mSphere);
		mSphere->SetGravity();



		Ogre::Vector3 p1(-100.0f,100.0f,0.0f);
		Ogre::Vector3 p2(100.0f,100.0f,0.0f);
		Ogre::Vector3 p3(100.0f,-100.0f,-100.0f);
		OgrePlane * aPlane = new OgrePlane(mPhysicsWorld ,mSceneMgr,p1,p2,p3);
		ObjectList.push_back(aPlane);

		Ogre::Vector3 p4(-100.0f,2000.0f,-100.0f);
		Ogre::Vector3 p5(100.0f,2000.0f,-100.0f);
		Ogre::Vector3 p6(100.0f,-2000.0f,-100.0f);
		OgrePlane * aPlane2 = new OgrePlane(mPhysicsWorld ,mSceneMgr,p4,p5,p6);
		ObjectList.push_back(aPlane2);




}













void Renderer::Scene4()
{
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


		mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4, 0.4, 0.4));


		 Ogre::Light * light = mSceneMgr->createLight("Light");
		 light->setType(Ogre::Light::LT_POINT);
		 light->setDirection(Ogre::Vector3(1, -1, 0));
		 light->setDiffuseColour(0.8, 0.8, 0.8);
		 light->setSpecularColour(0.8, 0.5, 0.8);
		 light->setPosition(100, 250, 100);

		//Camera
		mCamera = mSceneMgr->createCamera("PlayerCamera");


		//Screens
		Ogre::Viewport* vp = mWindow->addViewport(mCamera);
		vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

		// Parametrage du point de vue
		mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));




		Ogre::Vector3 p1(-100.0f,100.0f,100.0f);
		OgreCube * aCube = new OgreCube(mPhysicsWorld ,mSceneMgr,p1);
		aCube->SetGravity();
		ObjectList.push_back(aCube);



		Ogre::Vector3 p4(-100.0f,100.0f,0.0f);
		Ogre::Vector3 p2(100.0f,100.0f,0.0f);
		Ogre::Vector3 p3(100.0f,-100.0f,0.0f);
		OgrePlane * aPlane = new OgrePlane(mPhysicsWorld ,mSceneMgr,p4,p2,p3);
		ObjectList.push_back(aPlane);






}

void Renderer::CreateFrameListener()
//Creation de l'input listener et passage en parametre de l'ensemble des joueurs
{
	mInputManager= new InputListener(mWindow,this,mCamera);
        mRoot->addFrameListener(mInputManager);
}



void  Renderer::Update(double dt)
{
	mPhysicsWorld->Step(dt*0.001);

	for(std::list<OgreObject * >::iterator them= ObjectList.begin();them!=ObjectList.end();them++)
	{
		(*them)->Update();
	}

}

void  Renderer::Step()
{
	mPhysicsWorld->Step(0.05);

	for(std::list<OgreObject * >::iterator them= ObjectList.begin();them!=ObjectList.end();them++)
	{
		(*them)->Update();
	}

}
