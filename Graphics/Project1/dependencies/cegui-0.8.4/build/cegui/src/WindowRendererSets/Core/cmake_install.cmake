# Install script for directory: C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core

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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/lib/CEGUICoreWindowRendererSet_d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/lib/CEGUICoreWindowRendererSet.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/lib/CEGUICoreWindowRendererSet.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/lib/CEGUICoreWindowRendererSet.lib")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/bin/CEGUICoreWindowRendererSet_d.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/bin/CEGUICoreWindowRendererSet.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/bin/CEGUICoreWindowRendererSet.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/build/bin/CEGUICoreWindowRendererSet.dll")
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/WindowRendererSets/Core" TYPE FILE FILES
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Button.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Default.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Editbox.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/FrameWindow.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ItemEntry.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ItemListbox.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ListHeader.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ListHeaderSegment.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Listbox.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MenuItem.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Menubar.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Module.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MultiColumnList.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MultiLineEditbox.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/PopupMenu.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ProgressBar.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ScrollablePane.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Scrollbar.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Slider.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Static.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/StaticImage.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/StaticText.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/TabButton.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/TabControl.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Titlebar.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ToggleButton.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Tooltip.h"
    "C:/Users/Ben/Documents/CSC3224/Graphics/Project1/dependencies/cegui-0.8.4/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Tree.h"
    )
endif()

