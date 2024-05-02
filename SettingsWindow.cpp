#include "SettingsWindow.hpp"

#include <QDialogButtonBox>
#include <QTabWidget>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QToolButton>
#include <QButtonGroup>
#include <QCheckBox>
#include <QGroupBox>
#include <QAbstractButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>


SettingsWindow::SettingsWindow(Settings& externalSettings) :
	QDialog{nullptr, Qt::MSWindowsFixedSizeDialogHint},
	mExternalSettings{externalSettings},
	mButtonBox{new QDialogButtonBox},
	mSettingsTabs{new QTabWidget},
	mSortingAlogorithmsComboBox{new QComboBox},
	mInputDataSizeSpinBox{new QSpinBox},
	mZeroArrayValuesButton{new QToolButton},
	mGenerateAscendingArrayValuesButton{new QToolButton},
	mGenerateRandomArrayValuesButton{new QToolButton},
	mGenerateDescendingArrayValuesButton{new QToolButton},
	mGenerateButtonGroup{new QButtonGroup},
	mRepeatedValuesCheckBox{new QCheckBox}

{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(QStringLiteral("Ustawienia aplikacji"));
	setWindowIcon(QIcon(QStringLiteral(":/Resources/Settings.png")));
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setContextMenuPolicy(Qt::NoContextMenu);

	createWidgets();
	createConnections();
	createLayout();

	resetParameters();
}

void SettingsWindow::createWidgets()
{
	mButtonBox->addButton(QDialogButtonBox::StandardButton::Ok);
	mButtonBox->addButton(QDialogButtonBox::StandardButton::Cancel);
	mButtonBox->addButton(QDialogButtonBox::StandardButton::Reset);

	mSettingsTabs->addTab(createGeneralSettingsWidget(), QStringLiteral("Ogólne"));

	mSortingAlogorithmsComboBox->addItem(QStringLiteral("Sortowanie przez wstawianie"), QVariant::fromValue(SortingAlgorithmType::InsertionSort));
	mSortingAlogorithmsComboBox->addItem(QStringLiteral("Sortowanie przez wybieranie"), QVariant::fromValue(SortingAlgorithmType::SelectionSort));
	mSortingAlogorithmsComboBox->addItem(QStringLiteral("Sortowanie bąbelkowe"), QVariant::fromValue(SortingAlgorithmType::BubbleSort));
	mSortingAlogorithmsComboBox->addItem(QStringLiteral("Sortowanie przez scalanie"), QVariant::fromValue(SortingAlgorithmType::MergeSort));
	mSortingAlogorithmsComboBox->addItem(QStringLiteral("Sortowanie przez kopcowanie"), QVariant::fromValue(SortingAlgorithmType::HeapSort));
	mSortingAlogorithmsComboBox->addItem(QStringLiteral("Sortowanie szybkie (Lomuto)"), QVariant::fromValue(SortingAlgorithmType::QuickSortLomuto));
	mSortingAlogorithmsComboBox->addItem(QStringLiteral("Sortowanie szybkie (Hoare)"), QVariant::fromValue(SortingAlgorithmType::QuickSortHoare));

	mSortingAlogorithmsComboBox->setCurrentIndex(-1);

	mInputDataSizeSpinBox->setRange(2, Settings::ArrayFixedSize);
	mInputDataSizeSpinBox->setValue(2);

	mZeroArrayValuesButton->setText(QStringLiteral("Wyzeruj elementy"));
	mZeroArrayValuesButton->setFixedHeight(23);

	mGenerateAscendingArrayValuesButton->setText("Kolejność rosnąca");
	mGenerateAscendingArrayValuesButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	mGenerateAscendingArrayValuesButton->setIcon(QIcon(":/Resources/Ascending.png"));
	mGenerateAscendingArrayValuesButton->setIconSize(QSize(68, 24));
	mGenerateAscendingArrayValuesButton->setFixedSize(mGenerateAscendingArrayValuesButton->sizeHint());

	mGenerateRandomArrayValuesButton->setText("Kolejność losowa");
	mGenerateRandomArrayValuesButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	mGenerateRandomArrayValuesButton->setIcon(QIcon(":/Resources/Random.png"));
	mGenerateRandomArrayValuesButton->setIconSize(QSize(68, 24));
	mGenerateRandomArrayValuesButton->setFixedSize(mGenerateAscendingArrayValuesButton->sizeHint());

	mGenerateDescendingArrayValuesButton->setText("Kolejność malejąca");
	mGenerateDescendingArrayValuesButton->setToolTip("Wygeneruje dla wszystkich elementów wartości w kolejności malejącej");
	mGenerateDescendingArrayValuesButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	mGenerateDescendingArrayValuesButton->setIcon(QIcon(":/Resources/Descending.png"));
	mGenerateDescendingArrayValuesButton->setIconSize(QSize(68, 24));
	mGenerateDescendingArrayValuesButton->setFixedSize(mGenerateAscendingArrayValuesButton->sizeHint());

	mGenerateButtonGroup->addButton(mZeroArrayValuesButton, GenerateButtonID::ZeroArrayValuesButton);
	mGenerateButtonGroup->addButton(mGenerateAscendingArrayValuesButton, GenerateButtonID::AscendingArrayValuesButton);
	mGenerateButtonGroup->addButton(mGenerateRandomArrayValuesButton, GenerateButtonID::RandomArrayValuesButton);
	mGenerateButtonGroup->addButton(mGenerateDescendingArrayValuesButton, GenerateButtonID::DescendingArrayValuesButton);

	mRepeatedValuesCheckBox->setText(QStringLiteral("Powtarzające się wartości"));
	mRepeatedValuesCheckBox->setChecked(true);
	mRepeatedValuesCheckBox->setToolTip("Możliwe wystąpienie identycznych wartości podczas losowego generowania");
}

