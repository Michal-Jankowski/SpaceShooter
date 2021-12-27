## Cmake config
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_SUPPRESS_REGENERATION true)

project(SpaceShooter)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "SpaceShooter")

file(COPY res DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file(COPY src DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file(COPY res DESTINATION ${CMAKE_BINARY_DIR}/Release)
file(COPY src DESTINATION ${CMAKE_BINARY_DIR}/Release)
## User properties
set(TEMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/Temp)
set(LIB_GLFW_DIR "${CMAKE_SOURCE_DIR}/dependencies/glfw" CACHE PATH "glfw library")
set(LIB_GLAD_DIR "${CMAKE_SOURCE_DIR}/dependencies/glad" CACHE PATH "glad library")
set(LIB_STB_DIR "${CMAKE_SOURCE_DIR}/dependencies/stb" CACHE PATH "stb_image library")
set(LIB_GLM_DIR "${CMAKE_SOURCE_DIR}/dependencies/glm" CACHE PATH "glm library")
set(LIB_ASSIMP_INCLUDE_DIR "" CACHE PATH "Assimp include dir")
set(LIB_ASSIMP_BINARY_DIR "" CACHE PATH "Assimp build results")
set(LIB_FREETYPE_INCLUDE_DIR " " CACHE PATH "Assimp include dir")
set(LIB_FREETYPE_BINARY_DIR "" CACHE PATH "Assimp build results")
set(LIB_FREETYPE_INCLUDE_DIR "" CACHE PATH "Assimp include dir")
set(LIB_FREETYPE_BINARY_DIR "" CACHE PATH "Assimp build results")

option(CONFIGURE_WITH_ASSIMP "Add assimp to project" OFF)
option(DOWNLOAD_ASSIMP "Download assimp to project" OFF)
option(DOWNLOAD_FREETYPE "Download freetype to project" OFF)
option(CONFIGURE_WITH_FREETYPE "Add freetype to project" OFF)
option(MOVE_SCRIPT_AUTO_CLOSE "Auto close file moving script" ON)

## append source files to executable
file(GLOB FILES_SOURCES 
		"src/*.cpp"
		"src/*.h"
		"src/game/*.cpp"
		"src/game/*.h"
		"src/game/elements/*.cpp"
		"src/game/elements/*.h"
		"src/game/models/*.cpp"
		"src/game/models/*.h"
		"src/engine/buffers/*.cpp"
		"src/engine/buffers/*.h"
		"src/engine/collisions/*.cpp"
		"src/engine/collisions/*.h"
		"src/engine/core/*.cpp"
		"src/engine/core/*.h"
		"src/engine/lighting/*.cpp"
		"src/engine/lighting/*.h"
		"src/engine/maths/*.cpp"
		"src/engine/maths/*.h"
		"src/engine/models/*.cpp"
		"src/engine/models/*.h"
		"src/engine/models/procedural/*.cpp"
		"src/engine/models/procedural/*.h"
		"src/engine/shaders/*.cpp"
		"src/engine/shaders/*.h"
		"src/engine/text/*.cpp"
		"src/engine/text/*.h"
		"src/engine/textures/*.cpp"
		"src/engine/textures/*.h"
		"src/engine/UI/*.cpp"
		"src/engine/UI/*.h"
		"src/engine/utils/*.cpp"
		"src/engine/utils/*.h"
		"src/shaders/*.vert"
		"src/shaders/*.frag"
		"${LIB_GLAD_DIR}/include/glad.c"
		"${LIB_STB_DIR}/stb_image.h")
    
add_executable(SpaceShooter ${FILES_SOURCES})

target_include_directories(SpaceShooter
PUBLIC "${LIB_GLFW_DIR}/include"
PUBLIC "${LIB_GLM_DIR}"
PUBLIC "${LIB_ASSIMP_INCLUDE_DIR}"
PUBLIC "${LIB_GLAD_DIR}/include")

target_link_directories(SpaceShooter 
PUBLIC "${LIB_GLFW_DIR}/lib"
PUBLIC "${LIB_ASSIMP_BINARY_DIR}")

target_link_libraries(SpaceShooter 
glfw3.lib
opengl32.lib)

file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}" MOVE_SCRIPT_BUILD_DIR)
file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" MOVE_SCRIPT_SOURCE_DIR)
### Should be only added when decided how we treat release version from cmake
#file(COPY ${CMAKE_CURRENT_BINARY_DIR}/res/img/abel.ttf DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_BINARY_DIR}/res/img/virgo.ttf DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_BINARY_DIR}/res/img/Vac.ttf DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_BINARY_DIR}/res/img/edo.ttf DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
configure_file(src/moveNewFiles.bat.in moveNewFiles.bat)

if(LIB_GLM_DIR STREQUAL "")
message("Path to glm NOT added!")
endif()

if(${DOWNLOAD_FREETYPE})
##FreeType2
include(ExternalProject)
ExternalProject_Add(FreeType2 
	URL https://download.savannah.gnu.org/releases/freetype/freetype-2.10.0.tar.bz2
	PREFIX  ${TEMP_DIR}/FreeType2
	INSTALL_DIR  ${CMAKE_CURRENT_BINARY_DIR}/lib/ft2
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>)
ExternalProject_Add_Step(FreeType2 install)
ExternalProject_Get_Property(FreeType2 install_dir)
set(LIB_FREETYPE_INCLUDE_DIR "${install_dir}/include/freetype2" CACHE PATH "FreeType include dir"  FORCE)
set(LIB_FREETYPE_BINARY_DIR "${install_dir}/lib" CACHE PATH "FreeType build results" FORCE)
message("Generate project and build FreeType project (as release), then reconfigure again with CONFIGURE_WITH_FREETYPE")
endif()

if(${CONFIGURE_WITH_FREETYPE})
include_directories(${LIB_FREETYPE_INCLUDE_DIR})
target_link_libraries(SpaceShooter ${LIB_FREETYPE_BINARY_DIR}/freetype.lib)
file(REMOVE_RECURSE ${TEMP_DIR}/FreeType2)
file(REMOVE_RECURSE ${TEMP_DIR}/x64/Release/FreeType2)
endif()

if(${DOWNLOAD_ASSIMP})
##Assimp
include(ExternalProject)
ExternalProject_Add(Assimp 
	URL https://github.com/assimp/assimp/archive/master.zip
	PREFIX  ${TEMP_DIR}/Assimp
	INSTALL_DIR  ${CMAKE_CURRENT_BINARY_DIR}/lib/assimp
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DASSIMP_BUILD_TESTS:BOOL=OFF -DASSIMP_BIN_INSTALL_DIR:PATH=lib -DCMAKE_BUILD_TYPE=Release
	BUILD_COMMAND ${CMAKE_COMMAND}  --build <BINARY_DIR> --target install --config Release)
ExternalProject_Get_Property(Assimp install_dir)
set(LIB_ASSIMP_INCLUDE_DIR "${install_dir}/include" CACHE PATH "Assimp include dir"  FORCE)
set(LIB_ASSIMP_BINARY_DIR "${install_dir}/lib" CACHE PATH "Assimp build results" FORCE)
message("Generate project and build Assimp project (as release), then reconfigure again with CONFIGURE_WITH_ASSIMP")
endif()

if(${CONFIGURE_WITH_ASSIMP})
file(GLOB ASSIMP_LIB RELATIVE "${LIB_ASSIMP_BINARY_DIR}" "${LIB_ASSIMP_BINARY_DIR}/*.lib")
if(ASSIMP_LIB STREQUAL "")
message("Assimp was not found!")
endif()
message("Assimp found: ${ASSIMP_LIB}")
file(GLOB ASSIMP_DLL "${LIB_ASSIMP_BINARY_DIR}/*.dll" )
target_link_libraries(SpaceShooter ${ASSIMP_LIB})
file(COPY ${ASSIMP_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${ASSIMP_DLL} DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file(COPY ${ASSIMP_DLL} DESTINATION ${CMAKE_BINARY_DIR}/Release)
file(REMOVE_RECURSE ${TEMP_DIR}/Assimp)
file(REMOVE_RECURSE ${TEMP_DIR}/x64/Release/Assimp)
endif()

if(${CONFIGURE_WITH_ASSIMP} AND ${CONFIGURE_WITH_FREETYPE})
file(REMOVE_RECURSE ${TEMP_DIR})
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/x64)
endif()
