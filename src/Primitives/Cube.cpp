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

#include "Cube.h"
#include <iostream>


using namespace Inertia;

Cube::Cube(double dimension)
{
	mObjectType	= CUBE;
	mInitialPosition =	NILVECTOR;
	mPosition =	NILVECTOR;
	mVelocity =	NILVECTOR;
	mAcceleration =	NILVECTOR;
	mDimension	= dimension;
	mIsMoving =	true;
	mMass=DEFAULTCUBEMASS;
	mOrientation = Vector4(1.0,0.0,0.0,0.0);
}

Cube::Cube(double dimension, Vector3  & aCenterPosition)
{
	mObjectType = CUBE;
	mInitialPosition =	aCenterPosition;
	mPosition =	mInitialPosition;
	mVelocity =	NILVECTOR;
	mAcceleration =	NILVECTOR;
	mNewPosition=aCenterPosition;
	mCollisionPosition=mNewPosition;
	mDimension = dimension;
	mIsMoving =	true;
	mMass=DEFAULTCUBEMASS;
	mOrientation = Vector4(1.0,0.0,0.0,0.0);
}

Cube::Cube(int aMass, double dimension, Vector3 & aPosition)
{
	mObjectType	= CUBE;
	mInitialPosition =	aPosition;
	mPosition =	mInitialPosition;
	mVelocity =	NILVECTOR;
	mAcceleration =	NILVECTOR;
	mNewPosition=aPosition;
	mCollisionPosition=mNewPosition;

	mDimension	= dimension;
	mIsMoving =	true;
	mMass=aMass;
	mOrientation = Vector4(1.0,0.0,0.0,0.0);

}

Cube::Cube(int aMass,double dimension, Vector3 & aPosition, Vector4 & anOrientation)
{
	mObjectType	= CUBE;
	mInitialPosition =	aPosition;
	mPosition =	mInitialPosition;
	mNewPosition=aPosition;
	mCollisionPosition=mNewPosition;

	mVelocity =	NILVECTOR;
	mAcceleration =	NILVECTOR;
	mDimension	= dimension;
	mMass = aMass;
	mIsMoving =	true;
	mOrientation = anOrientation;

}


Cube::~Cube ( )
{

}

double Cube::GetDimension()
{
	return mDimension;
}


