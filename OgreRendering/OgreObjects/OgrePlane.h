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



#ifndef OGREPLANE_H_
#define OGREPLANE_H_


#include "OGRE/Ogre.h"
#include "../../PhysicalKernel/InternalPhysics.h"
#include "OgreObject.h"


class OgrePlane : public OgreObject
{
protected :
	Ogre::ManualObject *myManualObject;
	Inertia::Plane * mPhysicsPlane;
	Ogre::SceneManager * mSceneMgr;
public:
	OgrePlane ( Inertia::InternalPhysics * aPhysicalWorld ,Ogre::SceneManager * aSceneMgr, Ogre::Vector3 & p1, Ogre::Vector3 & p2,Ogre::Vector3 & p3);
	virtual ~OgrePlane ( );
	virtual void Update();
};

#endif /* OGREPLANE_H_ */
