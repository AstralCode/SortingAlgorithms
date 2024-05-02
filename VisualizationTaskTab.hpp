#ifndef VISUALIZATIONTASKTAB_HPP
#define VISUALIZATIONTASKTAB_HPP

#include <QWidget>

#include "SortingAlgorithm.hpp"
#include "Settings.hpp"
#include "Instruction.hpp"

class QAction;
class QMenu;
class QLCDNumber;
class QSpinBox;
class QToolButton;
class QButtonGroup;
class QTabWidget;
class QStackedWidget;
class QTimer;

class MainWindow;
class ArrayView;
class SourceCodeView;
class VariablesView;

class VisualizationTaskTab : public QWidget
{
	Q_OBJECT

	friend class MainWindow;

	enum PanelTabID
	{
		MainPanelTab
	};

	enum WorkModeWidgetID
	{
		AutomaticWorkModeWidget,
		ManualWorkModeWidget
	};

	enum AutomaticModeButtonID
	{
		RunAutomaticModeButton,
		PauseAutomaticModeButton,
		StopAutomaticModeButton
	};

	enum ManualModeButtonID
	{
		FirstInstructionButton,
		PreviousInstructionButton,
		NextInstructionButton
	};

	enum MenuButtonID
	{
		AutomaticModeButton,
		ManualModeButton,
		VisualizationSettingsButton
	};

public:
	explicit VisualizationTaskTab(QWidget* parent = 0);

private slots:
	void onSetSourceCode(SortingAlgorithmType sortingAlgorithm);
	void onAutomaticModeButtonClicked(int buttonID);
	void onManualModeButtonClicked(int buttonID);
	void onMenuButtonClicked(int buttonID);
	void onPrepareVisualizationTask();
	void onContextMenu(const QPoint& Position);
	void onHidePanelRightSide(bool hide);

private:
	void createActions();
	void createWidgets();
	void createConnections();
	void createLayout();

	QWidget* createRightSideWidget();
	QWidget* createMainPanelWidget();
	QWidget* createAutomaticWorkModeWidget();
	QWidget* createManualWorkModeWidget();
	QWidget* createColorBoxFrame(int length, const QColor& color);

	void openVisualizationSettings();
	void refreshViews();

	QTabWidget* mPanelTabs;
	QAction* mPanelRightSideVisible;
	QMenu* mPanelMenu;
	QWidget* mPanelRightSide;
	QLCDNumber* mLCDCurrentInstruction;
	QLCDNumber* mLCDInstructionCounter;
	QLCDNumber* mLCDCompareCounter;
	QLCDNumber* mLCDSwapCounter;
	QToolButton* mRunAutomaticModeButton;
	QToolButton* mPauseAutomaticModeButton;
	QToolButton* mStopAutomaticModeButton;
	QButtonGroup* mAutomaticModeButtonGroup;
	QToolButton* mFirstInstructionButton;
	QToolButton* mPreviousInstructionButton;
	QToolButton* mNextInstructionButton;
	QButtonGroup* mManualModeButtonGroup;
	QStackedWidget* mWorkModeWidgets;
	QToolButton* mAutomaticModeButton;
	QToolButton* mManualModeButton;
	QToolButton* mVisualizationSettingsButton;
	QButtonGroup* mMenuButtonGroup;
	QSpinBox* mIntervalSpinBox;
	QSpinBox* mInstructionChanger;
	QTimer* mTimer;
	ArrayView* mArrayView;
	SourceCodeView* mSourceCodeView;
	VariablesView* mVariablesView;
	SortingAlgorithm::Ptr mSortingAlgorithm;
	Settings mSettings;
	QVector<Instruction> mInstructions;
};

#endif // VISUALIZATIONTASKTAB_HPP
