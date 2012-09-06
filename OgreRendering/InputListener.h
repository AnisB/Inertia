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



#ifndef INPUTLISTENER_H_
#define INPUTLISTENER_H_


//----------------------------------------------------Includes OIS
#include <OIS/OIS.h>
#include <map>
//----------------------------------------------------Includes personnels
#include "Renderer.h"
#include "OGRE/Ogre.h"
#include "CameraMan.h"

class Renderer;

class InputListener :public Ogre::FrameListener, public OIS::KeyListener, OIS::MouseListener
{
public:
	//----------------------------------------------------Constructeur et destructeur
	 InputListener(Ogre::RenderWindow* aWindow, Renderer * theRenderer,Ogre::Camera * aCamera);
     ~InputListener();

 	//----------------------------------------------------Rendu
		virtual bool frameStarted(const Ogre::FrameEvent & evt);
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& 	);
	//----------------------------------------------------Gestion des entree
	    bool keyPressed(const OIS::KeyEvent &e);
	    bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		bool keyReleased(const OIS::KeyEvent &e);
		bool mouseMoved(const OIS::MouseEvent &e);
		virtual bool frameEnded (const Ogre::FrameEvent &evt);
	    void windowResized(Ogre::RenderWindow* rw);


	private:
	      Renderer * mRenderer;
		  Ogre::RenderWindow * mWindow;
	      bool mShutdown;
		  OIS::Keyboard * mKeyboard;
		  OIS::Mouse * mMouse;
		  OIS::InputManager * mInputManager;
		  Ogre::Camera * mCamera;
		  CameraMan * mCameraMan;



};

#endif /* INPUTLISTENER_H_ */
