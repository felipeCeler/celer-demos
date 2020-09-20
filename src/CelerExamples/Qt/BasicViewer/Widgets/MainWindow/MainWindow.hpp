#ifndef _MYMAINWINDOW_
#define _MYMAINWINDOW_

#include <Widgets/GLWidget/GLWidget.hpp>

#include "ui_MainWindow.h"

#include <QtGui/QKeyEvent>

class QWorkspace;

class MainWindow: public QMainWindow
{
		Q_OBJECT

	public:
		MainWindow ( QMainWindow *parent = 0 );
		void open ( QString fileName = QString ( ) , bool who = true );
		void keyPressEvent ( QKeyEvent *e );

	public slots:

		void on_action_Load_Shaders_triggered ( );


	private:

		Ui::MainWindow * ui;

		bool showfullScreen_;
		GLWidget* glWidget;
};

#endif
