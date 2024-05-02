#include "VisualizationTaskTab.hpp"

#include <QMenu>
#include <QAction>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QSpinBox>
#include <QLCDNumber>
#include <QToolButton>
#include <QButtonGroup>
#include <QFrame>
#include <QTabWidget>
#include <QStackedWidget>
#include <QTimer>
#include <QGroupBox>
#include <QSplitter>
#include <QGridLayout>
#include <QVBoxLayout>

#include "ArrayView.hpp"
#include "SourceCodeView.hpp"
#include "VariablesView.hpp"
#include "SortingAlgorithms.hpp"
#include "SettingsWindow.hpp"


VisualizationTaskTab::VisualizationTaskTab(QWidget* parent) :
	QWidget{parent},
	mPanelTabs{new QTabWidget},
	mPanelRightSideVisible{new QAction{this}},
	mPanelMenu{new QMenu},
	mPanelRightSide{new QWidget},
	mLCDCurrentInstruction{new QLCDNumber},
	mLCDInstructionCounter{new QLCDNumber},
	mLCDCompareCounter{new QLCDNumber},
	mLCDSwapCounter{new QLCDNumber},
	mRunAutomaticModeButton{new QToolButton},
	mPauseAutomaticModeButton{new QToolButton},
	mStopAutomaticModeButton{new QToolButton},
	mAutomaticModeButtonGroup{new QButtonGroup},
	mFirstInstructionButton{new QToolButton},
	mPreviousInstructionButton{new QToolButton},
	mNextInstructionButton{new QToolButton},
	mManualModeButtonGroup{new QButtonGroup},
	mWorkModeWidgets{new QStackedWidget},
	mAutomaticModeButton{new QToolButton},
	mManualModeButton{new QToolButton},
	mVisualizationSettingsButton{new QToolButton},
	mMenuButtonGroup{new QButtonGroup},
	mIntervalSpinBox{new QSpinBox},
	mInstructionChanger{new QSpinBox},
	mTimer{new QTimer},
	mArrayView{new ArrayView},
	mSourceCodeView{new SourceCodeView},
	mVariablesView{new VariablesView}
{
	setContextMenuPolicy(Qt::NoContextMenu);

	createActions();
	createWidgets();
	createConnections();
	createLayout();

	refreshViews();

	onPrepareVisualizationTask();
}

void VisualizationTaskTab::onSetSourceCode(SortingAlgorithmType sortingAlgorithm)
{
	switch(sortingAlgorithm)
	{
		case SortingAlgorithmType::InsertionSort:
		{
			mSortingAlgorithm.reset(new InsertionSort);

			break;
		}
		case SortingAlgorithmType::SelectionSort:
		{
			mSortingAlgorithm.reset(new SelectionSort);

			break;
		}
		case SortingAlgorithmType::BubbleSort:
		{
			mSortingAlgorithm.reset(new BubbleSort);

			break;
		}
		case SortingAlgorithmType::MergeSort:
		{
			mSortingAlgorithm.reset(new MergeSort);

			break;
		}
		case SortingAlgorithmType::HeapSort:
		{
			mSortingAlgorithm.reset(new HeapSort);

			break;
		}
		case SortingAlgorithmType::QuickSortLomuto:
		{
			mSortingAlgorithm.reset(new QuickSortLomuto);

			break;
		}
		case SortingAlgorithmType::QuickSortHoare:
		{
			mSortingAlgorithm.reset(new QuickSortHoare);

			break;
		}
		default:
		{
			break;
		}
	}

	mSourceCodeView->setSourceCode(mSortingAlgorithm->getName(), mSortingAlgorithm->getSourceCode());
	mVariablesView->setVariableInformation(mSortingAlgorithm->getVariableInformationList());
}

void VisualizationTaskTab::onAutomaticModeButtonClicked(int buttonID)
{
	switch(buttonID)
	{
		case AutomaticModeButtonID::RunAutomaticModeButton:
		{
			if(!mTimer->isActive())
				mTimer->start();

			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::RunAutomaticModeButton)->setEnabled(false);
			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::PauseAutomaticModeButton)->setEnabled(true);
			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->setEnabled(true);
			mManualModeButtonGroup->button(ManualModeButtonID::NextInstructionButton)->setEnabled(true);

			break;
		}
		case AutomaticModeButtonID::PauseAutomaticModeButton:
		{
			if(mTimer->isActive())
				mTimer->stop();

			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::RunAutomaticModeButton)->setEnabled(true);
			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::PauseAutomaticModeButton)->setEnabled(false);
			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->setEnabled(true);

			break;
		}
		case AutomaticModeButtonID::StopAutomaticModeButton:
		{
			if(mTimer->isActive())
				mTimer->stop();

			mManualModeButtonGroup->button(ManualModeButtonID::FirstInstructionButton)->setEnabled(true);
			mManualModeButtonGroup->button(ManualModeButtonID::FirstInstructionButton)->click();

			break;
		}
	}
}

