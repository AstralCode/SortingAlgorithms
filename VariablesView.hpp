#ifndef VARIABLESVIEW_HPP
#define VARIABLESVIEW_HPP

#include <QTableWidget>

class VariableInformation;

class VariablesView : public QTableWidget
{
	Q_OBJECT

public:
	explicit VariablesView(QWidget* parent = nullptr);

	void setVariableInformation(const QList<VariableInformation>& variableInformationList);
	void setVariables(const QVector<QPair<QString, QString>>& variables);
};

#endif // VARIABLESVIEW_HPP
