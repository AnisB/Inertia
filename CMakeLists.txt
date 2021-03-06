
cmake_minimum_required(VERSION 2.6)

macro(prepare_binary PATH FILE_NAME)
	message (STATUS ${PATH})
    set(PATH ${CMAKE_BINARY_DIR})
    set( FILE ${FILE_NAME})
    file(MAKE_DIRECTORY ${PATH}/${FILE_NAME}.app)
    file(MAKE_DIRECTORY ${PATH}/${FILE_NAME}.app/Contents)
    file(MAKE_DIRECTORY ${PATH}/${FILE_NAME}.app/Contents/MacOS)
    file(MAKE_DIRECTORY ${PATH}/${FILE_NAME}.app/Contents/Frameworks)
    execute_process( COMMAND ${CMAKE_COMMAND}  -E create_symlink @OGRE_HOME@/lib/release/Ogre.framework/ ${PATH}/${FILE_NAME}.app/Contents/Frameworks/Ogre.framework )
    configure_file(${CMAKE_SOURCE_DIR}/CMake/Resources/info.plist.in
      ${PATH}/${FILE_NAME}.app/Contents/info.plist)
    set(EXECUTABLE_OUTPUT_PATH  ${PATH}${FILE_NAME}.app/Contents/MacOS )
endmacro(prepare_binary)


set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")


#Locating ogre Linux
  if(UNIX AND NOT APPLE)

    if(NOT DEFINED OGRE_PLUGINS)
      if(EXISTS "/usr/local/lib/OGRE/") #Ogre built from source (default install path)
        set(OGRE_PLUGINS "/usr/local/lib/OGRE/")
      elseif(EXISTS "/usr/lib/OGRE/") #Old ubuntu install
        set(OGRE_PLUGINS "/usr/lib/OGRE/")
      elseif (EXISTS "/usr/lib/i386-linux-gnu/OGRE/") #Ubuntu12.04-32bits-default
	message(STATUS "Found plugins")
        set(OGRE_PLUGINS "/usr/lib/i386-linux-gnu/OGRE/")
      elseif (EXISTS "/usr/lib/i386-linux-gnu/OGRE-1.7.4/") #Ubuntu12.04-32bits-default
	message(STATUS "Found plugins")
        set(OGRE_PLUGINS "/usr/lib/i386-linux-gnu/OGRE-1.7.4/")
      elseif (EXISTS "/usr/lib/x86_64-linux-gnu/OGRE-1.7.4/") #Ubuntu12.04-64bits-default
	message(STATUS "Found plugins")
        set(OGRE_PLUGINS  "/usr/lib/x86_64-linux-gnu/OGRE-1.7.4/")
      else()
        message(SEND_ERROR "Unable to find Ogre plugins, please set OGRE_PLUGINS variable")
      endif(EXISTS "/usr/local/lib/OGRE/")
    endif()

    if(EXISTS "/usr/local/lib/OGRE/cmake")
      set(CMAKE_MODULE_PATH "/usr/local/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
    elseif(EXISTS "/usr/share/OGRE/cmake")
      set(CMAKE_MODULE_PATH "/usr/share/OGRE/cmake/modules;${CMAKE_MODULE_PATH}")
    else ()
      message(SEND_ERROR "Failed to find module path, please set OGRE_DIR variable to the folder containing FindOgre.cmake")
    endif(EXISTS "/usr/local/lib/OGRE/cmake")
    
  endif(UNIX AND NOT APPLE)

#Locating ogre mac
if(APPLE)
    FIND_LIBRARY(CARBON_LIBRARY Carbon)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(IOKIT_LIBRARY IOKit )
    FIND_LIBRARY(FOUNDATION_LIBRARY Foundation )
    MARK_AS_ADVANCED (CARBON_LIBRARY COCOA_LIBRARY)
    SET(EXTRA_LIBS ${CARBON_LIBRARY} ${COCOA_LIBRARY}  ${IOKIT_LIBRARY} ${FOUNDATION_LIBRARY})

    set( OGRE_HOME $ENV{OGRE_HOME})
    if(NOT DEFINED OGRE_HOME)
      message("The variable OGRE_HOME is unset, please set it, this cmake lists has very low chances to compile")
      set(CMAKE_MODULE_PATH "${OGRE_DIR}/cmake/;${CMAKE_MODULE_PATH}")
      set(OGRE_PLUGINS "${OGRE_DIR}/lib/")
    else()
      set(OGRE_HOME "$ENV{OGRE_HOME}")
      set(OGRE_DIR OGRE_HOME)
      set(CMAKE_MODULE_PATH "${OGRE_HOME}/cmake/;${CMAKE_MODULE_PATH}")
      set(OGRE_PLUGINS "${OGRE_HOME}/lib/")
    endif()
    set(OGRE_DIR "${OGRE_HOME}" )
    ADD_DEFINITIONS("-x objective-c++")
  endif(APPLE)

set(PATH ${CMAKE_SOURCE_DIR}/CMake/Resources)
configure_file(${CMAKE_SOURCE_DIR}/src/OgreRendering/Renderer.h.in  ${CMAKE_SOURCE_DIR}/src/OgreRendering/Renderer.h )


  find_package(OGRE REQUIRED)
  if(OGRE_FOUND)
    find_package(OIS REQUIRED)
    message(STATUS  "libOgre found. ")
    set(Includes ${Includes}${CMAKE_SOURCE_DIR}/src/ ${Include} ${OGRE_INCLUDE_DIR} ${OIS_INCLUDE_DIR})	

    if(NOT APPLE)
      SET(Dependencies ${Dependencies} ${OGRE_LIBRARIES} ${OIS_LIBRARIES}  )
    else()
      SET(Dependencies ${Dependencies}  ${OGRE_LIBRARY_REL} ${OIS_LIBRARIES} ${EXTRA_LIBS})
    endif()
  else ( OGRE_FOUND )
    message(FATAL_ERROR  "Ogre not found.  Check the cmake variables associated to this package or disable it." )
  endif ( OGRE_FOUND )


message(STATUS "Looking for boost")
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_FOUND FALSE)
FIND_PACKAGE(Boost 1.42.0 REQUIRED COMPONENTS program_options system)
if ( Boost_FOUND )
  message(STATUS "Boost and boost components found.")
  include_directories( ${Boost_INCLUDE_DIRS} )
  SET(Dependencies 
  	  ${Dependencies} 
     ${Boost_LIBRAIRIES}  
     ${Boost_PROGRAM_OPTIONS_LIBRARY}
     ${Boost_SYSTEM_LIBRARY})
   SET(Include ${Include}${Boost_INCLUDE_DIRS})
endif( Boost_FOUND )



set(Dependencies ${Dependencies} ${OGRE_LIBRARIES} ${Boost_LIBRARIES})




configure_file(${CMAKE_SOURCE_DIR}/CMake/Resources/plugins.cfg.in  ${CMAKE_SOURCE_DIR}/CMake/Resources/plugins.cfg )  


add_subdirectory(test)