void VisualizationTaskTab::onManualModeButtonClicked(int buttonID)
{
	int currentInstruction = mLCDCurrentInstruction->value();

	switch(buttonID)
	{
		case ManualModeButtonID::FirstInstructionButton:
		{
			currentInstruction = 0;

			mManualModeButtonGroup->button(ManualModeButtonID::FirstInstructionButton)->setEnabled(false);
			mManualModeButtonGroup->button(ManualModeButtonID::PreviousInstructionButton)->setEnabled(false);
			mManualModeButtonGroup->button(ManualModeButtonID::NextInstructionButton)->setEnabled(true);

			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::RunAutomaticModeButton)->setEnabled(true);
			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::PauseAutomaticModeButton)->setEnabled(false);
			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->setEnabled(false);

			break;
		}
		case ManualModeButtonID::PreviousInstructionButton:
		{
			--currentInstruction;

			mManualModeButtonGroup->button(ManualModeButtonID::NextInstructionButton)->setEnabled(true);

			if(currentInstruction <= 0)
			{
				mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->setEnabled(true);
				mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->click();
			}

			break;
		}
		case ManualModeButtonID::NextInstructionButton:
		{
			++currentInstruction;

			mManualModeButtonGroup->button(ManualModeButtonID::FirstInstructionButton)->setEnabled(true);
			mManualModeButtonGroup->button(ManualModeButtonID::PreviousInstructionButton)->setEnabled(true);

			if(currentInstruction > mLCDInstructionCounter->value())
			{
				--currentInstruction;

				mManualModeButtonGroup->button(ManualModeButtonID::FirstInstructionButton)->setEnabled(true);
				mManualModeButtonGroup->button(ManualModeButtonID::PreviousInstructionButton)->setEnabled(true);
				mManualModeButtonGroup->button(ManualModeButtonID::NextInstructionButton)->setEnabled(false);
			}

			break;
		}
	}

	mLCDCurrentInstruction->display(currentInstruction < 0 ? ++currentInstruction : currentInstruction);

	const Instruction& instruction = mInstructions.at(currentInstruction);

	mLCDCompareCounter->display(instruction.getCompareCounter());
	mLCDSwapCounter->display(instruction.getSwapCounter());

	mSourceCodeView->setCurrentSourceCode(instruction.getCurrentFunction());
	mSourceCodeView->onSetCurrentHighlightLine(instruction.getLineNumber());

	mVariablesView->setVariables(instruction.getVariables());

	mArrayView->resetArrayBlocks();
	mArrayView->onSetArrayBlockValues(instruction.getArray());
	mArrayView->setArrayBlocksColored(instruction.getSortRangeBlocks());
	mArrayView->setArrayBlocksColor(instruction.getMarkBlocks());
	mArrayView->setArrayBlocksColor(instruction.getCompareBlocks(), Qt::white);
	mArrayView->setArrayBlocksColor(instruction.getSwapBlocks(), Qt::red);
}

void VisualizationTaskTab::onMenuButtonClicked(int buttonID)
{
	switch(buttonID)
	{
		case MenuButtonID::AutomaticModeButton:
		{
			mWorkModeWidgets->setCurrentIndex(WorkModeWidgetID::AutomaticWorkModeWidget);

			break;
		}
		case MenuButtonID::ManualModeButton:
		{
			mWorkModeWidgets->setCurrentIndex(WorkModeWidgetID::ManualWorkModeWidget);
			mAutomaticModeButtonGroup->button(AutomaticModeButtonID::PauseAutomaticModeButton)->click();

			break;
		}
		case MenuButtonID::VisualizationSettingsButton:
		{
			openVisualizationSettings();

			break;
		}
	}
}

void VisualizationTaskTab::onPrepareVisualizationTask()
{
	mInstructions.clear();

	mSortingAlgorithm->run(mSettings.mArray, mInstructions);

	mLCDCurrentInstruction->display(0);
	mLCDInstructionCounter->display(mInstructions.size() - 1);

	mInstructionChanger->setRange(mLCDCurrentInstruction->value(), mLCDInstructionCounter->value());

	mSourceCodeView->onSetCurrentHighlightLine(mInstructions.at(0).getLineNumber());

	mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->setEnabled(true);
	mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->click();
}

