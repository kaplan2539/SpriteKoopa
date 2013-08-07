cmake_minimum_required(VERSION 2.8.9)

project( SpriteKoopa )

# Find includes in corresponding build directories.
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Instruct CMake to run moc automatically when needed.
set( CMAKE_AUTOMOC ON )

# Find OpenCV
find_package( OpenCV REQUIRED )

# Find the Qt modules
find_package( Qt5Core    REQUIRED )
find_package( Qt5Gui     REQUIRED )
find_package( Qt5Widgets REQUIRED )

include_directories (${CMAKE_CURRENT_BINARY_DIR}) 

set( spritekoopa_forms
     mainwindow.ui
   )

qt5_wrap_ui( spritekoopa_ui ${spritekoopa_forms} )

add_executable( spritekoopa 
                main.cpp
                mainwindow.cpp
                ${spritekoopa_ui}
              )

# Link to OpenCV.
target_link_libraries( spritekoopa ${OpenCV_LIBS} )

# Link to Qt modules.
qt5_use_modules(spritekoopa Widgets Gui Core)
