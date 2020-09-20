#include <Widgets/GLWidget/GLWidget.hpp>

#include <QtCore/QDir>

// Qt5 Framework
// Qt Gui
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QApplication>


#include <stdio.h>
#include <stdlib.h>

GLWidget::GLWidget (QWidget * parent) : QOpenGLWidget (parent)
{

}

/// OpenGL
void GLWidget::initializeGL ( )
{
	/// Celer OpenGL
	Celer::OpenGL::OpenGLContext::instance()->glewInitialize("CelerFrameBuffer GLWidget.cpp line 22");
	/// Celer OpenGL

	setMinimumSize ( 640 , 480 );
	setSizePolicy ( QSizePolicy::MinimumExpanding , QSizePolicy::MinimumExpanding );
	/// Key event to GLWidget not o MainWindow ! | @QtDocumentation
	setFocus ( );
	/// If mouse tracking is enabled, the widget receives mouse move events even if no buttons are pressed. | @QtDocmentation
	setMouseTracking ( true );
	setFocusPolicy ( Qt::StrongFocus );
	setAttribute ( Qt::WA_NoSystemBackground );
	setAutoFillBackground ( false );
	setAcceptDrops(true);

	timer = new QTimer ( this );
	connect ( timer , SIGNAL ( timeout ( ) ) , this , SLOT ( repaint ( ) ) );
	timer->start ( 0 );


	glGenVertexArrays(1, &dumbVertexArray );
	glBindVertexArray ( dumbVertexArray );

	/// Requesting Vertex Buffers to the GPU
	glGenBuffers ( 1 , &dumbVertexBuffer );
		glBindBuffer ( GL_ARRAY_BUFFER , dumbVertexBuffer );
		glBufferData ( GL_ARRAY_BUFFER , 0 , 0 , GL_STATIC_DRAW );
		// Set up generic attributes pointers
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, 0);
		/// Requesting Vertex Buffers to the GPU

	loadShaders ( );

	camera_.setPosition ( Celer::Vector3<float> ( 0.0f , 0.0f , 10.0f ) );
	camera_.setAspectRatio(width(),height());
	camera_.setPerspectiveProjectionMatrix ( 60 , camera_.aspectRatio() , 0.1 , 500 );
	camera_.setOrthographicProjectionMatrix ( 0.0 , GLfloat ( width ( ) ) , 0.0 , GLfloat ( height ( ) ) , -100.0 , 100.0 );

	camera_.setBehavior ( Celer::Camera<float>::REVOLVE_AROUND_MODE );
	camera_.setTarget( Celer::Vector3<float>(0.0f,0.0f,0.0f));
	camera_.setOffset( 8.0f );

	glEnable ( GL_DEPTH_TEST );

	glClearColor ( 0.0, 0.0 , 0.0 , 1.0 );

}



void GLWidget::resizeGL ( int width , int height )
{
	glViewport ( 0 , 0 , width , height );

	camera_.setWindowSize ( width , height );

	camera_.setAspectRatio( width, height );

	camera_.setPerspectiveProjectionMatrix ( 60 , camera_.aspectRatio() , 0.1 , 500 );

	centerX_ = static_cast<float> ( width * 0.5 );
	centerY_ = static_cast<float> ( height * 0.5 );
}
/// KeyInput
void GLWidget::processMultiKeys ( )
{

	foreach( int key , keysPresseds_)
	{
		if ( key == Qt::Key_Q )
		{
			camera_.moveUpward ( cameraStep_ );

		}
		if ( key == Qt::Key_E )
		{
			camera_.moveUpward ( -cameraStep_ );

		}
		else if ( key == Qt::Key_W )
		{
			camera_.moveForward ( cameraStep_ );

		}
		if ( key == Qt::Key_S )
		{
			camera_.moveForward ( -cameraStep_ );

		}
		if ( key == Qt::Key_A )
		{
			camera_.strafeRight ( -cameraStep_ );

		}
		if ( key == Qt::Key_D )
		{
			camera_.strafeRight ( cameraStep_ );

		}
		if ( key == Qt::Key_R )
		{

			camera_.reset ( );

		}
		if ( key == Qt::Key_Plus )
		{

			if ( cameraStep_ < 2.0 )
			cameraStep_ += 0.01;

		}
		if ( key == Qt::Key_Minus )
		{

			if ( cameraStep_ > 0.0 )
			cameraStep_ -= 0.01;
		}
	}


}