void VisualizationTaskTab::createActions()
{
	mPanelMenu->setTitle(QStringLiteral("Panel menu"));

	mPanelRightSideVisible->setText(QStringLiteral("Ukryj postęp i menu"));
	mPanelRightSideVisible->setCheckable(true);

	mPanelMenu->addAction(mPanelRightSideVisible);
}

void VisualizationTaskTab::createWidgets()
{
	mArrayView->setArrayFixedSize(Settings::ArrayFixedSize, Settings::ArrayMaximumValue);

	mPanelTabs->addTab(createMainPanelWidget(), QStringLiteral("Panel główny"));

	mLCDCurrentInstruction->setSegmentStyle(QLCDNumber::Flat);
	mLCDCurrentInstruction->setFixedSize(64, 30);

	mLCDInstructionCounter->setSegmentStyle(QLCDNumber::Flat);
	mLCDInstructionCounter->setFixedSize(64, 30);

	mLCDCompareCounter->setSegmentStyle(QLCDNumber::Flat);
	mLCDCompareCounter->setFixedSize(64, 30);

	mLCDSwapCounter->setSegmentStyle(QLCDNumber::Flat);
	mLCDSwapCounter->setFixedSize(64, 30);

	mRunAutomaticModeButton->setIcon(QIcon(QStringLiteral(":/Resources/Run.png")));
	mRunAutomaticModeButton->setIconSize(QSize(68, 24));

	//mRunAutomaticModeButton->setFixedSize(mRunAutomaticModeButton->sizeHint());

	mRunAutomaticModeButton->setEnabled(false);
	mRunAutomaticModeButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

	mPauseAutomaticModeButton->setIcon(QIcon(QStringLiteral(":/Resources/Pause.png")));
	mPauseAutomaticModeButton->setIconSize(mRunAutomaticModeButton->iconSize());

	//mPauseAutomaticModeButton->setFixedSize(mRunAutomaticModeButton->sizeHint());

	mPauseAutomaticModeButton->setEnabled(false);
	mPauseAutomaticModeButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

	mStopAutomaticModeButton->setIcon(QIcon(QStringLiteral(":/Resources/Stop.png")));
	mStopAutomaticModeButton->setIconSize(mRunAutomaticModeButton->iconSize());

	//mStopAutomaticModeButton->setFixedSize(mRunAutomaticModeButton->sizeHint());

	mStopAutomaticModeButton->setEnabled(false);
	mStopAutomaticModeButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

	mAutomaticModeButtonGroup->addButton(mRunAutomaticModeButton, AutomaticModeButtonID::RunAutomaticModeButton);
	mAutomaticModeButtonGroup->addButton(mPauseAutomaticModeButton, AutomaticModeButtonID::PauseAutomaticModeButton);

	mAutomaticModeButtonGroup->addButton(mStopAutomaticModeButton, AutomaticModeButtonID::StopAutomaticModeButton);

	mFirstInstructionButton->setIcon(QIcon(QStringLiteral(":/Resources/FirstInstruction.png")));
	mFirstInstructionButton->setIconSize(mRunAutomaticModeButton->iconSize());

	//mFirstInstructionButton->setFixedSize(mRunAutomaticModeButton->sizeHint());

	mFirstInstructionButton->setEnabled(false);
	mFirstInstructionButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

	mPreviousInstructionButton->setIcon(QIcon(QStringLiteral(":/Resources/PreviousInstruction.png")));
	mPreviousInstructionButton->setIconSize(mRunAutomaticModeButton->iconSize());

	//mPreviousInstructionButton->setFixedSize(mRunAutomaticModeButton->sizeHint());

	mPreviousInstructionButton->setEnabled(false);
	mPreviousInstructionButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

	mNextInstructionButton->setIcon(QIcon(QStringLiteral(":/Resources/NextInstruction.png")));
	mNextInstructionButton->setIconSize(mRunAutomaticModeButton->iconSize());

	//mNextInstructionButton->setFixedSize(mRunAutomaticModeButton->sizeHint());

	mNextInstructionButton->setEnabled(false);
	mNextInstructionButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

	mManualModeButtonGroup->addButton(mFirstInstructionButton, ManualModeButtonID::FirstInstructionButton);
	mManualModeButtonGroup->addButton(mPreviousInstructionButton, ManualModeButtonID::PreviousInstructionButton);

	mManualModeButtonGroup->addButton(mNextInstructionButton, ManualModeButtonID::NextInstructionButton);

	mWorkModeWidgets->addWidget(createAutomaticWorkModeWidget());
	mWorkModeWidgets->addWidget(createManualWorkModeWidget());

	mAutomaticModeButton->setText("Automat");
	mAutomaticModeButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	mAutomaticModeButton->setIcon(QIcon(QStringLiteral(":/Resources/AutomaticMode.png")));
	mAutomaticModeButton->setIconSize(QSize(32, 32));
	mAutomaticModeButton->setFixedSize(QSize(66, 38));
	mAutomaticModeButton->setCheckable(true);
	mAutomaticModeButton->setChecked(true);

	mManualModeButton->setText("Manualny");
	mManualModeButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	mManualModeButton->setIcon(QIcon(QStringLiteral(":/Resources/ManualMode.png")));
	mManualModeButton->setIconSize(mAutomaticModeButton->iconSize());
	mManualModeButton->setFixedSize(mAutomaticModeButton->size());
	mManualModeButton->setCheckable(true);

	mVisualizationSettingsButton->setText("Ustawienia");
	mVisualizationSettingsButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
	mVisualizationSettingsButton->setIcon(QIcon(QStringLiteral(":/Resources/Settings.png")));
	mVisualizationSettingsButton->setIconSize(mAutomaticModeButton->iconSize());
	mVisualizationSettingsButton->setFixedSize(mAutomaticModeButton->size());

	mMenuButtonGroup->addButton(mAutomaticModeButton, MenuButtonID::AutomaticModeButton);
	mMenuButtonGroup->addButton(mManualModeButton, MenuButtonID::ManualModeButton);
	mMenuButtonGroup->addButton(mVisualizationSettingsButton, MenuButtonID::VisualizationSettingsButton);

	mIntervalSpinBox->setRange(200, 10000);
	mIntervalSpinBox->setSingleStep(200);
	mIntervalSpinBox->setSuffix(QStringLiteral("ms"));
	mIntervalSpinBox->setValue(400);

	mInstructionChanger->setRange(0, 0);
	mInstructionChanger->setButtonSymbols(QAbstractSpinBox::NoButtons);

	mTimer->setInterval(mIntervalSpinBox->value());
}

