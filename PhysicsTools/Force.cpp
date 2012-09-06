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


#include "Force.h"
using namespace Inertia;

Force::Force ()
{

}
Force::Force ( Vector3 newForce, Vector3 newApplicationPoint  )
{
	mForce=newForce;
	mApplicationPoint =newApplicationPoint;

}

Force::Force ( Vector3 newForce )
{
	mForce=newForce;


}

Force::~Force ( )
{
	// TODO Auto-generated destructor stub
}


void Force::SetForce(Vector3 newForce)
{
	mForce=newForce;
}
void Force::SetApplicationPoint(Vector3 newApplicationPoint)
{
	mApplicationPoint=newApplicationPoint;
}

Vector3 Force::GetForce()
{
	return mForce;
}
Vector3 Force::GetApplicationPoint()
{
	return mApplicationPoint;
}
