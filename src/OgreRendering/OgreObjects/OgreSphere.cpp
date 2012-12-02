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


#include "OgreSphere.h"
#include <iostream>
#include "../../PhysicConstants.h"
OgreSphere::OgreSphere (  Inertia::InternalPhysics * aPhysicalWorld ,Ogre::SceneManager * aSceneMgr, Ogre::Vector3 & a)
{
	mPhysicsSphere =  new Inertia::Sphere(10.0,a.x, a.y,a.z);
	mPhysicalWorld = aPhysicalWorld;
	mPhysicalWorld->addNewCollisionalObject(mPhysicsSphere);
	mNode = aSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->setPosition(a);
	mSceneMgr=aSceneMgr;
	mObject= mSceneMgr->createEntity(Ogre::SceneManager::PT_SPHERE);
	mNode->scale(0.2f,0.2f,0.2f);
	mNode->attachObject(mObject);
}

OgreSphere::~OgreSphere ( )
{
	// TODO Auto-generated destructor stub
}


void OgreSphere::Update()
{
	mNode->setPosition(mPhysicsSphere->GetPosition().GetX(),mPhysicsSphere->GetPosition().GetY(),mPhysicsSphere->GetPosition().GetZ());
}




void OgreSphere::SetGravity()
{
	mPhysicsSphere->AddNewConstantForce(Vector3(0.0f,0.0f,-mPhysicsSphere->GetMass()*Inertia::g));
}


void OgreSphere::AddNewImpultionalForce(Ogre::Vector3 aForce)
{

}

void OgreSphere::AddNewConstantForce(Ogre::Vector3 aForce)
{
	mPhysicsSphere->AddNewConstantForce(Vector3(aForce.x,aForce.y,aForce.z));
}
