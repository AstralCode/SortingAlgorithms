#include "VariablesView.hpp"

#include <QHeaderView>

#include "VariableInformation.hpp"

VariablesView::VariablesView(QWidget* parent) :
	QTableWidget{parent}
{
	setContextMenuPolicy(Qt::CustomContextMenu);
	setWordWrap(false);
	setCornerButtonEnabled(false);
	setFocusPolicy(Qt::NoFocus);
	setSelectionMode(QAbstractItemView::NoSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	horizontalHeader()->setVisible(false);
	horizontalHeader()->setMinimumSectionSize(40);
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	verticalHeader()->setVisible(false);
	verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	setFixedHeight(80);
}

void VariablesView::setVariableInformation(const QList<VariableInformation>& variableInformationList)
{
	auto addInformation = [](const QString& info, const QColor& backgroundColor, Qt::AlignmentFlag align)->QTableWidgetItem*
	{
		const QFont ItemFont("Courier New", 16, QFont::Normal);

		QTableWidgetItem* item = new QTableWidgetItem(info);
		item->setTextAlignment(align);
		item->setFont(ItemFont);
		item->setBackground(QBrush(backgroundColor));

		return item;
	};

	setRowCount(3);
	setColumnCount(0);

	for(const VariableInformation& variableInformation : variableInformationList)
	{
		insertColumn(columnCount());

		setItem(0, columnCount() - 1, addInformation(variableInformation.mName, Qt::transparent, Qt::AlignCenter));
		setItem(1, columnCount() - 1, addInformation(QStringLiteral(""), Qt::transparent, Qt::AlignCenter));
		setItem(2, columnCount() - 1, addInformation(QStringLiteral(""), variableInformation.mColor, Qt::AlignCenter));
	}
}

void VariablesView::setVariables(const QVector<QPair<QString, QString>>& variables)
{
	for(int j = 0; j < variables.size(); ++j)
	{
		for(int i = 0; i < columnCount(); ++i)
		{
			if(item(0, i)->text() == variables.at(j).first)
				item(1, i)->setText(variables.at(j).second);
		}
	}
}
