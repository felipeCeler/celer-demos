#include <QtGui>
#include <QtGui/QInputDialog>
#include <iostream>

#include <Widgets/MainWindow/MainWindow.hpp>

MainWindow::MainWindow ( QMainWindow *parent ) :
	QMainWindow ( parent )
{

	ui = new Ui::MainWindow;
	ui->setupUi( this );

	this->glWidget = new GLWidget ( this );
	this->setCentralWidget ( glWidget );

	QIcon icon;
	icon.addFile ( ":/Icons/caju.png" , QSize ( ) , QIcon::Normal , QIcon::Off );
	setWindowIcon ( icon );
	showfullScreen_ = 0;
}

void MainWindow::on_action_Load_Shaders_triggered()
{
	glWidget->loadShaders();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	if(e->key()==Qt::Key_Return && e->modifiers()==Qt::AltModifier)
	{
		showfullScreen_ = !showfullScreen_;
		if ( showfullScreen_ )
		{
			showFullScreen ( );
		}else
		{
			showNormal();
		}
		e->accept();
	}
	else e->ignore();
}
