# Install script for directory: C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/cegui")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/cegui/src/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/cegui/src/RendererModules/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/cegui/src/XMLParserModules/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/cegui/src/ImageCodecModules/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/cegui/src/WindowRendererSets/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/cegui/src/ScriptModules/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/cegui/src/CommonDialogs/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/samples_framework/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/samples/cmake_install.cmake")
  include("C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/datafiles/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
