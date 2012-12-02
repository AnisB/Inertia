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

/**
 * @file MyApplication.h
 * @author Anis Benyoub (\c anis.benyoub@insa-lyon.fr )
 * Liris CNRS
 */

#if defined(MyApplication_RECURSES)
#error Recursive header files inclusion detected in MyApplication.h
#else // defined(MyApplication_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MyApplication_RECURSES

#if !defined MyApplication_h
/** Prevents repeated inclusion of headers. */
#define MyApplication_h



#include "Ogre/OgrePlatform.h"

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>

int MyApplicationMain(int argc, const char **argv);

@interface MyApplication : NSApplication
{
	bool shouldKeepRunning;
}

- (void)terminate:(id)sender;

@end
#endif

#include "MyApplication.ih"
#endif /* MyApplication_H_ */

#undef MyApplication_RECURSES
#endif // else defined(MyApplication_RECURSES)
