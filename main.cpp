#include "MainWindow.h"
#include "Block.h"
#include "baseLine.h"
#include "GameController.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
