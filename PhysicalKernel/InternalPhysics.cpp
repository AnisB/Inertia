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


#include "InternalPhysics.h"
#include "../MathTools/Vector3.h"
#include "../MathTools/Matrix.h"
#include <iostream>
#include "math.h"

using namespace Inertia;



InternalPhysics::InternalPhysics ( )
{
	mSimulationStep=0.0f;
	mStep= 1.0;

}

InternalPhysics::~InternalPhysics ( )
{
	// TODO Auto-generated destructor stub
}

void InternalPhysics::StartRendering()
{
	mIsRendering=true;
}


void InternalPhysics::StopRendering()
{
	mIsRendering=false;
}


void InternalPhysics::SetSimulationStep(double newStep)
{
	mStep=newStep;
}

void InternalPhysics::Render()
{
	while(mIsRendering)
	{
			mSimulationStep+=mStep;
		    ApplyForces(mSimulationStep);
		    Update();
		    sleep(mStep);
	}
}

void InternalPhysics::addNewCollisionalObject(Object * newObject)
{
	mCollisionalObjects.push_back(newObject);
}


void InternalPhysics::removeCollisionalObject (Object * newObject)
{
	list<Object *>::iterator it;
	for(it=mCollisionalObjects.begin();it!=mCollisionalObjects.end();it++)
	{
		if((*it)!=(newObject))
		{
			mCollisionalObjects.erase(it);
		}
	}
}


void InternalPhysics::Step(double aStep)
{
	mSimulationStep+=aStep;
    ApplyForces(mSimulationStep);
    Update();
}



void InternalPhysics::ApplyForces(double aStep)
{
	// Declaring the local variables
	Vector3 anAcceleration, anAngularAcceleration;
	Vector3 aVelocity, anAngularVelocity;
	Vector3 aPosition;
	Vector3 aSumOfForces, aSumOfMoments;


	//Initiating
	aVelocity = NILVECTOR;
	anAcceleration = NILVECTOR;
	aPosition= NILVECTOR;


	// Computing the
	list<Object*>::iterator anObject = mCollisionalObjects.begin();
	while( anObject != mCollisionalObjects.end() )
	{
		Inertia::Object  * CurrentObject = (*anObject);


		if( (*anObject)->GetType() != PLANE && (*anObject)->IsMoving())
		{
				// Re-initiating the values
				aSumOfForces = NILVECTOR;
				aSumOfMoments = NILVECTOR;


				//  Computing the forces
				list<Force>::iterator aForce = (*anObject)->GetVariableForces().begin();
				while( aForce != (*anObject)->GetVariableForces().end() )
				{
					aSumOfForces += (*aForce).GetForce();
					aSumOfMoments += ((*aForce).GetForce()).Cross((*aForce).GetApplicationPoint());
					aForce++;
				}
				aSumOfForces += (*anObject)->GetConstantForces();


				// Computing the acceleration
				anAcceleration = aSumOfForces / (*anObject)->GetMass();


				// Setting the acceleration
				(*anObject)->SetNewAcceleration( anAcceleration );

				// Computing the veocity
				aVelocity = CurrentObject->GetVelocity() + (anAcceleration * aStep);

				// Setting the velocity
				(*anObject)->SetNewVelocity( aVelocity );

				// Computing the position (Newton's 3rd theorem)
				aPosition = CurrentObject->GetPosition() + anAcceleration * aStep * aStep *0.5+ aStep * (*anObject)->GetVelocity();

				// Setting the position
				(*anObject)->SetNewPosition( aPosition );


				// Removing the variable forces
				(*anObject)->RemoveVariableForces();
			}
		++anObject;
	}
	// Fin de la boucle de calculs de la dynamique
}




void InternalPhysics::TestCollision( list<Object*>::iterator *theObject, int aNumeroObjet )
{
	int currentObject = 0;

	// We go through the list and test each collision
	list<Object*>::iterator anObject = mCollisionalObjects.begin();
	while( anObject != mCollisionalObjects.end() )
	{

		// If the object isn't the one passed in parameter
		if( currentObject != aNumeroObjet )
		{

			// Types getting
			int typeA = (**theObject)->GetType();
			int typeB = (*anObject)->GetType();


			// We are in a sphere/sphere configuration
			if( typeA==SPHERE && typeB==SPHERE )
			{
				// We test if there is and intersectio of those spheres
				if ( TestSphereSphereCollision((Sphere*)(**theObject), (Sphere*)(*anObject)) )
				{
					// Yes there is
					AddIntersection((**theObject),(*anObject) );
				}
			}

			// We are in a sphere/plane configuration
			if( typeA==SPHERE && typeB==PLANE)
			{
				// We test if there is and intersection
				if ( TestPlaneSphereCollision((Sphere*)(**theObject),(Plane*)(*anObject)) )
				{
					// Yes there is
					AddIntersection( (**theObject),(Plane*)(*anObject) );
				}
			}

			if( typeA==CUBE && typeB==PLANE)
			{
				// We test if there is and intersection
				if ( TestPlaneCubeCollision((Cube*)(**theObject),(Plane*)(*anObject)) )
				{
					// Yes there is
					AddIntersection( (**theObject),(Plane*)(*anObject) );
				}
			}

			if( typeA==CUBE && typeB==SPHERE)
			{

			}
		}
		++anObject;
		currentObject++;
	}

}


