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


#ifndef __OBJECT_h__
#define __OBJECT_h__

#include "../MathTools/Vector3.h"
#include "../PhysicsTools/Force.h"
#include "../PhysicConstants.h"

#include <list>


// Possible objects
enum OBJ_TYPE
{
	SPHERE,
	PLANE,
	CUBE
};

namespace Inertia
{
class Object
{

public:

	// Constructors
	Object();
	virtual ~Object();

	// Getters
	Vector3 	&	GetPosition();
	Vector3 	&	GetVelocity();
	Vector3 	&	GetAcceleration();
	Vector3 	&	GetNewPosition();
	Vector3		&	GetNewVelocity();
	Vector3 	&	GetNewAcceleration();
	Vector3 	&	GetCollisionVelocity();
	Vector3		&	GetCollisionPosition();
	double			GetDeltaPosition();
	int     		GetType();
	double     		GetMass();
	bool			IsMoving();


	// Setters
	void			SetPosition( Vector3  &newPosition );
	void			SetVelocity( Vector3 & newVelocity );
	void			SetAcceleration( Vector3  & newAcceleration );
	void			SetNewPosition( Vector3 & V );
	void			SetNewVelocity( Vector3 & V );
	void			SetNewAcceleration( Vector3 & V );
	void			SetMass( double Mass );
	void			SetCollisionPosition( Vector3 newPosition );
	void			SetCollision( Vector3 newSpeed, double newDelta);
	void			SetIsMoving( bool newSituation);
	bool			IsInCollision();
	void			ResetIsInCollision();

	// --------------------------------------------------------------- Dynamic methods
	void		AddNewVariableForce( Force newForce );
	void		RemoveVariableForces( )	;
	void		AddNewConstantForce( Vector3  newForce );
	Vector3	&	GetConstantForces( );
	std::list<Force> & GetVariableForces( );




protected:


	// Attributes

	// Typage dynamique
	OBJ_TYPE 	mObjectType;


	double		mMass;
	int			mNbCollision;

	// Paramètres dynamiques
	Vector3		mInitialPosition;
	Vector3		mPosition;
	Vector3		mVelocity;
	Vector3		mAcceleration;

	Vector3		mNewPosition;
	Vector3		mNewVelocity;
	Vector3		mNewAcceleration;

	Vector3		mCollisionSpeed;
	Vector3		mCollisionPosition;
	double		mDeltaPosition;

	bool		mIsOnCollision;
	bool		mIsMoving;

	// Forces
	std::list<Force>	  mVariableForces;
	Vector3		  mConstantForces;

};
}
#endif
