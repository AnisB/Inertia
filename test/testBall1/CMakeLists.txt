
cmake_minimum_required(VERSION 2.6)

 
file(
	GLOB_RECURSE 
	Source_File 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.ih
	${CMAKE_SOURCE_DIR}/src/*.cpp
    )
 

  include_directories( ${Includes})

if(APPLE)
    prepare_binary(${CMAKE_BINARY_DIR}/test/testBall1/ testBall1)
    add_executable(testBall1 testBall1.cpp ${Source_File} )
    target_link_libraries (testBall1  ${Dependencies}  ) 
else()
    add_executable(testBall1 testBall1.cpp ${Source_File} )
    target_link_libraries (testBall1  ${Dependencies}  )
endif()