void GLWidget::keyPressEvent ( QKeyEvent * event )
{
	buttonRelease_ = true;
	keysPresseds_ += event->key ( );
}

void GLWidget::keyReleaseEvent ( QKeyEvent * event )
{
	buttonRelease_ = false;
	keysPresseds_ -= event->key ( );
}
/// MouseInput
void GLWidget::mousePressEvent ( QMouseEvent *event )
{
	event->accept ( );

	if ( event->button ( ) == Qt::LeftButton )
	{
		camera_.lockMouse ( true );
		centerX_ = static_cast<float> ( event->x ( ) );
		centerY_ = static_cast<float> ( event->y ( ) );
	}
}

void GLWidget::mouseReleaseEvent ( QMouseEvent *event )
{
	event->accept ( );

	if ( event->button ( ) == Qt::LeftButton )
	{
		camera_.lockMouse ( false );

	}

}

void GLWidget::mouseMoveEvent ( QMouseEvent *event )
{

	if ( event->buttons ( ) & Qt::LeftButton )
	{
		//camera_.SetMouseInfo(event->x(),event->y());
		float heading 	= 0.0f;
		float pitch 	= 0.0f;
		float roll 	= 0.0f;

		pitch 	= - ( static_cast<float> ( event->x ( ) ) - centerX_ ) * 0.2;
		heading = - ( static_cast<float> ( event->y ( ) ) - centerY_ ) * 0.2;

		camera_.rotate ( pitch , heading , roll );

		/*! Tr�s coisas :
		 *  - event->pos() retorna coordenadas x e y relativa a widget que recebeu o evento.
		 *  - mapToGlobla mapei as coordenadas da widget para coordenada global da tela.
		 *  - QCurso::setPos() posiciona o mouse em coordenada global.
		 *
		 *  Tudo o que eu queria para implementar a First Person Camera !
		 */
		QCursor::setPos ( mapToGlobal ( QPoint ( static_cast<int> ( centerX_ ) , static_cast<int> ( centerY_ ) ) ) );
	}

}

void GLWidget::repaint()
{
	paintGL();
};

void GLWidget::paintGL ( )
{

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	camera_.setViewByMouse ( );

	if ( buttonRelease_ )
	{
		processMultiKeys ( );
	}

	camera_.computerViewMatrix( );


	boxGeometryShader.active();

	// 1rst attribute buffer : vertices
	glBindVertexArray(dumbVertexArray);

	glUniform4fv ( boxGeometryShader.uniforms_["min_point"].location , 1 , Celer::Vector4<float> ( -1.0,-1.0,-1.0 , 1.0f ) );
	glUniform4fv ( boxGeometryShader.uniforms_["max_point"].location , 1 , Celer::Vector4<float> (  1.0, 1.0, 1.0 , 1.0f ) );
	glUniformMatrix4fv ( boxGeometryShader.uniforms_["ModelMatrix"].location , 1 , GL_TRUE , camera_.orientation ( ).to4x4Matrix ( ) );
	glUniformMatrix4fv ( boxGeometryShader.uniforms_["ViewMatrix"].location , 1 , GL_TRUE , camera_.viewMatrix ( ) );
	glUniformMatrix4fv ( boxGeometryShader.uniforms_["ProjectionMatrix"].location , 1 , GL_TRUE , camera_.perspectiveProjectionMatrix ( ) );


	// Dump Call Function
	glDrawArrays ( GL_POINTS , 0 , 1 );

	glBindVertexArray(0);

	boxGeometryShader.deactive();

}


void GLWidget::loadShaders ( )
{
	QDir shadersDir = QDir ( qApp->applicationDirPath () );
	//qDebug () << "Directory " << shadersDir.path ();
	shadersDir.cdUp ();
	//qDebug () << "Directory " << shadersDir.path ();

	boxGeometryShader.create("boxGeometryShader",("share/Shaders/boxGeometryShader.vert"),("share/Shaders/boxGeometryShader.geom"),("share/Shaders/boxGeometryShader.frag"));
}