void VisualizationTaskTab::createConnections()
{
	connect(mPanelTabs->widget(PanelTabID::MainPanelTab),
		&QTableWidget::customContextMenuRequested,
		this,
		&VisualizationTaskTab::onContextMenu);

	connect(mPanelRightSideVisible,
		&QAction::toggled,
		this,
		&VisualizationTaskTab::onHidePanelRightSide);

	connect(mAutomaticModeButtonGroup,
		static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this,
		&VisualizationTaskTab::onAutomaticModeButtonClicked);

	connect(mManualModeButtonGroup,
		static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this,
		&VisualizationTaskTab::onManualModeButtonClicked);

	connect(mMenuButtonGroup,
		static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this,
		&VisualizationTaskTab::onMenuButtonClicked);

	connect(mIntervalSpinBox,
		static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		mTimer,
		static_cast<void(QTimer::*)(int)>(&QTimer::setInterval));

	connect(mTimer,
		&QTimer::timeout,
		[this](){ mManualModeButtonGroup->button(ManualModeButtonID::NextInstructionButton)->click(); });

	connect(mInstructionChanger,
		static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		[this](int value)
		{
			if(value > mLCDCurrentInstruction->value())
			{
				mLCDCurrentInstruction->display(value - 1);
				mManualModeButtonGroup->button(ManualModeButtonID::NextInstructionButton)->click();
			}
			else
			{
				mLCDCurrentInstruction->display(value == 0 ? value : value + 1);
				mManualModeButtonGroup->button(ManualModeButtonID::PreviousInstructionButton)->click();
			}
		});
}

void VisualizationTaskTab::createLayout()
{
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setSpacing(6);
	mainLayout->setContentsMargins(0, 0, 0, 0);

	QSplitter* centralSplitter = new QSplitter(Qt::Horizontal);
	centralSplitter->addWidget(mSourceCodeView);
	centralSplitter->addWidget(createRightSideWidget());

	mainLayout->addWidget(centralSplitter);

	centralSplitter->setCollapsible(1, false);
	centralSplitter->setStretchFactor(0, 1);

	setLayout(mainLayout);
}

