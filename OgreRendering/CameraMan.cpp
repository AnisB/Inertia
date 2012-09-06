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




//////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include "CameraMan.h"
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION of inline methods.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// ----------------------- Standard services ------------------------------



/**
 * Constructor
 */
CameraMan::CameraMan (Ogre::SceneNode * aNode, Ogre::Camera * aCamera, int aSpeed , int aRotationSpeed ) : myCamera ( aCamera )
{

  // Initiate moving flags
  myIsGoingFoward = false;
  myIsGoingBackward = false;
  myIsGoingLeftward = false;
  myIsGoingRightward = false;

  // initate moving parameters
  mySpeed = aSpeed;
  myRotationSpeed = aRotationSpeed;
  myTempMouseMove = Ogre::Vector3::ZERO;
  myIsOnShiftMode = false;

  // Initial Camera position and orientation
  myCameraNode=aNode;
  myCamera->setFarClipDistance(5000);
  myCamera->setNearClipDistance(1);

  myCameraNode->attachObject(myCamera);
  myCameraNode->setPosition(Ogre::Vector3(00.0, -500.0, 50.0 ));
  myX=0;
  myY=0;
  myIsTurning=false;

  myCameraNode->lookAt ( Ogre::Vector3 ( 0, 0, 0 ) ,Ogre::Node::TS_WORLD);
//  myCameraNode->roll(Ogre::Radian(Ogre::Math::PI),Ogre::Node::TS_LOCAL);

}


/**
* Destructor.
*/
CameraMan::~CameraMan( )
{
  //Nothing to do
}



/**
  * Public method that handles the user key press
*/
bool CameraMan::handleKeyPress ( const OIS::KeyEvent & evt )
{
  switch ( evt.key )
    {

      case OIS::KC_Z :
        startGoingFoward();
        break;

      case OIS::KC_S :
        startGoingBackward();
        break;

      case OIS::KC_Q :
        startGoingLeftward();
        break;

      case OIS::KC_D :
        startGoingRightward();
        break;

      default :
        break;
    }

  return false;
}



/**
  * Public method that handles the user key Release
*/
bool CameraMan::handleKeyRelease ( const OIS::KeyEvent & evt )
{
  switch ( evt.key )
    {

      case OIS::KC_CAPITAL :
        myIsOnShiftMode = !myIsOnShiftMode;
        break;

      case OIS::KC_Z :
        stopGoingFoward();
        break;

      case OIS::KC_S :
        stopGoingBackward();
        break;

      case OIS::KC_Q :
        stopGoingLeftward();
        break;

      case OIS::KC_D :
        stopGoingRightward();
        break;

      default :
        break;
    }

  return false;
}


/**
  * Public method that handles the user mouse move
*/
bool CameraMan::handleMouseMove ( const OIS::MouseEvent & evt )
{
  myTempMouseMove = Ogre::Vector3 ( -0.05f * evt.state.X.rel, -0.05f * evt.state.Y.rel, -evt.state.Z.rel );
  return false;
}

