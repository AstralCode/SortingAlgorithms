#ifndef VARIABLEINFORMATION_HPP
#define VARIABLEINFORMATION_HPP

#include <QString>
#include <QColor>

class VariableInformation
{
public:
	VariableInformation(const QString& name, const QColor& color);

	QString mName;
	QColor mColor;
};

#endif // VARIABLEINFORMATION_HPP
