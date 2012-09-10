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

#ifndef INTERNALPHYSICS_H_
#define INTERNALPHYSICS_H_


#include <list>
#include "../Primitives/Sphere.h"
#include "../Primitives/Plane.h"
#include "../Primitives/Cube.h"

namespace Inertia
{

struct Intersection
{
	// Constructor
	Intersection( Object* aA, Object* aB)
	{
		mA = aA;
		mB = aB;
	}
	Intersection( Object* aA, Object* aB, Vector3 aNormal,Vector3 aContactPoint)
	{
		mA = aA; mB = aB;

		mNormal=aNormal;
		mContactPoint=aContactPoint;
	}

	// Attributes
	Object* mA;
	Object* mB;
	Vector3 mNormal;
	Vector3 mContactPoint;
};



class InternalPhysics
{
	public:

	// Constructor
		InternalPhysics ( );

	// Destructor
		virtual ~InternalPhysics ( );


	// Rendering methods

		// On a different thread
		void StartRendering();
		void StopRendering();
		void SetSimulationStep(double newStep);
		void Render();

		// On the main thread
		void Step(double aStep);

	// Adding physicial objects
		void addNewCollisionalObject(Object * newObject);
		void removeCollisionalObject (Object * newObject);

	protected:


	// Collision test
		void TestCollision( std::list<Object*>::iterator *theObject, int aNumeroObjet );
		bool TestSphereSphereCollision(Sphere * A,Sphere * B);
		bool TestPlaneSphereCollision(Sphere *A, Plane  *B);
		bool TestPlaneCubeCollision(Cube *A, Plane  *B);

	// Collision manage
		void ManageSphereSphereCollision(Sphere* A, Sphere* B);
		void ManageSpherePlaneCollision(Sphere* A, Plane * B);
		void ManagePlaneCubeCollision(Cube* A, Plane * B);

		void ApplyForces(double aStep);


		bool IsInsidePlan( Object* A, Plane* aPlan, float aDist );
		void AddIntersection(Object* A, Object*B, Vector3 theNormal, Vector3 theContactPoint);
		void AddIntersection(Object* A, Object*B);


		void Update();

	protected:
		std::list<Object*> mCollisionalObjects;
		double mSimulationStep;
		double mStep;
		bool mIsRendering;
		std::list<Intersection> mListIntersection;

};
}
#endif /* INTERNALPHYSICS_H_ */
