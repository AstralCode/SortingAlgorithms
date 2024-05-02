#include "MainWindow.hpp"

#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QButtonGroup>
#include <QToolButton>
#include <QTabWidget>
#include <QTime>

#include "VisualizationTaskTab.hpp"
#include "ExperimentalResearchTaskTab.hpp"
#include "InformationWindow.hpp"


MainWindow::MainWindow() :
	mOpenInformationAction{new QAction(QStringLiteral("Informacje"), this)},
	mExitProgramAction{new QAction(QStringLiteral("Zakończ"), this)},
	mProgramTaskTabs{new QTabWidget},
	mVisualizationTaskTab{new VisualizationTaskTab},
	mExperimentalResearchTaskTab{new ExperimentalResearchTaskTab}
{
	setWindowTitle(QStringLiteral("Algorytmy sortowania"));
	setWindowIcon(QIcon(QStringLiteral(":/Resources/Ascending.png")));
	setContextMenuPolicy(Qt::NoContextMenu);

	createMenuBar();
	createWidgets();
	createConnections();
	createLayout();

	qsrand(static_cast<uint>(QTime::currentTime().msec()));
}

void MainWindow::onProgramTaskTabChanged(int index)
{
	switch(index)
	{
		case ProgramTaskTabID::VisualizationTab:
		{
			break;
		}

		case ProgramTaskTabID::ExperimentalResearchTab:
		{
			break;
		}
	}
}

void MainWindow::createMenuBar()
{
	mOpenInformationAction->setIcon(QIcon(QStringLiteral(":/Resources/Information.png")));
	mExitProgramAction->setIcon(QIcon(QStringLiteral(":/Resources/Exit.png")));

	QMenu* programMenu = menuBar()->addMenu(QStringLiteral("Program"));
	programMenu->addAction(mOpenInformationAction);
	programMenu->addSeparator();
	programMenu->addAction(mExitProgramAction);
}

void MainWindow::createWidgets()
{
	mProgramTaskTabs->addTab(mVisualizationTaskTab, QStringLiteral("Wizualizacja"));
	mProgramTaskTabs->addTab(mExperimentalResearchTaskTab, QStringLiteral("Badania eksperymentalne"));
}

void MainWindow::createConnections()
{
	connect(mExitProgramAction,
		&QAction::triggered,
		this,
		&QWidget::close);

	connect(mProgramTaskTabs,
		&QTabWidget::currentChanged,
		this,
		&MainWindow::onProgramTaskTabChanged);

	connect(mOpenInformationAction,
		&QAction::triggered, [](){ new InformationWindow; });
}

void MainWindow::createLayout()
{
	setContentsMargins(3, 3, 3, 3);
	setCentralWidget(mProgramTaskTabs);
}
