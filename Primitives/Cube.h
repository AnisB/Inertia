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

#ifndef __CUBE_H__
#define __CUBE_H__

#include "Object.h"
#include "../MathTools/Vector4.h"
namespace Inertia
{
const double DEFAULTCUBEMASS = 10.0;
class Cube : public Object
{

public:

	// -------------------------------------------------------------- Constructors

	Cube(double dimension);
	Cube(double dimension, Vector3  & aCenterPosition);
	Cube(int aMass, double dimension, Vector3 & aPosition);
	Cube(int aMass,double dimension, Vector3 & aPosition, Vector4 & anOrientation);


	// -------------------------------------------------------------- Destructor
	virtual ~Cube();


	// --------------------------------------------------------------- Accessors
	double GetDimension();

private:

	// --------------------------------------------------------------- Attributs
	double 		mDimension;
	Inertia::Vector4 mOrientation;

};
}
#endif /* SPHERE_H_ */
