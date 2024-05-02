#ifndef SETTINGSWINDOW_HPP
#define SETTINGSWINDOW_HPP

#include <QDialog>

#include "Settings.hpp"

class QDialogButtonBox;
class QTabWidget;
class QComboBox;
class QSpinBox;
class QLabel;
class QToolButton;
class QButtonGroup;
class QCheckBox;
class QAbstractButton;

class SettingsWindow : public QDialog
{
	Q_OBJECT

	enum GenerateButtonID
	{
		ZeroArrayValuesButton,
		AscendingArrayValuesButton,
		RandomArrayValuesButton,
		DescendingArrayValuesButton
	};

public:
	SettingsWindow(Settings& externalSettings);

	void resetParameters();

signals:
	void sortingAlgorithmsChanged(SortingAlgorithmType);
	void arraySizeChanged(int);
	void arrayBlockValueChanged(int, int);
	void parametersSaved();

private:
	void createWidgets();
	void createConnections();
	void createLayout();
	QWidget* createGeneralSettingsWidget();
	QWidget* createArrayWidget();
	void zeroArrayValues();
	void generateAscendingArrayValues();
	void generateRandomArrayValues();
	void generateDescendingArrayValues();
	bool saveParameters();
	bool isParametersChanged();

private slots:
	void onButtonClicked(QAbstractButton* button);
	void onSortingAlgorithmsChanged(int index);
	void onArraySizeChanged(int size);
	void onGenerateButtonClicked(int buttonID);

private:
	Settings& mExternalSettings;
	QDialogButtonBox* mButtonBox;
	QTabWidget* mSettingsTabs;
	QComboBox* mSortingAlogorithmsComboBox;
	QSpinBox* mInputDataSizeSpinBox;
	QToolButton* mZeroArrayValuesButton;
	QToolButton* mGenerateAscendingArrayValuesButton;
	QToolButton* mGenerateRandomArrayValuesButton;
	QToolButton* mGenerateDescendingArrayValuesButton;
	QButtonGroup* mGenerateButtonGroup;
	QCheckBox* mRepeatedValuesCheckBox;
	QVector<QPair<QSpinBox*, QLabel*>>	mArray;
};

#endif // SETTINGSWINDOW_HPP
