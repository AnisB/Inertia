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


#ifndef RENDERER_H_
#define RENDERER_H_


#include "OGRE/Ogre.h"
#include "InputListener.h"
#include "../PhysicalKernel/InternalPhysics.h"
#include "OgreObjects/OgreSphere.h"
#include "OgreObjects/OgrePlane.h"
#include "OgreObjects/OgreCube.h"
#include "Singleton.h"

const std::string resourcesPath="/Users/anisbenyoub/Documents/Developpement/Inertia/CMake/Resources/";


class InputListener;
class Renderer : public Singleton<Renderer>
{
protected:
    Ogre::Root* 			mRoot;
    Ogre::RenderWindow* 	mWindow;
    Ogre::SceneManager* 	mSceneMgr;

    InputListener * mInputManager;

    Ogre::Camera  * mCamera;
    Inertia::InternalPhysics * mPhysicsWorld;
    OgreSphere * mSphere;
    std::list<OgreObject *> ObjectList;
    Ogre::LogManager * myLogManager  ;



public:
    Renderer();
    virtual ~Renderer();
    Ogre::Root * getOgreRoot()
	{
	    return mRoot;
	}
    void initiate();
    void preScene();
    void render();
    void InitMaterials();
    bool InitConfigs();
    void Scene1();
    void Scene2();
    void Scene3();
    void Scene4();
    void CreateFrameListener();
    Ogre::SceneManager * getSceneManager()
	{
	    return mSceneMgr;
	}
    void Update(double dt);
    void  Step();

};

#endif /* RENDERER_H_ */


