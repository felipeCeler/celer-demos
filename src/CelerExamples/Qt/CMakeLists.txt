# Examples

set(QT_USE_QTOPENGL true)
set(QT_USE_QTGUI true)
set(QT_WRAP_CPP true)
set(QT_WRAP_UI true)


# find needed packages
find_package(Qt4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


INCLUDE(${QT_USE_FILE})

IF(WIN32)
    ## OpenGL Windows without console ! See QMain Documentation
	LINK_LIBRARIES(${QT_QTMAIN_LIBRARY})
ENDIF(WIN32)

include_directories(
		##- Celer Library
		${CMAKE_SOURCE_DIR}/libs/Celer/src
        ${QT_INCLUDE_DIR}
        ${QT_QTCORE_INCLUDE_DIR}
        ${QT_QTGUI_INCLUDE_DIR}
        ${QT_QTOPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        )

add_subdirectory(BasicViewer)
