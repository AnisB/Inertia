
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



#include "InputListener.h"
#include <iostream>




InputListener::InputListener(Ogre::RenderWindow * aWindow, Renderer * aRenderer,Ogre::Camera * aCamera):
mWindow(aWindow),mRenderer(aRenderer)

{
				mCamera=aCamera;
				OIS::ParamList pl;
				unsigned int windowHnd = 0;
				std::stringstream windowHndStr;
				aWindow->getCustomAttribute("WINDOW", &windowHnd);
				windowHndStr << windowHnd;
				pl.insert(std::make_pair("WINDOW", windowHndStr.str()));
				mInputManager = OIS::InputManager::createInputSystem(pl);
				mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
				mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

				mKeyboard->setEventCallback(this);
				mMouse->setEventCallback(this);

				mShutdown= false;

				mCameraMan = new CameraMan(mRenderer->getSceneManager()->createSceneNode(),mCamera);
				}

				//Adjust mouse clipping area



	     InputListener::~InputListener()
			{
				mInputManager->destroyInputObject(mKeyboard);
				mInputManager->destroyInputObject(mMouse);

				OIS::InputManager::destroyInputSystem(mInputManager);
			}


bool InputListener::frameRenderingQueued(const Ogre::FrameEvent & evt)
		{

			if(mMouse)
				mMouse->capture();
			if(mKeyboard)
				mKeyboard->capture();
			if (mWindow->isClosed() || mShutdown)
					return false;

			mRenderer->Update(evt.timeSinceLastFrame);
			mCameraMan->render(evt.timeSinceLastFrame);
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
			mShutdown = true;
			return false;
			break;
		case OIS::KC_SPACE:
			return true;
				break;
	}
	mCameraMan->handleKeyPress(evt);
	return true;

}


bool InputListener::frameEnded (const Ogre::FrameEvent &evt)
{
	return true;
}



bool InputListener::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	mCameraMan->handleMouseClick(arg,id);
	return true;

}

bool InputListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	mCameraMan->handleMouseRelease(e,id);
	return true;
}

bool InputListener::keyReleased(const OIS::KeyEvent &e)
{
	mCameraMan->handleKeyRelease(e);
	return true;
}


bool InputListener::mouseMoved(const OIS::MouseEvent &e)
{
	mCameraMan->handleMouseMove(e);
	return true;
}