bool InternalPhysics::TestSphereSphereCollision(Sphere * aA,Sphere * aB)
{
	// Getting the distance between the centers
	Vector3 distance = aB->GetNewPosition() - aA->GetNewPosition();
	float norme = distance.Norm();

	// If the distance is less that the sum of the 2 radius so there is intersection
	return ( norme <= aA->GetRadius() + aB->GetRadius() );
	// Else , there isn't

}

bool InternalPhysics::TestPlaneCubeCollision(Cube * aA,Plane * aB)
{
	return false;
}

bool InternalPhysics::TestPlaneSphereCollision(Sphere *aA, Plane *aB)
{
	// Computing the normal distance from the sphere center to the plane
	Vector3 vector1 = aA->GetNewPosition() - aB->GetPosition();
	Vector3 vector2 = aB->GetNormal();
	float distance = vector1*vector2;

	// If this distance is Less than the radius
	if( fabs(distance) <= aA->GetRadius() )
	{
		// Calling the IsInsidePLan method
		return IsInsidePlan( aA, aB, distance);
	}
	// No possible interaction
	return false;
}

void InternalPhysics::AddIntersection(Object* A, Object*B, Vector3 theNormal, Vector3 theContactPoint)
{
	bool AlreadyDone = false;

	// We go through the list of presaved intersections and check if this one has already been managed
	list<Intersection>::iterator it = mListIntersection.begin();
	while( it != mListIntersection.end() )
	{
		// Has it?
		if( (*it).mA == B && (*it).mB == A )
		{
			AlreadyDone=true;
			break;
		}
		++it;
	}
	// If it hasn't we add it
	if( AlreadyDone==false )
	{
		mListIntersection.push_back( Intersection(A,B,theNormal,theContactPoint) );
	}

}

void InternalPhysics::AddIntersection(Object* A, Object*B)
{
	bool  alreadyDone = false;

	// We go through the list of presaved intersections and check if this one has already been managed
	list<Intersection>::iterator it = mListIntersection.begin();
	while( it != mListIntersection.end() )
	{
		// Has it?
		if( (*it).mA == B && (*it).mB == A )
		{
			alreadyDone=true;
			break;
		}
		++it;
	}
	// If it hasn't we add it
	if( alreadyDone==false )
		mListIntersection.push_back( Intersection(A,B) );

}


void InternalPhysics::ManageSphereSphereCollision(Sphere* A, Sphere* B)
{
	// Local variable initialisation
	Vector3 VelocityA,VelocityB;


	// Getting masses
	double   AMass = A->GetMass();
	double   BMass = B->GetMass();


	// Getting the distance between the two spheres
	Vector3 centerDistanceVector = B->GetNewPosition() - A->GetNewPosition();
	float norme = centerDistanceVector.Norm();

	// Getting the collision unit vector
	centerDistanceVector.Normalize();


	// We are testing if this collision has already been managed

	// For A
	if(A->IsInCollision() == true)
	{
		VelocityA=A->GetCollisionVelocity();
	}
	else
	{
		VelocityA=A->GetNewVelocity();
	}


	//For B
	if(B->IsInCollision() == true)
	{
		VelocityB=B->GetCollisionVelocity();
	}
	else
	{
		VelocityB=B->GetNewVelocity();
	}



//Speed Collision managing

	// For A , pre-collision  speed
	Vector3 vAAfterx = (centerDistanceVector * VelocityA) * centerDistanceVector;
	Vector3 vAAftery = VelocityA - vAAfterx;

	// For B , pre-collision  speed
	Vector3 vBAfterx = (-centerDistanceVector * VelocityB) * (-centerDistanceVector);
	Vector3 vBAftery = VelocityB - vBAfterx;

	//Applying collision thorem
	Vector3 VAx = ( (vAAfterx*AMass) + (vBAfterx*BMass) - (vAAfterx-vBAfterx)*BMass )/(AMass+BMass);
	Vector3 VAy = vAAftery;
	Vector3 VBx = ( (vAAfterx*AMass) + (vBAfterx*BMass) - (vBAfterx-vAAfterx)*AMass )/(AMass+BMass);
	Vector3 VBy = vBAftery;



	Vector3 vAAfter = VAx+VAy;
	Vector3 vBAfter = VBx+VBy;

	// Reducing the speed by a factor 0.9, it simulates energy loss
	vAAfter= 0.9*vAAfter;
	vBAfter=0.9*vBAfter;


	// Adding a reaction force when the balls touches the ground

	// For A
	Vector3 verticalForce( A->GetConstantForces() );
	Vector3 reactionForce =  fabs(verticalForce.GetZ()/centerDistanceVector.GetZ())*centerDistanceVector;
	Vector3 applicationPoint(A->GetPosition());
	Force reaction(reactionForce,reactionForce);
	A->AddNewVariableForce( reaction );


	// For B
	verticalForce= B->GetConstantForces() ;
	reactionForce =  fabs(verticalForce.GetZ()/centerDistanceVector.GetZ())*centerDistanceVector;
	reaction.SetForce(reactionForce);
	B->AddNewVariableForce( reaction );


	// Changing brutally the speed, the accelerations and the positions and cancelling the collision

	//For A
	Vector3 NIL(0.0f,0.0f,0.0f);
	A->SetNewAcceleration( NIL );
	A->SetNewVelocity(vAAfter);
	A->SetNewPosition( A->GetPosition() );
	A->ResetIsInCollision();



	//For B
	B->SetNewAcceleration( NIL );
	B->SetNewVelocity(vBAfter);
	B->SetNewPosition( B->GetPosition() );
	B->ResetIsInCollision();


}


