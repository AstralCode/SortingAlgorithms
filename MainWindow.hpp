#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class QAction;
class QTabWidget;
class VisualizationTaskTab;
class ExperimentalResearchTaskTab;

class MainWindow : public QMainWindow
{
	Q_OBJECT

	enum ProgramTaskTabID
	{
		VisualizationTab,
		ExperimentalResearchTab
	};

public:
	explicit MainWindow();

private slots:
	void onProgramTaskTabChanged(int index);

private:
	void createMenuBar();
	void createWidgets();
	void createConnections();
	void createLayout();

	QAction* mOpenInformationAction;
	QAction* mExitProgramAction;
	QTabWidget* mProgramTaskTabs;
	VisualizationTaskTab* mVisualizationTaskTab;
	ExperimentalResearchTaskTab* mExperimentalResearchTaskTab;
};

#endif // MAINWINDOW_HPP