QWidget* VisualizationTaskTab::createRightSideWidget()
{
	QSplitter* rightSideSplitter = new QSplitter(Qt::Vertical);
	rightSideSplitter->setContentsMargins(0, 0, 0, 0);
	rightSideSplitter->addWidget(mArrayView);
	rightSideSplitter->addWidget(mPanelTabs);
	rightSideSplitter->setCollapsible(0, false);
	rightSideSplitter->setStretchFactor(1, 1);

	return rightSideSplitter;
}

QWidget* VisualizationTaskTab::createMainPanelWidget()
{
	QWidget* mainPanel = new QWidget;
	mainPanel->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

	QVBoxLayout* mainPanelLayout = new QVBoxLayout(mainPanel);
	mainPanelLayout->setSpacing(6);
	mainPanelLayout->setContentsMargins(6, 6, 6, 6);

	QGridLayout* mainPanelContentLayout = new QGridLayout;

		QGroupBox* variablesViewGroupBox = new QGroupBox(QStringLiteral("Zmienne"));

		QVBoxLayout* variablesViewGroupBoxLayout = new QVBoxLayout(variablesViewGroupBox);
		variablesViewGroupBoxLayout->setSpacing(6);
		variablesViewGroupBoxLayout->setContentsMargins(10, 10, 10, 10);
		variablesViewGroupBoxLayout->addWidget(mVariablesView);

	mainPanelContentLayout->addWidget(variablesViewGroupBox, 0, 0);

		QGroupBox* workModeGroupBox = new QGroupBox(QStringLiteral("Funkcje"));

		QHBoxLayout* workModeGroupBoxLayout = new QHBoxLayout(workModeGroupBox);
		workModeGroupBoxLayout->setSpacing(6);
		workModeGroupBoxLayout->setContentsMargins(10, 10, 10, 10);
		workModeGroupBoxLayout->addWidget(mWorkModeWidgets);
		workModeGroupBoxLayout->addStretch(1);

	mainPanelContentLayout->addWidget(workModeGroupBox, 1, 0);

		QVBoxLayout* rightSideLayout = new QVBoxLayout(mPanelRightSide);
		rightSideLayout->setSpacing(6);
		rightSideLayout->setContentsMargins(0, 0, 0, 0);

			QGroupBox* progressGroupBox = new QGroupBox(QStringLiteral("Postęp"));

			QGridLayout* progressGroupBoxLayout = new QGridLayout(progressGroupBox);
			progressGroupBoxLayout->addWidget(new QLabel(QStringLiteral("Licznik instrukcji:")), 0, 0);
			progressGroupBoxLayout->addWidget(mLCDCurrentInstruction, 0, 1);
			progressGroupBoxLayout->addWidget(new QLabel(QStringLiteral(":")), 0, 2, Qt::AlignHCenter);
			progressGroupBoxLayout->addWidget(mLCDInstructionCounter, 0, 3);
			progressGroupBoxLayout->addWidget(new QLabel(QStringLiteral("Licznik porównań:")), 1, 0);
			progressGroupBoxLayout->addWidget(mLCDCompareCounter, 1, 1);
			progressGroupBoxLayout->addWidget(createColorBoxFrame(mLCDCompareCounter->sizeHint().height(), Qt::white), 1, 3);
			progressGroupBoxLayout->addWidget(new QLabel(QStringLiteral("Licznik zamian:")), 2, 0);
			progressGroupBoxLayout->addWidget(mLCDSwapCounter, 2, 1);
			progressGroupBoxLayout->addWidget(createColorBoxFrame(mLCDSwapCounter->sizeHint().height(), Qt::red), 2, 3);

		rightSideLayout->addWidget(progressGroupBox);

			QGroupBox* menuGroupBox = new QGroupBox(QStringLiteral("Menu"));

			QHBoxLayout* menuGroupBoxLayout = new QHBoxLayout(menuGroupBox);
			menuGroupBoxLayout->setSpacing(6);
			menuGroupBoxLayout->setContentsMargins(10, 10, 10, 10);
			menuGroupBoxLayout->addWidget(mAutomaticModeButton);
			menuGroupBoxLayout->addWidget(mManualModeButton);
			menuGroupBoxLayout->addWidget(mVisualizationSettingsButton);

		rightSideLayout->addWidget(menuGroupBox);
		rightSideLayout->addStretch(1);

	mainPanelContentLayout->addWidget(mPanelRightSide, 0, 1, 2, 1);

	mainPanelLayout->addLayout(mainPanelContentLayout);
	mainPanelLayout->addStretch(1);

	return mainPanel;
}

