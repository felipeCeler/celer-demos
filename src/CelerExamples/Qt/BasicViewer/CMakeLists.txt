# Teste
project(BasicViewer)

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

set( ${PROJECT_NAME}_SOURCES App/main.cpp 
    						 Widgets/MainWindow/MainWindow.cpp
    						 Widgets/GLWidget/GLWidget.cpp
    						 )
	
set( ${PROJECT_NAME}_HEADERS 
    Widgets/MainWindow/MainWindow.hpp
    Widgets/GLWidget/GLWidget.hpp)	

set( MOC_HEADERS Widgets/MainWindow/MainWindow.hpp
                 Widgets/GLWidget/GLWidget.hpp
                   )
                 
set( UI_SOURCES Widgets/MainWindow/MainWindow.ui)

set(RCC_SOURCES Widgets/MainWindow/Resources/Resources.qrc)

QT4_WRAP_CPP( MOC_SOURCES ${MOC_HEADERS})
QT4_WRAP_UI (UI_HEADERS ${UI_SOURCES})
QT4_ADD_RESOURCES(RCC_HEADERS ${RCC_SOURCES})

IF(WIN32)
	ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS} ${MOC_SOURCES} ${UI_HEADERS} ${RCC_HEADERS})
ELSE(WIN32)
	ADD_EXECUTABLE(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS} ${MOC_SOURCES} ${UI_HEADERS} ${RCC_HEADERS})	
ENDIF(WIN32)
               
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES}  ${OPENGL_LIBRARIES} CelerMath CelerScene CelerOpenGLFramework )


# Do a better solution. This one is Ungly !!!
SET (SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/Widgets/GLWidget/Shaders")
             
SET (DESTINATION "${CMAKE_BINARY_DIR}/build/share/Shaders")

ADD_CUSTOM_TARGET (CopyShaders ALL
                   DEPENDS ${SOURCE}
                   COMMENT "Copying Shaders: ${SOURCE} ${DESTINATION}" )
                 
ADD_CUSTOM_COMMAND (
                TARGET CopyShaders
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE} ${DESTINATION} )   