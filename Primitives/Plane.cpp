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


#include "Plane.h"


using namespace Inertia;
Plane::Plane(Vector3 & aPoint1, Vector3 & aPoint2, Vector3  & aPoint3)
{
	mObjectType = PLANE;

	mPoint1 = aPoint1;
	mPoint2 = aPoint2;
	mPoint3 = aPoint3;
	mPoint4 = 	(aPoint1 + aPoint3)-aPoint2;

	mPosition	=	aPoint1;

	mNormal = (aPoint2-aPoint1).Cross(aPoint3-aPoint1);
	mNormal = mNormal.Normalize();

}
Vector3 Plane::GetNormal()
{
	return mNormal;
}

Vector3 Plane::GetPoint1()
{
	return mPoint1;
}
Vector3 Plane::GetPoint3()
{
	return mPoint3;
}
Vector3 Plane::GetPoint4()
{
	return mPoint4;
}


Vector3 Plane::GetPoint2()
{
	return mPoint2;
}
