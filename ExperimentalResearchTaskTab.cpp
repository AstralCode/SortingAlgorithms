#include "ExperimentalResearchTaskTab.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QTextEdit>

#include "SortingAlgorithms.hpp"


ExperimentalResearchTaskTab::ExperimentalResearchTaskTab(QWidget* parent) :
	QWidget{parent},
	mSortTypeComboBox{new QComboBox},
	mElementsCountSpinBox{new QSpinBox},
	mSortCommandButton{new QPushButton},
	mFormatResultsCheckBox{new QCheckBox},
	mLogTextEdit{new QTextEdit}
{
	setContextMenuPolicy(Qt::NoContextMenu);

	createWidgets();
	createConnections();
	createLayout();

	initializeSortingAlgorithms();
}

void ExperimentalResearchTaskTab::onSortCommandButtonClicked()
{
	mSortCommandButton->setEnabled(false);
	mSortTypeComboBox->setEnabled(false);
	mLogTextEdit->clear();

	QVector<int> data(mElementsCountSpinBox->value());

	switch (mSortTypeComboBox->currentIndex())
	{
		case 0:
			generateRandomValues(data);
		break;
		case 1:
			generateToMaxValues(data);
		break;
		case 2:
			generateToMinValues(data);
		break;
	}

	int swapCounter, compareCounter, instructionCounter;

	for (auto sortingAlgorithm : mSortingAlgorithms)
	{
		swapCounter = compareCounter = instructionCounter = 0;
		sortingAlgorithm->run(data, swapCounter, compareCounter, instructionCounter);

		const QString result = mFormatResultsCheckBox->isChecked() ?
					QString("%1:\n\tLiczba zamian: %2\n\tLiczba porównań: %3\n\tLiczba instrukcji: %4").arg(sortingAlgorithm->getName()).arg(swapCounter).arg(compareCounter).arg(instructionCounter)
				  : QString("%1, %2, %3").arg(swapCounter).arg(compareCounter).arg(instructionCounter) ;
		mLogTextEdit->append(result);
	}

	mSortCommandButton->setEnabled(true);
	mSortTypeComboBox->setEnabled(true);
}

void ExperimentalResearchTaskTab::initializeSortingAlgorithms()
{
	mSortingAlgorithms.push_back(QSharedPointer<SortingAlgorithm>(new InsertionSort));
	mSortingAlgorithms.push_back(QSharedPointer<SortingAlgorithm>{new SelectionSort});
	mSortingAlgorithms.push_back(QSharedPointer<SortingAlgorithm>{new BubbleSort});
	mSortingAlgorithms.push_back(QSharedPointer<SortingAlgorithm>{new MergeSort});
	mSortingAlgorithms.push_back(QSharedPointer<SortingAlgorithm>{new HeapSort});
	mSortingAlgorithms.push_back(QSharedPointer<SortingAlgorithm>{new QuickSortLomuto});
	mSortingAlgorithms.push_back(QSharedPointer<SortingAlgorithm>{new QuickSortHoare});
}

void ExperimentalResearchTaskTab::generateToMaxValues(QVector<int>& data)
{
	std::iota(data.begin(), data.end(), 1);
}

void ExperimentalResearchTaskTab::generateToMinValues(QVector<int>& data)
{
	for (int i = 0; i < data.size(); ++i)
		data[i] = data.size() - i;
}

void ExperimentalResearchTaskTab::generateRandomValues(QVector<int>& data)
{
	std::generate(data.begin(), data.end(), []() -> int
	{
		return qrand() % 10000;
	});
}

void ExperimentalResearchTaskTab::createWidgets()
{
	mSortTypeComboBox->addItem(QStringLiteral("Ułożone losowo"));
	mSortTypeComboBox->addItem(QStringLiteral("Posortowane rosnąco"));
	mSortTypeComboBox->addItem(QStringLiteral("Posortowane malejąco"));
	mSortTypeComboBox->setCurrentIndex(0);

	mElementsCountSpinBox->setRange(2, 100000);
	mElementsCountSpinBox->setSingleStep(1);
	mElementsCountSpinBox->setSuffix(QStringLiteral(" elementów"));
	mElementsCountSpinBox->setValue(10);

	mSortCommandButton->setText(QStringLiteral("Sortuj"));

	mFormatResultsCheckBox->setText(QStringLiteral("Formatuj wyniki"));
	mFormatResultsCheckBox->setChecked(true);
}

void ExperimentalResearchTaskTab::createConnections()
{
	connect(mSortCommandButton, &QPushButton::clicked,
			this, &ExperimentalResearchTaskTab::onSortCommandButtonClicked);
}

void ExperimentalResearchTaskTab::createLayout()
{
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setSpacing(6);

	QGroupBox* topWidgetsGroupBox = new QGroupBox{QStringLiteral("Ustawienia")};
	QVBoxLayout* topWidgetsLayout = new QVBoxLayout{topWidgetsGroupBox};
	topWidgetsLayout->setSpacing(6);
	topWidgetsLayout->setContentsMargins(10, 10, 10, 10);

	QHBoxLayout* topUpWidgetsLayout = new QHBoxLayout;
	topUpWidgetsLayout->addWidget(mSortTypeComboBox);
	topUpWidgetsLayout->addWidget(mElementsCountSpinBox);
	topUpWidgetsLayout->addWidget(mSortCommandButton);
	topUpWidgetsLayout->addStretch(1);

	QHBoxLayout* topDownWidgetsLayout = new QHBoxLayout;
	topDownWidgetsLayout->addWidget(mFormatResultsCheckBox);
	topDownWidgetsLayout->addStretch(1);

	topWidgetsLayout->addLayout(topUpWidgetsLayout);
	topWidgetsLayout->addLayout(topDownWidgetsLayout);

	mainLayout->addWidget(topWidgetsGroupBox);
	mainLayout->addWidget(mLogTextEdit);

	setLayout(mainLayout);
}

