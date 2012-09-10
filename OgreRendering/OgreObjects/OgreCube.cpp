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

#include "OgreCube.h"
#include <iostream>
using namespace std;

OgreCube::OgreCube(Inertia::InternalPhysics * aPhysicalWorld ,Ogre::SceneManager * aSceneMgr, Ogre::Vector3 & p1)
{
	Vector3 aPoint(p1.x, p1.y,p1.z);
	mPhysicsCube =  new Inertia::Cube(10.0,aPoint);
	mPhysicalWorld = aPhysicalWorld;
	mPhysicalWorld->addNewCollisionalObject(mPhysicsCube);
	mNode = aSceneMgr->getRootSceneNode()->createChildSceneNode();
	mNode->setPosition(p1);
	mSceneMgr=aSceneMgr;
	mObject= mSceneMgr->createEntity(Ogre::SceneManager::PT_CUBE);
	mNode->scale(0.2f,0.2f,0.2f);
	mNode->attachObject(mObject);
}

OgreCube::~OgreCube() {
}


void OgreCube::Update()
{
	mNode->setPosition(mPhysicsCube->GetPosition().GetX(),mPhysicsCube->GetPosition().GetY(),mPhysicsCube->GetPosition().GetZ());
}




void OgreCube::SetGravity()
{
	mPhysicsCube->AddNewConstantForce(Vector3(0.0f,0.0f,-mPhysicsCube->GetMass()*Inertia::g));
}


void OgreCube::AddNewImpultionalForce(Ogre::Vector3 aForce)
{

}

void OgreCube::AddNewConstantForce(Ogre::Vector3 aForce)
{
	mPhysicsCube->AddNewConstantForce(Vector3(aForce.x,aForce.y,aForce.z));
}
