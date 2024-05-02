#ifndef EXPERIMENTALRESEARCHTASKTAB_HPP
#define EXPERIMENTALRESEARCHTASKTAB_HPP

#include <QWidget>

#include "SortingAlgorithm.hpp"

class QComboBox;
class QSpinBox;
class QPushButton;
class QCheckBox;
class QTextEdit;

class ExperimentalResearchTaskTab : public QWidget
{
	Q_OBJECT

	friend class MainWindow;

public:
	explicit ExperimentalResearchTaskTab(QWidget* parent = nullptr);

private slots:
	void onSortCommandButtonClicked();

private:
	void createWidgets();
	void createConnections();
	void createLayout();
	void initializeSortingAlgorithms();
	void generateToMaxValues(QVector<int>& data);
	void generateToMinValues(QVector<int>& data);
	void generateRandomValues(QVector<int>& data);

	QComboBox* mSortTypeComboBox;
	QSpinBox* mElementsCountSpinBox;
	QPushButton* mSortCommandButton;
	QCheckBox* mFormatResultsCheckBox;
	QTextEdit* mLogTextEdit;
	QList<SortingAlgorithm::Ptr> mSortingAlgorithms;
};

#endif // EXPERIMENTALRESEARCHTASKTAB_HPP
