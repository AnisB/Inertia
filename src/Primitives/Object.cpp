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

// includes
#include "Object.h"
#include <iostream>

using namespace Inertia;
Object::Object ( )
{
	mNbCollision=0;
	mDeltaPosition = 0.10f;
	mIsOnCollision=false;
}
Object::~Object ( )
{
	std::cout<<"Probleme d'heritage"<<std::endl;
}
Vector3 & Object::GetPosition()
{

	return mPosition;
}
Vector3 & Object::GetVelocity()
{
	return mVelocity;
}
Vector3 & Object::GetAcceleration()
{
	return mAcceleration;
}
Vector3  &Object::GetNewPosition()
{
	return mNewPosition;
}
Vector3	 &Object::GetNewVelocity()
{
	return mNewVelocity;
}
Vector3  &Object::GetNewAcceleration()
{
	return mNewAcceleration;
}
Vector3  &Object::GetCollisionVelocity()
{
	return mCollisionSpeed;
}
Vector3	 & Object::GetCollisionPosition()
{
	return mCollisionPosition;
}


double	Object::GetDeltaPosition()
{
	return mDeltaPosition;
}
int Object::GetType()
{
	return mObjectType;
}
double Object::GetMass()
{
	return mMass;
}

bool Object::IsMoving()
{
	return mIsMoving;
}


void Object::SetPosition( Vector3  &newPos )
{

	mPosition = newPos;

}
void Object::SetVelocity( Vector3  &newVelocity )
{
	mVelocity = newVelocity;
}
void Object::SetAcceleration( Vector3 & newAcceleration )
{
	mAcceleration = newAcceleration;
}
void Object::SetNewPosition( Vector3 & newPosition )
{
	mNewPosition = newPosition;
}
void Object::SetNewVelocity( Vector3  &newVelocity )
{
	mNewVelocity = newVelocity;
}
void Object::SetNewAcceleration( Vector3 & V )
{
	mNewAcceleration = V;
}
void Object::SetMass( double aMass )
{
	mMass = aMass;
}

void Object::SetCollisionPosition( Vector3 _vPos )
{
	mCollisionPosition = _vPos;
}
void Object::SetCollision( Vector3 newSpeed, double newDelta)
{
	mCollisionSpeed = newSpeed;
	mDeltaPosition = newDelta ;
	mIsOnCollision = true;
	mNbCollision++;
}

void Object::SetIsMoving( bool newSituation)
{
	mIsMoving = newSituation;
}


bool Object::IsInCollision()
{
	return mIsOnCollision;
}
void Object::ResetIsInCollision()
{
	mCollisionSpeed = NILVECTOR;
	mDeltaPosition= 0.0f;
	mIsOnCollision = false;
	mNbCollision=0;
}


void Object::AddNewVariableForce( Force newForce )
{
	mVariableForces.push_back(newForce);
}
void Object::RemoveVariableForces( )
{
	mVariableForces.clear();
}
void Object::AddNewConstantForce( Vector3  newForce )
{
	mConstantForces += newForce;
}
Vector3 & Object::GetConstantForces()
{
	return mConstantForces;
}

std::list<Force> & Object::GetVariableForces( )
{
	return mVariableForces;
}
