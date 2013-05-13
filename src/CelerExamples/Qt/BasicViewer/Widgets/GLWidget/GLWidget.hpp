#ifndef _GLWIDGET_H
#define _GLWIDGET_H

/// Celer::Libraries
	/// OpenGL
#include <Celer/OpenGLFramework/OpenGLContext.hpp>
#include <Celer/OpenGLFramework/GLTexture.hpp>
#include <Celer/OpenGLFramework/Shader.hpp>
#include <Celer/OpenGLFramework/ShaderManager.hpp>
	/// Math
#include <Celer/Core/Geometry/Math/Vector3.hpp>
#include <Celer/Core/Geometry/Math/Vector4.hpp>
	/// Scene
#include <Celer/Scene/Camera.hpp>

#include <QtOpenGL/QGLWidget>
#include <QtCore/QSet>
#include <QtCore/QTimer>



class GLWidget: public QGLWidget
{
		Q_OBJECT

	public:

		// From QGLWidget
		explicit GLWidget ( const QGLFormat& format , QWidget* parent = 0 , const QGLWidget* shareWidget = 0 , Qt::WindowFlags f = 0 );
		explicit GLWidget ( QWidget* parent = 0 , const QGLWidget* shareWidget = 0 , Qt::WindowFlags f = 0 );

		void initializeGL ( );
		void resizeGL ( int width , int height );
		void paintGL ( );
		void repaint ( );

		void processMultiKeys ( );

		void mousePressEvent ( QMouseEvent *event );
		void mouseMoveEvent ( QMouseEvent *event );
		void mouseReleaseEvent ( QMouseEvent *event );

		void keyPressEvent ( QKeyEvent * event );
		void keyReleaseEvent ( QKeyEvent * event );

	public slots:

		void loadShaders ( );



private:
	
	// About Scene
	Celer::Camera<float> camera_;

	float cameraStep_;

	/// Avoid camera_ move issues
	QSet<int> keysPresseds_;
	bool buttonRelease_;
	QTimer *timer;

	float centerX_;
	float centerY_;

	GLuint dumbVertexArray;
	GLuint dumbVertexBuffer;

	Celer::OpenGL::ShaderManager boxGeometryShader;
	Celer::OpenGL::ShaderManager wireframe;

};

#endif