void InternalPhysics::ManagePlaneCubeCollision(Cube* A, Plane* B)
{

}

void InternalPhysics::Update()
{
	int objectNumber = 0;

	// Testing collisions after computing following positions
	list<Object*>::iterator anObject = mCollisionalObjects.begin();
	while( anObject != mCollisionalObjects.end() ) //Test collisions
	{
		// We don't test collisions for planes
		if( (*anObject)->GetType() != PLANE)
		{
			// If it's a moving shape, we test collisions
			TestCollision(&anObject,objectNumber);
		}
		++anObject;
		objectNumber++;

	}


	//Managing the collisions
	list<Intersection>::iterator anIntersection = mListIntersection.begin();
	while( anIntersection != mListIntersection.end() )
	{
		// Object getting
		Object* A,*B;
		A = (*anIntersection).mA;
		B = (*anIntersection).mB;

		// Type getting
		int typeA = A->GetType();
		int typeB = B->GetType();

		// Managing the sphere/sphere collision
		if(	typeA == SPHERE	&&	typeB == SPHERE )
		{
			ManageSphereSphereCollision	( (Sphere*) A, (Sphere*) B);
		}
		// Managing the sphere/plane collision
		if( typeA == SPHERE	&&	typeB == PLANE)
		{
			ManageSpherePlaneCollision( (Sphere*) A, (Plane *) B);
		}

		// Moving to the next one
		anIntersection++;
	}
	mListIntersection.clear();


	// Updating speeds and positions
	anObject = mCollisionalObjects.begin();
	while( anObject != mCollisionalObjects.end() )
	{
		// Only if not a plane
		if( (*anObject)->GetType() != PLANE )
		{

			(*anObject)->SetVelocity( (*anObject)->GetNewVelocity() );
			(*anObject)->SetPosition( (*anObject)->GetNewPosition() );

			// Adding a break force
			if( (*anObject)->GetType() == SPHERE )
			{
				Vector3 velocity = (*anObject)->GetVelocity();
				Sphere *sphere = (Sphere*)(*anObject);
				// Applying Stockes lay
				Vector3 airBreak = -6.0 * Inertia::Pi * Inertia::Nu * sphere->GetRadius() * velocity;
				Vector3 applicationPoint(sphere->GetPosition()+velocity.Normalize()*sphere->GetRadius());
				Force airBreak2(airBreak,applicationPoint);
				sphere->AddNewVariableForce(airBreak2);
			}


		}
		++anObject;
	}

}


