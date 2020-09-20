#include <QtWidgets/QApplication>
#include <iostream>

#include <Widgets/MainWindow/MainWindow.hpp>


int main(int argc, char *argv[])
{

	QApplication app ( argc , argv );

	MainWindow * form = new MainWindow;

	form->show ( );

	return app.exec ( );
}




