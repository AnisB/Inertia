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


#include "OgrePlane.h"
#include <iostream>
#include "../../PhysicConstants.h"
OgrePlane::OgrePlane (  Inertia::InternalPhysics * aPhysicalWorld ,Ogre::SceneManager * aSceneMgr, Ogre::Vector3 & p1, Ogre::Vector3 & p2,Ogre::Vector3 & p3)
{
	Vector3 ap1=Vector3(p1.x,p1.y,p1.z);
	Vector3 ap2=Vector3(p2.x,p2.y,p2.z);
	Vector3 ap3=Vector3(p3.x,p3.y,p3.z);
	Ogre::Vector3 inter((p1+p3)/2);
	Ogre::Vector3 p4(2*inter-p2);
	mPhysicsPlane=  new Inertia::Plane(ap1,ap2,ap3);
	mPhysicalWorld = aPhysicalWorld;
	mPhysicalWorld->addNewCollisionalObject(mPhysicsPlane);
	mNode = aSceneMgr->getRootSceneNode()->createChildSceneNode();

	mSceneMgr=aSceneMgr;


	myManualObject = mSceneMgr->createManualObject();
	myManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

	myManualObject->position(p1.x,p1.y,p1.z);  // start position

	myManualObject->position(p2.x,p2.y,p2.z);  // draw first line

	myManualObject->position(p2.x,p2.y,p2.z);
	myManualObject->position(p3.x,p3.y,p3.z);

	myManualObject->position(p3.x,p3.y,p3.z);
	myManualObject->position(p4.x,p4.y,p4.z);
	myManualObject->position(p4.x,p4.y,p4.z);
	myManualObject->position(p1.x,p1.y,p1.z);  // start position

	myManualObject->end();
	mNode->attachObject(myManualObject);
	mNode->setPosition(0,0,0);
}

OgrePlane::~OgrePlane ( )
{
	// TODO Auto-generated destructor stub
}


void OgrePlane::Update()
{
//	mNode->setPosition(mPhysicsPlane->GetPosition().GetX(),mPhysicsPlane->GetPosition().GetY(),mPhysicsPlane->GetPosition().GetZ());
}




