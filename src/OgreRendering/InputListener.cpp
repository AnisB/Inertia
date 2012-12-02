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


///////////////////////////////////////////////////////////////////////////////
#include "InputListener.h"
#include <iostream>
#include "time.h"
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// class InputListener
///////////////////////////////////////////////////////////////////////////////

  template<> InputListener* Singleton<InputListener>::mySingleton = 0;


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :



/**
 * Constructor.
 */
InputListener::InputListener ( Ogre::RenderWindow * aWindow, Renderer * aViewer, Ogre::Camera * aCamera, Ogre::SceneManager * aSceneManager ) :
  myWindow ( aWindow ), myViewer ( aViewer )

{

  // Camera Intiate
  myCamera = aCamera;
  Ogre::SceneNode * aNode=aSceneManager->getRootSceneNode()->createChildSceneNode();
   myCameraMan = new CameraMan (aNode, myCamera );

  size_t windowHnd = 0;
  std::ostringstream windowHndStr;
    
  myWindow->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;

  OIS::ParamList pl;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  myInputManager = OIS::InputManager::createInputSystem( pl );

  //Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
  myKeyboard = static_cast<OIS::Keyboard*>(myInputManager->createInputObject( OIS::OISKeyboard, true ));
  myMouse = static_cast<OIS::Mouse*>(myInputManager->createInputObject( OIS::OISMouse, true ));

  myMouse->setEventCallback(this);
  myKeyboard->setEventCallback(this);
  // End flag initate
  myShutdown = false;


    
  const OIS::MouseState &ms = myMouse->getMouseState();
  ms.width = myWindow->getWidth();
  ms.height = myWindow->getHeight();
 


  // Other initating
  myIsInShiftMode = false;
  mySceneMgr = aSceneManager;

  //Register as a Window listener
  Ogre::WindowEventUtilities::addWindowEventListener(myWindow, this);


  // Initiating timer
  myTimer = OGRE_NEW Ogre::Timer();
  myTimer->reset();

  myWindow->setActive(true);
  myTime =-1;
  myWindow->setDeactivateOnFocusChange(false);



}



/**
 * Destructor.
 */
InputListener::~InputListener()
{
  myInputManager->destroyInputObject ( myKeyboard );
  myInputManager->destroyInputObject ( myMouse );
  delete myCameraMan;
  OIS::InputManager::destroyInputSystem ( myInputManager );
}



bool InputListener::frameRenderingQueued(const Ogre::FrameEvent & evt)
		{

			if(myMouse)
				myMouse->capture();
			if(myKeyboard)
				myKeyboard->capture();
			if (myWindow->isClosed() || myShutdown)
					return false;

			myViewer->Update(evt.timeSinceLastFrame);
			myCameraMan->render(evt.timeSinceLastFrame);
			return true;
		}

bool InputListener::frameStarted(const Ogre::FrameEvent & evt)
{
	return true;
}

bool InputListener::keyPressed(const OIS::KeyEvent & evt)
{
	switch (evt.key)
	{

		case OIS::KC_ESCAPE:
			myShutdown = true;
			return false;
			break;
		case OIS::KC_SPACE:
			return true;
				break;
	}
	myCameraMan->handleKeyPress(evt);
	return true;

}


bool InputListener::frameEnded (const Ogre::FrameEvent &evt)
{
	return true;
}



bool InputListener::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	myCameraMan->handleMouseClick(arg,id);
	return true;

}

bool InputListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	myCameraMan->handleMouseRelease(e,id);
	return true;
}

bool InputListener::keyReleased(const OIS::KeyEvent &e)
{
	myCameraMan->handleKeyRelease(e);
	return true;
}


bool InputListener::mouseMoved(const OIS::MouseEvent &e)
{
	myCameraMan->handleMouseMove(e);
	return true;
}/**
 * makes the render loop stop
 */
void InputListener::stopRendering ( )
{
  myShutdown = true;
}




/**
 * makes the render loop starts
 */
void InputListener::startRendering ( )
{
  myShutdown = false;
}


/**
 * Handles a window resize
 */
 void InputListener::windowResized(Ogre::RenderWindow* rw)
{

}
/**
 * Handles a window close
 */
void InputListener::windowClosed(Ogre::RenderWindow* rw)
{
  myShutdown=true;

}
