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

#ifndef OGRECUBE_H_
#define OGRECUBE_H_


#include "OGRE/Ogre.h"
#include "../../PhysicalKernel/InternalPhysics.h"
#include "OgreObject.h"



class OgreCube : public OgreObject
{
public:
	OgreCube(Inertia::InternalPhysics * aPhysicalWorld ,Ogre::SceneManager * aSceneMgr, Ogre::Vector3 & p1);
	virtual ~OgreCube();
	virtual void SetGravity( );
	void AddNewConstantForce(Ogre::Vector3 aForce);
	void AddNewImpultionalForce(Ogre::Vector3 aForce);
	virtual void Update();


protected :
	Ogre::Entity* mObject;
	Inertia::Cube * mPhysicsCube;
	Ogre::SceneManager * mSceneMgr;

};

#endif /* OGRECUBE_H_ */
