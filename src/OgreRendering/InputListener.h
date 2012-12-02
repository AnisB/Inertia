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



#if defined(InputListener_RECURSES)
#error Recursive header files inclusion detected in InputListener.h
#else // defined(InputListener_RECURSES)
/** Prevents recursive inclusion of headers. */
#define InputListener_RECURSES

#if !defined InputListener_h
/** Prevents repeated inclusion of headers. */
#define InputListener_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
//----------------------------------------------------Includes OIS
#include <OIS/OIS.h>
#include <OGRE/Ogre.h>
#include "CameraMan.h"
#include "Singleton.h"			

//////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// class InputListener
    /**
    * Description of class 'InputListener' <p>
    * \brief Aim:  Manage the inputs for the Ogre3D viewer
    */

        class Renderer;

        class InputListener : public Singleton<InputListener> ,
			      public Ogre::FrameListener,
			      public OIS::KeyListener, OIS::MouseListener ,
			      public Ogre::WindowEventListener
          {

              // ----------------------- Standard services ------------------------------

            public:

              /**
               * Destructor.
               */
              ~InputListener();

              /**
               * Constructor.
               */
              InputListener ( Ogre::RenderWindow * aWindow,
                              Renderer * aViewer,
                              Ogre::Camera * aCamera,
                              Ogre::SceneManager * aSceneManager );



              // ----------------------- Interface --------------------------------------

            public:


              /**
               * Method that initiate the inputManager (First frame)
               */
              virtual bool frameStarted ( const Ogre::FrameEvent & evt );


              /**
               * the rendering method 
               */
              virtual bool frameRenderingQueued ( const Ogre::FrameEvent& );

              /**
                * The last frame
                */
              virtual bool frameEnded ( const Ogre::FrameEvent &evt );


              /**
               * Handles a key press
               */
              bool keyPressed ( const OIS::KeyEvent &e );


              /**
               * Handles a mouse press
               */
              bool mousePressed ( const OIS::MouseEvent &e, OIS::MouseButtonID id );


              /**
               * Handles a mouse release
               */
              bool mouseReleased ( const OIS::MouseEvent &e, OIS::MouseButtonID id );


              /**
               * Handles a key release
               */
              bool keyReleased ( const OIS::KeyEvent &e );


              /**
               * Handles a mouse move
               */
              bool mouseMoved ( const OIS::MouseEvent &e );


              /**
               * Handles a window resize
               */
	      virtual void windowResized(Ogre::RenderWindow* rw);
              /**
               * Handles a window close
               */
              virtual void windowClosed(Ogre::RenderWindow* rw);
	     /**
               * makes the render loop stop
               */
              void stopRendering ( );
	      
	      
              /**
               * makes the render loop starts
               */
              void startRendering ( );
	      
	
	      /**
	       *  Returns a pointer on the cameraman
	       * 
	       */
	        CameraMan * getCameraMan() 
		{
		  return myCameraMan;
		}


	      /**
	       *  Returns a pointer on the keyboard
	       * 
	       */
	        OIS::Keyboard * getKeyBoard() 
		{
		  return myKeyboard;
		}


	      /**
	       *  Returns a pointer on the mouse
	       * 
	       */
	        OIS::Mouse * getMouse() 
		{
		  return myMouse;
		}

	       /**
	       *  Returns a pointer on the mouse
	       * 
	       */
	        Ogre::Timer * getTimer() 
		{
		  return myTimer;
		}

	 
                bool viewerIsRunning()
		{
		     return !myShutdown;
		}

	      
	                    // ----------------------- Private members --------------------------------------
            private:
     	      
	      /**
              * The viewer
              */	      
              Renderer * myViewer;
	      
	      
	     /**
              * The window
              */
              Ogre::RenderWindow * myWindow;
	      
	      
	     /**
              * Flag that manages the rendering
              */  
              bool myShutdown;

	      /**
              * The keyboard
              */
              OIS::Keyboard * myKeyboard;
	      
	      
	      /**
              * The mouse
              */	      
              OIS::Mouse * myMouse;
              	     
              	    
	      
	      /**
              * The OIS input listenner
              */		      
              OIS::InputManager * myInputManager;
	      
	      
	     /**
              * The Camera Object
              */		   
              Ogre::Camera * myCamera;
	      
	      /**
              * The CameraMan
              */		   
              CameraMan * myCameraMan;
	      
	      
	      /**
              *  Free 3D moving flag
              */	      
              bool myIsInShiftMode;
	      
	      
	      /**
              * The ogre scene manager
              */	
              Ogre::SceneManager * mySceneMgr;
	      
	      int myMouseX;
	      int myMouseY;
              double myTime;

	      /**
	       * The rendering timer
               */
               Ogre::Timer * myTimer;


          };
      

#include "Renderer.h"

  

// //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined InputListener_h

#undef InputListener_RECURSES
#endif // else defined(InputListener_RECURSES)
            
