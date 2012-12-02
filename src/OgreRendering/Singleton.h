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


#pragma once

#if defined(Singleton_RECURSES)
#error Recursive header files inclusion detected in Singleton.h
#else // defined(Singleton_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Singleton_RECURSES

#if !defined Singleton_h
/** Prevents repeated inclusion of headers. */
#define Singleton_h

//////////////////////////////////////////////////////////////////////////////

// Includes
#include <assert.h>

//////////////////////////////////////////////////////////////////////////////

	/**
	 * Description of struct 'Singleton' <p>
	 * \brief Ogre Factory for Singleton:
 	*/
    template <typename T> class Singleton
    {    


    public:
          // ----------------------- Standard services ------------------------------


          /**
          * Constructor 
          */
        Singleton( void )
        {
            assert( !mySingleton );
	    mySingleton = static_cast< T* >( this );
        }
	  /**
	  *  Destructor 
	  */
        ~Singleton( void )   
        {  
		assert( mySingleton );  
		mySingleton = 0;  
	}


	/**
	 * This function returns a reference on the unique object
	 */
        static T& getSingleton( void )
		
	{
		assert( mySingleton );  
		return ( *mySingleton );
	 }

	/**
	 * This function returns a pointer on the unique object
	 */
        static T* getSingletonPtr( void )		
	{
		 return mySingleton; 
	}

	protected:
          // ------------------------- Protected Datas ------------------------------
        static T* mySingleton;


	private:
          // ------------------------- Hidden services ------------------------------
          /**
          * Copy constructor.
          * @param other the object to clone.
          * Forbidden by default.
          */
	  Singleton(const Singleton<T> & other);

          /**
          * Copy constructor.
          * @param other the object to clone.
          * Forbidden by default.
          */
	Singleton& operator=(const Singleton<T> & other);
    };



///////////////////////////////////////////////////////////////////////////////


// //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Singleton_h
#undef Singleton_RECURSES
#endif // else defined(Singleton_RECURSES)




