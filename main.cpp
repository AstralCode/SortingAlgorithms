#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
	QApplication application(argc, argv);
	application.setApplicationName(QStringLiteral("Wizualizacja algorytmów sortowania"));

	MainWindow mainWindow;
	mainWindow.showMaximized();

	return application.exec();
}
