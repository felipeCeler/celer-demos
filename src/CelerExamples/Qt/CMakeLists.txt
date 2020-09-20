# Examples

# find needed packages
find_package(Qt5 COMPONENTS Widgets Gui REQUIRED)
#   find_package(tinyobjloader)

# Enable automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(AUTOMOC_MOC_OPTIONS PROPERTIES FOLDER CMakeAutomocTargets)
set_property(GLOBAL PROPERTY AUTOMOC_FOLDER CMakeAutomocTargets)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


IF(WIN32)
    ## OpenGL Windows without console ! See QMain Documentation
	## LINK_LIBRARIES(${QT_QTMAIN_LIBRARY})
ENDIF(WIN32)

include_directories(
		##- Celer Library
		${CMAKE_SOURCE_DIR}/libs/Celer/src        
        )

add_subdirectory(BasicViewer)