void InternalPhysics::ManageSpherePlaneCollision(Sphere* aSphere, Plane * aPlan)
{

	//local variable declaring
	Vector3 PointIntersect;


	// Getting the distance between the plan and the sphere
	Vector3 vector1 = aSphere->GetPosition() - aPlan->GetPosition();
	Vector3 planNormal = aPlan->GetNormal();
	float distance = vector1*planNormal;

	// Getting the sphere velocity
	Vector3 sphereVelocity= aSphere->GetVelocity();
	Vector3 SphereVelocityNorm = sphereVelocity;
	SphereVelocityNorm.Normalize();


	// Testing if the sphere is comming from under or over the plan
	if( planNormal * sphereVelocity > 0 )
	{
		planNormal = - planNormal;
	}


	// Testing if the ball isn't just rolling on the plan
	if(fabs(sphereVelocity*planNormal)<0.0001)
	{
		// If it's not it's a bit more complicate, we need to find were it will be (not just a little below)
		// it's function of the speed
		PointIntersect = aSphere->GetPosition() - (sphereVelocity.Norm()*(aSphere->GetRadius()-fabs(distance))/fabs(sphereVelocity*planNormal))*SphereVelocityNorm - aSphere->GetRadius() * planNormal;
	}
	else
	{
		// If it's the case, the intersection point is on the sphere and the plan
		PointIntersect = aSphere->GetPosition() - aSphere->GetRadius() * planNormal;
	}

	// Testing if it had already a collision
	if(aSphere->IsInCollision() == true )
	{
		// If it's the case we use it's collisional velocity
		sphereVelocity = aSphere->GetCollisionVelocity();
	}
	else
	{
		// if it's not we use it's velocity
		sphereVelocity = aSphere->GetVelocity();
	}


	// Computing the velocity after collision
	Vector3 nextVelocity 	=  sphereVelocity + (fabs( sphereVelocity * planNormal ) * planNormal) *2 ;

	// Plan Vertical energy loss after collision
    float normalSpeed = fabs(nextVelocity*planNormal);

    // only if not nill
    if(fabs(normalSpeed)>0.001f)
    {
    	nextVelocity = nextVelocity +(normalSpeed*0.20)* (-planNormal);
    }

    /*
    // Plan horizontal break after collision
    Vector3 horizontal = nextVelocity - (nextVelocity*planNormal)* (-planNormal);
    horizontal.Normalize();
	float horizontalSpeed = fabs((nextVelocity - (nextVelocity*planNormal)* (-planNormal)).Norm());

	// only if not nill
	if(fabs(horizontalSpeed)>0.001f)
	{
		nextVelocity = nextVelocity -(horizontalSpeed*0.30)* (horizontal);
	}
*/

		Vector3 verticalForce( 0.0f, 0.0f , aSphere->GetConstantForces().GetZ());

		Force reaction(verticalForce,PointIntersect);
		aSphere->AddNewVariableForce( reaction );

		// Changing brutally the speed, the accelerations and the positions and cancelling the collision
		Vector3 NIL(0.0f,0.0f,0.0f);
		aSphere->SetNewAcceleration( NIL );
		aSphere->SetNewVelocity(nextVelocity);
 		Vector3 newPos=aSphere->GetPosition() + planNormal*0.01;
		aSphere->SetNewPosition( newPos );
		aSphere->ResetIsInCollision();

}



bool InternalPhysics::IsInsidePlan( Object* aA, Plane * aPlan, float aDist )
{
	// Creating the local variables
	Vector3		planNormal, planProjection;
	Vector3		CotePlan1,CotePlan2,CotePlan3,CotePlan4;
	int			Sens, SensCourant;

	// Getting normal
	planNormal	= aPlan->GetNormal();

	//Locating the object's projection on the plan
	planProjection	= aA->GetNewPosition() - aDist * planNormal;

	// Calcul des cotes du _pPlan
	CotePlan1 = aPlan->GetPoint2() - aPlan->GetPoint1();
	CotePlan2 = aPlan->GetPoint3() - aPlan->GetPoint2();
	CotePlan3 = aPlan->GetPoint4() - aPlan->GetPoint3();
	CotePlan4 = aPlan->GetPoint1() - aPlan->GetPoint4();

	// On regarde si l'objet est à gauche ou a droite
	Sens = ( planProjection - aPlan->GetPoint1() ) * CotePlan1;

	if( Sens != 0 )
	{
		int temp;
		if (Sens>0)
		{
			temp=Sens;
		}
		else
		{
			temp=-Sens;

		}
		Sens = Sens / temp;
	}
	SensCourant = ( planProjection - aPlan->GetPoint2() ) * CotePlan2;

	if( SensCourant != 0 )
	{
		int temp;
		if (SensCourant>0)
		{
			temp=SensCourant;
		}
		else
		{
			temp=-SensCourant;

		}
		SensCourant = SensCourant / temp;
	}

	if( SensCourant == Sens )
	{
		SensCourant = ( planProjection - aPlan->GetPoint3() ) * CotePlan3;

		if( SensCourant != 0 )
		{
			int temp;
			if (SensCourant>0)
			{
				temp=SensCourant;
			}
			else
			{
				temp=-SensCourant;

			}
			SensCourant = SensCourant / temp;
		}
		if( SensCourant == Sens )
		{
			SensCourant = (planProjection - aPlan->GetPoint4() ) * CotePlan4;

			if( SensCourant != 0 )
			{
				int temp;
				if (SensCourant>0)
				{
					temp=SensCourant;
				}
				else
				{
					temp=-SensCourant;

				}
				SensCourant = SensCourant / temp;
			}

			if( SensCourant == Sens )
					return true;

		}
	}

	return false;
}