QWidget* VisualizationTaskTab::createAutomaticWorkModeWidget()
{
	QWidget* automaticWorkMode = new QWidget;

	QHBoxLayout* automaticWorkModeLayout = new QHBoxLayout(automaticWorkMode);
	automaticWorkModeLayout->setSpacing(6);
	automaticWorkModeLayout->setContentsMargins(0, 0, 0, 0);

		QGridLayout* contentAutomaticWorkModeGridLayout = new QGridLayout;
		contentAutomaticWorkModeGridLayout->addWidget(mRunAutomaticModeButton, 0, 0);
		contentAutomaticWorkModeGridLayout->addWidget(mPauseAutomaticModeButton, 0, 1);
		contentAutomaticWorkModeGridLayout->addWidget(mStopAutomaticModeButton, 0, 2);
		contentAutomaticWorkModeGridLayout->addWidget(new QLabel(QStringLiteral("Przeskok instrukcji:")), 1, 0, 1, 2, Qt::AlignRight);
		contentAutomaticWorkModeGridLayout->addWidget(mIntervalSpinBox, 1, 2);

	automaticWorkModeLayout->addLayout(contentAutomaticWorkModeGridLayout);
	automaticWorkModeLayout->addStretch(1);

	return automaticWorkMode;
}

QWidget* VisualizationTaskTab::createManualWorkModeWidget()
{
	QWidget* manualWorkMode = new QWidget;

	QHBoxLayout* manualWorkModeLayout = new QHBoxLayout(manualWorkMode);
	manualWorkModeLayout->setSpacing(6);
	manualWorkModeLayout->setContentsMargins(0, 0, 0, 0);

		QGridLayout* contentManualWorkModeGridLayout = new QGridLayout;
		contentManualWorkModeGridLayout->addWidget(mFirstInstructionButton, 0, 0);
		contentManualWorkModeGridLayout->addWidget(mPreviousInstructionButton, 0, 1);
		contentManualWorkModeGridLayout->addWidget(mNextInstructionButton, 0, 2);
		contentManualWorkModeGridLayout->addWidget(new QLabel(QStringLiteral("Skocz do instrukcji:")), 1, 0, 1, 2, Qt::AlignRight);
		contentManualWorkModeGridLayout->addWidget(mInstructionChanger, 1, 2);

	manualWorkModeLayout->addLayout(contentManualWorkModeGridLayout);
	manualWorkModeLayout->addStretch(1);

	return manualWorkMode;
}

QWidget* VisualizationTaskTab::createColorBoxFrame(int length, const QColor& color)
{
	QFrame* boxFrame = new QFrame;
	boxFrame->setFrameShape(QFrame::Box);
	boxFrame->setFixedSize(length, length);
	boxFrame->setPalette(QPalette(color));
	boxFrame->setAutoFillBackground(true);

	return boxFrame;
}

void VisualizationTaskTab::openVisualizationSettings()
{
	mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->setEnabled(true);
	mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->click();

	SettingsWindow* settingsWindow = new SettingsWindow(mSettings);

	connect(settingsWindow,
		&SettingsWindow::sortingAlgorithmsChanged,
		this,
		&VisualizationTaskTab::onSetSourceCode);

	connect(settingsWindow,
		&SettingsWindow::arraySizeChanged,
		mArrayView,
		&ArrayView::onSetArraySize);

	connect(settingsWindow,
		&SettingsWindow::arrayBlockValueChanged,
		mArrayView,
		&ArrayView::onSetArrayBlockValue);

	connect(settingsWindow,
		&SettingsWindow::parametersSaved,
		this,
		&VisualizationTaskTab::onPrepareVisualizationTask);

	settingsWindow->exec();

	refreshViews();

	mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->setEnabled(true);
	mAutomaticModeButtonGroup->button(AutomaticModeButtonID::StopAutomaticModeButton)->click();
}

void VisualizationTaskTab::refreshViews()
{
	onSetSourceCode(mSettings.mSortingAlgorithm);

	mArrayView->onSetArraySize(mSettings.mArray.size());
	mArrayView->onSetArrayBlockValues(mSettings.mArray);
}

void VisualizationTaskTab::onContextMenu(const QPoint&)
{
	mPanelMenu->exec(QCursor::pos());
}

void VisualizationTaskTab::onHidePanelRightSide(bool hide)
{
	mPanelRightSide->setHidden(hide);
}