void SettingsWindow::createConnections()
{
	connect(mButtonBox,
		&QDialogButtonBox::clicked,
		this,
		&SettingsWindow::onButtonClicked);

	connect(mSortingAlogorithmsComboBox,
		static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		this,
		&SettingsWindow::onSortingAlgorithmsChanged);

	connect(mInputDataSizeSpinBox,
		static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this,
		&SettingsWindow::onArraySizeChanged);

	connect(mGenerateButtonGroup,
		static_cast<void(QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		this,
		&SettingsWindow::onGenerateButtonClicked);
}

void SettingsWindow::createLayout()
{
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setSpacing(6);
	mainLayout->setContentsMargins(10, 10, 10, 10);
	mainLayout->addWidget(mSettingsTabs);
	mainLayout->addWidget(mButtonBox);

	setLayout(mainLayout);
}

QWidget* SettingsWindow::createGeneralSettingsWidget()
{
	QWidget* generalSettings = new QWidget;

	QVBoxLayout* generalSettingsLayout = new QVBoxLayout(generalSettings);
	generalSettingsLayout->setSpacing(6);
	generalSettingsLayout->setContentsMargins(10, 10, 10, 10);

		QGroupBox* sortingAlgorithmsGroupBox = new QGroupBox(QStringLiteral("Algorytm sortowania"));
		QVBoxLayout* sortingAlgorithmsGroupBoxLayout = new QVBoxLayout(sortingAlgorithmsGroupBox);

		sortingAlgorithmsGroupBoxLayout->setSpacing(6);
		sortingAlgorithmsGroupBoxLayout->setContentsMargins(10, 10, 10, 10);

			QHBoxLayout* sortingAlgorithmsContentLayout = new QHBoxLayout;
			sortingAlgorithmsContentLayout->setSpacing(6);
			sortingAlgorithmsContentLayout->addWidget(new QLabel(QStringLiteral("Nazwa:")));
			sortingAlgorithmsContentLayout->addWidget(mSortingAlogorithmsComboBox);
			sortingAlgorithmsContentLayout->addStretch(1);

		sortingAlgorithmsGroupBoxLayout->addLayout(sortingAlgorithmsContentLayout);

	generalSettingsLayout->addWidget(sortingAlgorithmsGroupBox);

		QGroupBox* inputDataGroupBox = new QGroupBox(QStringLiteral("Dane wejściowe"));

		QVBoxLayout* inputDataGroupBoxLayout = new QVBoxLayout(inputDataGroupBox);
		inputDataGroupBoxLayout->setSpacing(6);
		inputDataGroupBoxLayout->setContentsMargins(10, 10, 10, 10);

			QHBoxLayout* inputDataSizeLayout = new QHBoxLayout;
			inputDataSizeLayout->setSpacing(6);
			inputDataSizeLayout->addWidget(new QLabel(QStringLiteral("Rozmiar:")));
			inputDataSizeLayout->addWidget(mInputDataSizeSpinBox);
			inputDataSizeLayout->addStretch(1);
			inputDataSizeLayout->addWidget(mZeroArrayValuesButton);

		inputDataGroupBoxLayout->addLayout(inputDataSizeLayout);
		inputDataGroupBoxLayout->addWidget(createArrayWidget());

			QGroupBox* inputDataGeneratorGroupBox = new QGroupBox(QStringLiteral("Generator"));
			QVBoxLayout* inputDataGeneratorGroupBoxLayout = new QVBoxLayout(inputDataGeneratorGroupBox);

			inputDataGeneratorGroupBoxLayout->setSpacing(6);
			inputDataGeneratorGroupBoxLayout->setContentsMargins(10, 10, 10, 10);

				QHBoxLayout* inputDataGeneratorContentLayout = new QHBoxLayout;
				inputDataGeneratorContentLayout->setSpacing(6);
				inputDataGeneratorContentLayout->addWidget(mGenerateAscendingArrayValuesButton);
				inputDataGeneratorContentLayout->addWidget(mGenerateRandomArrayValuesButton);
				inputDataGeneratorContentLayout->addWidget(mGenerateDescendingArrayValuesButton);

			inputDataGeneratorGroupBoxLayout->addLayout(inputDataGeneratorContentLayout);
			inputDataGeneratorGroupBoxLayout->addWidget(mRepeatedValuesCheckBox);

		inputDataGroupBoxLayout->addWidget(inputDataGeneratorGroupBox);

	generalSettingsLayout->addWidget(inputDataGroupBox);

	return generalSettings;
}

QWidget* SettingsWindow::createArrayWidget()
{
	QGroupBox* arrayGroupBox = new QGroupBox(QStringLiteral("Tablica"));
	QGridLayout* arrayGroupBoxLayout = new QGridLayout(arrayGroupBox);

	arrayGroupBoxLayout->setSpacing(6);

	for(int i = 0; i < Settings::ArrayFixedSize; ++i)
	{
		QSpinBox* blockSpinBox = new QSpinBox;
		blockSpinBox->setRange(0, Settings::ArrayMaximumValue);
		blockSpinBox->setValue(0);

		QLabel* blockIndexLabel = new QLabel(QStringLiteral("[ ") + QString::number(i) + QStringLiteral(" ]"));
		blockIndexLabel->setAlignment(Qt::AlignCenter);

		arrayGroupBoxLayout->addWidget(blockSpinBox, 0, i);
		arrayGroupBoxLayout->addWidget(blockIndexLabel, 1, i);

		mArray.push_back(qMakePair(blockSpinBox, blockIndexLabel));

		connect(blockSpinBox,
			static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
			[this, i](int value){ emit arrayBlockValueChanged(i, value); });
	}

	return arrayGroupBox;
}

void SettingsWindow::zeroArrayValues()
{
	for(int i = 0; i < mInputDataSizeSpinBox->value(); ++i)
		mArray.at(i).first->setValue(0);
}

void SettingsWindow::generateAscendingArrayValues()
{
	for(int i = 0; i < mInputDataSizeSpinBox->value(); ++i)
		mArray.at(i).first->setValue(i + 1);
}

void SettingsWindow::generateRandomArrayValues()
{
	const int arraySize = mInputDataSizeSpinBox->value();

	if(mRepeatedValuesCheckBox->isChecked())
	{
		for(int i = 0; i < arraySize; ++i)
			mArray.at(i).first->setValue(qrand() % Settings::ArrayMaximumValue + 1);
	}
	else
	{
		QVector<int> randomValues(arraySize);

		for(int i = 0; i < arraySize; ++i)
			randomValues[i] = i + 1;

		for(int i = arraySize; i > 1; --i)
			qSwap(randomValues[i - 1], randomValues[qrand() % i]);

		for(int i = 0; i < arraySize; ++i)
			mArray.at(i).first->setValue(randomValues.at(i));
	}
}

void SettingsWindow::generateDescendingArrayValues()
{
	for(int i = mInputDataSizeSpinBox->value() - 1; i >= 0 ; --i)
		mArray.at(i).first->setValue(mInputDataSizeSpinBox->value() - i);
}

bool SettingsWindow::saveParameters()
{
	if(isParametersChanged())
	{
		mExternalSettings.mSortingAlgorithm = mSortingAlogorithmsComboBox->itemData(mSortingAlogorithmsComboBox->currentIndex()).value<SortingAlgorithmType>();
		mExternalSettings.mArray.clear();

		for(int i = 0; i < mInputDataSizeSpinBox->value(); ++i)
			mExternalSettings.mArray.push_back(mArray.at(i).first->value());

		mExternalSettings.mRepeatedValues = mRepeatedValuesCheckBox->isChecked();

		emit parametersSaved();

		return true;
	}

	return false;
}

bool SettingsWindow::isParametersChanged()
{
	if(mSortingAlogorithmsComboBox->itemData(mSortingAlogorithmsComboBox->currentIndex()).value<SortingAlgorithmType>() != mExternalSettings.mSortingAlgorithm)
		return true;

	if(mInputDataSizeSpinBox->value() != mExternalSettings.mArray.size())
		return true;

	for(int i = 0; i < mInputDataSizeSpinBox->value(); ++i)
	{
		if(mArray.at(i).first->value() != mExternalSettings.mArray.at(i))
			return true;
	}

	if(mRepeatedValuesCheckBox->isChecked() != mExternalSettings.mRepeatedValues)
		return true;

	return false;
}

void SettingsWindow::resetParameters()
{
	if(isParametersChanged())
	{
		mSortingAlogorithmsComboBox->setCurrentIndex(static_cast<int>(mExternalSettings.mSortingAlgorithm));
		mInputDataSizeSpinBox->setValue(mExternalSettings.mArray.size());
		mRepeatedValuesCheckBox->setChecked(mExternalSettings.mRepeatedValues);

		for(int i = 0; i < mExternalSettings.mArray.size(); ++i)
			mArray.at(i).first->setValue(mExternalSettings.mArray.at(i));
	}
}

void SettingsWindow::onButtonClicked(QAbstractButton* button)
{
	switch(mButtonBox->standardButton(button))
	{
		case QDialogButtonBox::StandardButton::Ok:
		{
			if(saveParameters())
			{
				accept();
			}
			else
			{
				reject();
			}

			break;
		}
		case QDialogButtonBox::StandardButton::Cancel:
		{
			reject();

			break;
		}
		case QDialogButtonBox::StandardButton::Reset:
		{
			resetParameters();

			break;
		}
		default:
		{
			break;
		}
	}
}

void SettingsWindow::onSortingAlgorithmsChanged(int index)
{
	emit sortingAlgorithmsChanged(mSortingAlogorithmsComboBox->itemData(index).value<SortingAlgorithmType>());
}

void SettingsWindow::onArraySizeChanged(int size)
{
	for(int i = 0; i < mArray.size(); ++i)
	{
		if(i < mInputDataSizeSpinBox->value())
		{
			mArray.at(i).first->setEnabled(true);
		}
		else
		{
			mArray.at(i).first->setEnabled(false);

			mArray.at(i).first->setValue(0);
		}
	}

	emit arraySizeChanged(size);
}

void SettingsWindow::onGenerateButtonClicked(int buttonID)
{
	switch(buttonID)
	{
		case GenerateButtonID::ZeroArrayValuesButton:
		{
			zeroArrayValues();

			break;
		}
		case GenerateButtonID::AscendingArrayValuesButton:
		{
			generateAscendingArrayValues();

			break;
		}
		case GenerateButtonID::RandomArrayValuesButton:
		{
			generateRandomArrayValues();

			break;
		}
		case GenerateButtonID::DescendingArrayValuesButton:
		{
			generateDescendingArrayValues();

			break;
		}
	}
}
