#ifndef INFORMATIONWINDOW_HPP
#define INFORMATIONWINDOW_HPP

#include <QDialog>

class QLabel;

class InformationWindow : public QDialog
{
	Q_OBJECT

public:
	InformationWindow();

private:
	void createWidgets();
	void createLayout();

	QLabel* mIconLabel;
	QLabel* mMainTitleLabel;
	QLabel* mInformationLabel;
};

#endif // INFORMATIONWINDOW_HPP
