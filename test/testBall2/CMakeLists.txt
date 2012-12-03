
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
    prepare_binary(${CMAKE_BINARY_DIR}/test/testBall2/ testBall2)
    add_executable(testBall2 testBall2.cpp ${Source_File} )
    target_link_libraries (testBall2  ${Dependencies}  ) 
else()
    add_executable(testBall2 testBall2.cpp ${Source_File} )
    target_link_libraries (testBall2  ${Dependencies}  )
endif()



