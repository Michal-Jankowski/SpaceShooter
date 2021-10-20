## Cmake config
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
project(SpaceShooter)

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_SUPPRESS_REGENERATION true)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT SpaceShooter)
set_property(DIRECTORY PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "debug:SpaceShooter" VS_DEBUGGER_COMMAND "debug:SpaceShooter")
set(TEMP_FILES_DIR "" CACHE PATH "assimp and freetype2 download path")
set(LIB_GLFW_DIR "${CMAKE_SOURCE_DIR}/dependencies/glfw" CACHE PATH "glfw library")
set(LIB_GLAD_DIR "${CMAKE_SOURCE_DIR}/dependencies/glad" CACHE PATH "glad library")
set(LIB_STB_DIR "${CMAKE_SOURCE_DIR}/dependencies/stb_image" CACHE PATH "stb_image library")
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


file(GLOB FILES_SOURCES 
"src/*.cpp"
"src/*.h"
"${LIB_GLAD_DIR}/include/glad.c"
"${LIB_STB_DIR}/stb_image.h"
"src/shaders/*.vs"
"src/shaders/*.fs")


add_executable(SpaceShooter ${FILES_SOURCES})

target_include_directories(SpaceShooter
PUBLIC "${LIB_GLFW_DIR}/include"
PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/glm"
PUBLIC "${LIB_ASSIMP_INCLUDE_DIR}"
PUBLIC "${LIB_GLAD_DIR}/include"
)
target_link_directories(SpaceShooter 
PUBLIC "${LIB_GLFW_DIR}/lib"
PUBLIC "${LIB_ASSIMP_BINARY_DIR}"
)

target_link_libraries(SpaceShooter 
glfw3.lib
opengl32.lib
)

if(NOT ${CONFIGURE_WITH_ASSIMP})
message("Configuring without assimp!")
else()
file(GLOB ASSIMP_LIB RELATIVE "${LIB_ASSIMP_BINARY_DIR}" "${LIB_ASSIMP_BINARY_DIR}/*.lib")
message("Assimp found: ${ASSIMP_LIB}")
file(GLOB ASSIMP_DLL "${LIB_ASSIMP_BINARY_DIR}/*.dll" )
target_link_libraries(SpaceShooter ${ASSIMP_LIB})
file(COPY ${ASSIMP_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()

make_directory(${CMAKE_CURRENT_BINARY_DIR}/lib/glm)
if(LIB_GLM_DIR STREQUAL "")
message("Path to glm NOT added!")
else()
file(COPY ${LIB_GLM_DIR}/glm DESTINATION  ${CMAKE_CURRENT_BINARY_DIR}/lib/glm)
file(COPY res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB SHADERY "src/shaders/*.vs"
 "src/shaders/*.fs")
file(COPY ${SHADERY} DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
file(TO_NATIVE_PATH "${CMAKE_CURRENT_BINARY_DIR}" MOVE_SCRIPT_BUILD_DIR)
file(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" MOVE_SCRIPT_SOURCE_DIR)
### Should be only added when decided how we treat release version from cmake
#file(COPY ${CMAKE_CURRENT_BINARY_DIR}/res/img/abel.ttf DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_BINARY_DIR}/res/img/virgo.ttf DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_BINARY_DIR}/res/img/Vac.ttf DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY ${CMAKE_CURRENT_BINARY_DIR}/res/img/edo.ttf DESTINATION  ${CMAKE_CURRENT_BINARY_DIR})
configure_file(src/moveNewFiles.bat.in moveNewFiles.bat)
endif()

if(${DOWNLOAD_FREETYPE})
##FreeType2
include(ExternalProject)
ExternalProject_Add(FreeType2 
	URL https://download.savannah.gnu.org/releases/freetype/freetype-2.11.0.tar.bz2
	PREFIX  ${DOWNLOAD_DIR}/FreeType2
	INSTALL_DIR  ${CMAKE_CURRENT_BINARY_DIR}/lib/ft2
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)
ExternalProject_Add_Step(FreeType2 install)
ExternalProject_Get_Property(FreeType2 install_dir)
set(LIB_FREETYPE_INCLUDE_DIR "${install_dir}/include/freetype2" CACHE PATH "FreeType include dir"  FORCE)
set(LIB_FREETYPE_BINARY_DIR "${install_dir}/lib" CACHE PATH "FreeType build results" FORCE)
message("Generate project and build FreeType project (as release), then reconfigure again with CONFIGURE_WITH_FREETYPE")
endif()

if(${CONFIGURE_WITH_FREETYPE})
include_directories(${LIB_FREETYPE_INCLUDE_DIR})
target_link_libraries(SpaceShooter ${LIB_FREETYPE_BINARY_DIR}/freetype.lib)
endif()

if(${DOWNLOAD_ASSIMP})
ExternalProject_Add(Assimp 
	URL https://github.com/assimp/assimp/archive/master.zip
	PREFIX  ${DOWNLOAD_DIR}/Assimp
	INSTALL_DIR  ${CMAKE_CURRENT_BINARY_DIR}/lib/assimp
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DASSIMP_BUILD_TESTS:BOOL=OFF -DASSIMP_BIN_INSTALL_DIR:PATH=lib -DCMAKE_BUILD_TYPE=Release
	BUILD_COMMAND ${CMAKE_COMMAND}  --build <BINARY_DIR> --target install --config Release
)
ExternalProject_Get_Property(Assimp install_dir)
set(LIB_ASSIMP_INCLUDE_DIR "${install_dir}/include" CACHE PATH "Assimp include dir"  FORCE)
set(LIB_ASSIMP_BINARY_DIR "${install_dir}/lib" CACHE PATH "Assimp build results" FORCE)
message("Generate project and build Assimp project (as release), then reconfigure again with CONFIGURE_WITH_ASSIMP")
endif()