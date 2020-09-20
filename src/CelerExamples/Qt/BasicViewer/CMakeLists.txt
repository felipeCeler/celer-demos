set(target BasicViewer)

#set(CMAKE_BUILD_TYPE "DEBUG")

message(STATUS "Lib ${target} as ${CMAKE_BUILD_TYPE}")

find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)
#   find_package(tinyobjloader)

# Enable automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)
set_property(GLOBAL PROPERTY AUTOMOC_FOLDER CMakeAutomocTargets)

# ENABLE CMP0020: Automatically link Qt executables to qtmain target on Windows.
cmake_policy(SET CMP0020 NEW)

# 
# Library name and options
# 

# Target name

# Exit here if required dependencies are not met
if (NOT Qt5Core_FOUND)
    message(STATUS "Example ${target} skipped: Qt5 not found")
    return()
endif()

# 
# Sources
#

set(${target}_sources 

    App/main.cpp
    Widgets/GLWidget/GLWidget.hpp
    Widgets/GLWidget/GLWidget.cpp
    Widgets/MainWindow/MainWindow.hpp
    Widgets/MainWindow/MainWindow.cpp
    Widgets/MainWindow/MainWindow.ui    
)

set ( ${target}_resources
    Widgets/MainWindow/Resources/Resources.qrc
)
# Build executable
add_executable(${target}
    ${${target}_sources}
    ${${target}_resources}
)

# Create namespaced alias
add_executable(${META_PROJECT_NAME}::${target} ALIAS ${target})

# 
# Project options
# 

set ( OUTPUT  "${CMAKE_BINARY_DIR}/build/${target}")

set_target_properties(${target}
    PROPERTIES
    # cmake/CompileOptions.cmake
    ${DEFAULT_PROJECT_OPTIONS}
    # Targets with no FOLDER property will appear as top level entities in IDEs like Visual Studio
    FOLDER "celer/01_create_context_qt"
    # Example: extension .exe
    OUTPUT_NAME ${target} 
    #SUFFIX ".bin"
    #PREFIX "celer_"
    CXX_STANDARD 17
        
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT}/data"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT}/bin"
)

# 
# Include directories
# 

target_include_directories(${target}
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    SYSTEM
    ${CMAKE_CURRENT_SOURCE_DIR}    
)

# 
# Libraries
# 

target_link_libraries(${target}
    PRIVATE           
      CelerMath 
      CelerScene 
      CelerOpenGLFramework  
      ${GLEW_GLEW_LIBRARY}
      Qt5::Gui
      Qt5::Widgets  
)



# 
# Compile definitions
# 

target_compile_definitions(${target}
    PRIVATE
        ${DEFAULT_COMPILE_DEFINITIONS}
    #@see https://github.com/cginternals/glbinding/blob/16d5d987bd65a6278066b3601b695b811fe943df/source/examples/comparison/CMakeLists.txt
)


# 
# Compile options
# 

# As an alternative, CMake also offers a finer grained approach, allowing you to specify the compiler features
# @see https://crascit.com/2015/03/28/enabling-cxx11-in-cmake/

target_compile_options(${target}
    PRIVATE
        ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(${target}
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)
        

# Do a better solution. This one is Ungly !!!
SET (SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Widgets/GLWidget/Shaders")
             
SET (DESTINATION "${CMAKE_BINARY_DIR}/build/share/Shaders")

ADD_CUSTOM_TARGET (CopyShaders ALL
                   DEPENDS ${SOURCE}
                   COMMENT "Copying Shaders: ${SOURCE} ${DESTINATION}" )
                 
ADD_CUSTOM_COMMAND (
                TARGET CopyShaders
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE} ${DESTINATION} )   