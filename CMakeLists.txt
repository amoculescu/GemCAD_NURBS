cmake_minimum_required(VERSION 2.8)

# ADD ADDITIONAL FIND SCRIPT PATH
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "Path for additional find scripts")

# PROJECT NAME
project(FrameWork_OpenGL_Curves)

# FIND OPENGL
find_package(OpenGL REQUIRED)
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OpenGL not found! This is no problem, if it is in the Windows/System32 folder.")
else(NOT OPENGL_FOUND)
	include_directories(${OpenGL_INCLUDE_DIRS})
endif(NOT OPENGL_FOUND)

# FIND GLUT (OR FREEGLUT). Set the root directory if it is not found automatically.
# CAUTION: USE "/" (e.g. C:/program files/...) for folder separation, not "\" !!!
if(WIN32)

	set(GLUT_ROOT_PATH ${PROJECT_SOURCE_DIR}/../freeglut CACHE PATH "Path to Glut Lib")	# use relative path. assume glut and this framework are siblings
	find_package(GLUT)
	if(NOT GLUT_FOUND)
		message(WARNING " GLUT or FREEGLUT not found! Try setting GLUT_ROOT_PATH in CMakeLists.txt.")
	else(NOT GLUT_FOUND)
		include_directories(${GLUT_INCLUDE_DIR})
	endif(NOT GLUT_FOUND)
else(WIN32)
	set(GLUT_LIBRARY glut)
endif(WIN32)

# MO add compiler flags -> compiler standard (>= c++11)
SET(GCC_STANDARD    "-std=c++11")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_STANDARD}" )

# ADD INCLUDE DIRECTORIES
include_directories(${PROJECT_SOURCE_DIR})

# GROUP SOURCES AND CREATE PROJECT
SET(HEADER_FILES
  "main.h"
  "BezierCurve.h"
  "NURBSCurve.h"
  "CurveRendering.h"
  "Vec3.h"
  "Vec4.h"
)
SET(SOURCE_FILES
  "main.cpp"
  "BezierCurve.cpp"
  "NURBSCurve.cpp"
  "CurveRendering.cpp"
)
source_group(Header FILES ${HEADER_FILES})
source_group(Source FILES ${SOURCE_FILES})
add_executable(main ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(main ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})

if(WIN32)

	IF(CMAKE_CL_64)
	# copy FreeGlut dll to build directory (on windows only)
	add_custom_command(TARGET main POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
			"${GLUT_INCLUDE_DIR}/../bin/x64/freeglut.dll"
			$<TARGET_FILE_DIR:main>)
	ELSE(CMAKE_CL_64)
	# copy FreeGlut dll to build directory (on windows only)
	add_custom_command(TARGET main POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
			"${GLUT_INCLUDE_DIR}/../bin/freeglut.dll"
			$<TARGET_FILE_DIR:main>)
	ENDIF(CMAKE_CL_64)
endif(WIN32)
