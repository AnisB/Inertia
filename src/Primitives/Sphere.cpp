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

#include "Sphere.h"
#include <iostream>


using namespace Inertia;

Sphere::Sphere(double aRadius)
{
	mObjectType	= SPHERE;
	mInitialPosition =	NILVECTOR;
	mPosition =	NILVECTOR;
	mVelocity =	NILVECTOR;
	mAcceleration =	NILVECTOR;
	mRadius	= aRadius;
	mIsMoving =	true;
	mMass=DEFAULTSPHEREMASS;
}

Sphere::Sphere(double aRadius, double aCenterX, double aCenterY, double aCenterZ)
{
	mObjectType = SPHERE;
	mInitialPosition =	Vector3( aCenterX, aCenterY, aCenterZ);
	mPosition =	mInitialPosition;
	mVelocity =	NILVECTOR;
	mAcceleration =	NILVECTOR;
	mNewPosition=Vector3( aCenterX, aCenterY, aCenterZ);
	mCollisionPosition=mNewPosition;
	mRadius = aRadius;
	mIsMoving =	true;
	mMass=DEFAULTSPHEREMASS;
}

Sphere::Sphere(double aRadius, Vector3 & aPosition)
{
	mObjectType	= SPHERE;
	mInitialPosition =	aPosition;
	mPosition =	mInitialPosition;
	mVelocity =	NILVECTOR;
	mAcceleration =	NILVECTOR;
	mNewPosition=aPosition;
	mCollisionPosition=mNewPosition;

	mRadius	= aRadius;
	mIsMoving =	true;
	mMass=DEFAULTSPHEREMASS;

}

Sphere::Sphere(int aMass, double aRadius, Vector3 & aPosition)
{
	mObjectType	= SPHERE;
	mInitialPosition =	aPosition;
	mPosition =	mInitialPosition;
	mNewPosition=aPosition;
	mCollisionPosition=mNewPosition;

	mVelocity =	NILVECTOR;
	mAcceleration =	NILVECTOR;
	mRadius	= aRadius;
	mMass = aMass;
	mIsMoving =	true;

}


Sphere::~Sphere ( )
{

}

double Sphere::GetRadius()
{
	return mRadius;
}