/**
  *  Public method that handles the user mouse click
*/
bool CameraMan::handleMouseClick ( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{

  return false;
}

/**
  *  Public method that handles the user mouse release
*/
bool CameraMan::handleMouseRelease ( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{

  return false;
}



/**
  *  Public method that acts on the camera geometric attributes
*/
void CameraMan::render ( double timeSinceLastFrame )
{
  double step = ( double )timeSinceLastFrame * mySpeed;



      if ( myIsGoingFoward )
        {
          Ogre::Vector3 NewPosition ( myCameraNode->getPosition() );
          NewPosition -= ( myCameraNode->getOrientation().zAxis() * step*100 );
          myCameraNode->setPosition ( NewPosition );
        }


      if ( myIsGoingBackward )
        {
          Ogre::Vector3 NewPosition ( myCameraNode->getPosition() );
          NewPosition += ( myCameraNode->getOrientation().zAxis() * step *100 );
          myCameraNode->setPosition ( NewPosition );
        }

      if ( myIsGoingLeftward )
        {
          Ogre::Vector3 NewPosition ( myCameraNode->getPosition() );
          NewPosition -= ( myCameraNode->getOrientation().xAxis() * step *100 );
          myCameraNode->setPosition ( NewPosition );
        }

      if ( myIsGoingRightward )
        {
          Ogre::Vector3 NewPosition ( myCameraNode->getPosition() );
          NewPosition += (myCameraNode->getOrientation().xAxis() * step*100);
          myCameraNode->setPosition ( NewPosition );
        }

      if ( ( myTempMouseMove.x != 0.f ) || ( myTempMouseMove.y != 0.f ) || ( myTempMouseMove.z != 0.f ) )
        {

          if ( myTempMouseMove.x != 0 )
            {
              myCameraNode->yaw ( Ogre::Degree ( myTempMouseMove.x ) );
            }

          if ( myTempMouseMove.y != 0 )
            {
              this->myCameraNode->pitch ( Ogre::Degree ( myTempMouseMove.y ) );
            }

          myTempMouseMove = Ogre::Vector3::ZERO;

        }

      if ( myTempMouseMove.z != 0 )
        {
            zoom(myTempMouseMove.z);
        }

}

/**
  *  Public method that makes the camera turns around the centralNode
  *
  */
void CameraMan::turnCamera ( int x, int y )
{
  if((x!=0) || (y !=0) )
  {
    myX=x;
    myY=y;
    myIsTurning=true;
  }
}


/**
  *  Public method that makes the camera translate
  *
  */
void CameraMan::translateCamera ( double x, double y )
{

  myCameraNode->setPosition ( myCameraNode->_getDerivedPosition() - ( myCameraNode->getOrientation().yAxis() * ( -y*3 ) + myCameraNode->getOrientation().xAxis() *x*3 ) );
  mySceneCenter = ( mySceneCenter - ( myCameraNode->getOrientation().yAxis() * ( -y * 3 ) + myCameraNode->getOrientation().xAxis() * x * 3 ) );
  myCameraNode->lookAt ( mySceneCenter,Ogre::Node::TS_WORLD  );

}

/**
*  Public method that updates the scene center
*
*/
void CameraMan::setSceneCenter ( Ogre::Vector3 aSceneCenter )
{
  mySceneCenter = aSceneCenter;
}


/**
*  Public method that translates the cameraMan by aVector
*
*/
void CameraMan::moveCameraman ( Ogre::Vector3 aVector )
{
//   myCameraNode->setPosition(myCameraNode->_getDerivedPosition()+(mySceneCenter-aVector));
}


/**
*  Public method that returns the node
*
*/
Ogre::SceneNode * CameraMan::getSceneNode ( )
{
  return myCameraNode;
}

/**
*  Public method that permits to zoom
*/
void CameraMan::zoom(int z)
{
      if ( z != 0 )
        {
          this->myCameraNode->translate ( myCameraNode->getOrientation().zAxis() *z*10 );
	 }
}
/**
  *  Public method that sets the initial position
  */
void CameraMan::setInitialPosition(Ogre::Vector3 & newPos)
{
  myInitialPosition =newPos;
//  myCameraNode->lookAt(mySceneCenter,Ogre::Node::TS_WORLD);
//  mySavedOrientation = myCameraNode->getOrientation();
}

/**
  *  Public method that resets the cameraman orientation and position
  */
void CameraMan::reset()
{
  myCameraNode->setOrientation(mySavedOrientation);
  myCameraNode->setPosition(myInitialPosition);
  myCameraNode->setPosition(myCameraNode->_getDerivedPosition());
  myCameraNode->lookAt(mySceneCenter, Ogre::Node::TS_WORLD);
}
///////////////////////////////////////////////////////////////////////////////
// Interface - public :

///////////////////////////////////////////////////////////////////////////////
// Implementation of inline functimyCameraons //



// //
///////////////////////////////////////////////////////////////////////////////
