#include "SourceCodeView.hpp"

#include <QHeaderView>
#include <QMenu>
#include <QAction>
#include <QComboBox>
#include <QWidgetAction>

#include "SourceLine.hpp"


SourceCodeView::SourceCodeView(QWidget* parent) :
	QTableWidget{parent},
	mSourceCodeIndentSize{4},
	mSourceCodeFont{QFont{QStringLiteral("Courier New"), 9, QFont::Normal}},
	mCurrentSourceCode{0},
	mCurrentHighlightLine{0},
	mSourceCode{0},
	mLineNumbersAction{new QAction{this}},
	mSourceCodeMenu{new QMenu{this}},
	mSourceCodeFontSizeComboBox{new QComboBox},
	mSourceCodeIndentSizeComboBox{new QComboBox}
{
	createActions();
	createConnections();

	setContextMenuPolicy(Qt::CustomContextMenu);
	setMinimumWidth(200);
	setShowGrid(false);
	setWordWrap(false);
	setCornerButtonEnabled(false);
	setFocusPolicy(Qt::NoFocus);
	setSelectionMode(QAbstractItemView::NoSelection);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setColumnCount(1);
	setHorizontalHeaderItem(0, new QTableWidgetItem(QStringLiteral("")));

	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	horizontalHeader()->setSectionsClickable(false);
	horizontalHeader()->setStretchLastSection(true);
	horizontalHeader()->setStyleSheet(QStringLiteral(
		R"(QHeaderView{font-family: "Courier New"; font-weight: bold;})"
	));

	verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	verticalHeader()->setSectionsClickable(false);
	verticalHeader()->setDefaultAlignment(Qt::AlignRight);
	verticalHeader()->setStyleSheet(QStringLiteral(
		R"(QHeaderView{font-family: "Courier New"; font-weight: bold; font-size: 12pt;})"
	));
}

void SourceCodeView::setSourceCode(const QString& caption, const QVector<QList<SourceLine>>& sourceCode)
{
	horizontalHeaderItem(0)->setText(caption);
	mSourceCode = &sourceCode;
	setCurrentSourceCode(0);
}

void SourceCodeView::setCurrentSourceCode(int index)
{
	if(index >= 0 && index < mSourceCode->size())
	{
		mCurrentSourceCode = index;

		setRowCount(0);

		for(const SourceLine& sourceLine : mSourceCode->at(index))
		{
			insertRow(rowCount());

			QTableWidgetItem* item = new QTableWidgetItem;
			item->setFont(mSourceCodeFont);
			item->setBackground(QColor(255, 255, 230));
			item->setText(QString(mSourceCodeIndentSize * sourceLine.getIndentSize(), QChar::Space) + sourceLine);

			setItem(rowCount() - 1, 0, item);
		}
	}
}

int SourceCodeView::getSourceCodeFontSize() const
{
	return mSourceCodeFont.pointSize();
}

int SourceCodeView::getSourceCodeIndentSize() const
{
	return mSourceCodeIndentSize;
}

int SourceCodeView::getCurrentHighlightLine() const
{
	return mCurrentHighlightLine;
}

void SourceCodeView::onSetSourceCodeIndentSize(int indentSize)
{
	if(mSourceCodeIndentSize != indentSize)
	{
		mSourceCodeIndentSize = indentSize;

		if(mSourceCode)
		{
			int i = 0;

			for(const SourceLine& sourceLine : mSourceCode->at(mCurrentSourceCode))
				item(i++, 0)->setText(QString(mSourceCodeIndentSize * sourceLine.getIndentSize(), QChar::Space) + sourceLine);
		}
	}
}

void SourceCodeView::onSetSourceCodeIndentSize(const QString& size)
{
	onSetSourceCodeIndentSize(size.toInt());
}

void SourceCodeView::onSetSourceCodeFontSize(int size)
{
	if(mSourceCodeFont.pointSize() != size)
	{
		mSourceCodeFont.setPointSize(size);

		for(int i = 0; i < rowCount(); ++i)
		{
			if(item(i, 0)->font().bold())
			{
				item(i, 0)->setFont(mSourceCodeFont);

				QFont boldFont(mSourceCodeFont);
				boldFont.setBold(true);

				item(i, 0)->setFont(boldFont);
			}
			else
			{
				item(i, 0)->setFont(mSourceCodeFont);
			}
		}

		horizontalHeader()->setStyleSheet(QStringLiteral(
			"QHeaderView{font-family: \"") + mSourceCodeFont.family() +
			QStringLiteral("\"; font-weight: bold; font-size: ") + QString::number(size) + QStringLiteral("pt;}"
		));

		verticalHeader()->setStyleSheet(QStringLiteral(
			"QHeaderView{font-family: \"") + mSourceCodeFont.family() +
			QStringLiteral("\"; font-weight: bold; font-size: ") + QString::number(size) + QStringLiteral("pt;}"
		));
	}
}

void SourceCodeView::onSetSourceCodeFontSize(const QString& size)
{
	onSetSourceCodeFontSize(size.toInt());
}

void SourceCodeView::onSetCurrentHighlightLine(int line)
{
	if(mCurrentHighlightLine > 0 && mCurrentHighlightLine <= rowCount())
	{
		item(mCurrentHighlightLine - 1, 0)->setTextColor(Qt::black);
		item(mCurrentHighlightLine - 1, 0)->setFont(mSourceCodeFont);
		item(mCurrentHighlightLine - 1, 0)->setBackground(QColor(255, 255, 230));
	}

	if(line > 0 && line <= rowCount())
	{
		QFont boldFont(mSourceCodeFont);
		boldFont.setBold(true);

		item(line - 1, 0)->setTextColor(Qt::white);
		item(line - 1, 0)->setFont(boldFont);
		item(line - 1, 0)->setBackground(QColor(51, 153, 255));

		mCurrentHighlightLine = line;
	}
	else
	{
		mCurrentHighlightLine = 0;
	}
}

void SourceCodeView::onSetVisibleLineNumbers(bool visible)
{
	verticalHeader()->setVisible(visible);
}

void SourceCodeView::createActions()
{
	mSourceCodeMenu->setTitle(QStringLiteral("Kod źródłowy"));

	mLineNumbersAction->setText(QStringLiteral("Numery linii"));
	mLineNumbersAction->setCheckable(true);
	mLineNumbersAction->setChecked(true);

	mSourceCodeMenu->addAction(mLineNumbersAction);

	QMenu* sourceCodeFontSizeMenu = mSourceCodeMenu->addMenu(QStringLiteral("Rozmiar czcionki"));

	QWidgetAction* sourceCodeFontSizeAction = new QWidgetAction(sourceCodeFontSizeMenu);
	sourceCodeFontSizeAction->setDefaultWidget(mSourceCodeFontSizeComboBox);

	mSourceCodeFontSizeComboBox->addItems(QStringList()
		<< "6" << "7" << "8" << "9" << "10" << "11" << "12" << "14"
		<< "16" << "18" << "20" << "22" << "24" << "26" << "38"
		<< "48" << "72");

	mSourceCodeFontSizeComboBox->setCurrentIndex(mSourceCodeFontSizeComboBox->findText(QString::number(getSourceCodeFontSize())));

	sourceCodeFontSizeMenu->addAction(sourceCodeFontSizeAction);

	QMenu* sourceCodeIndentSizeMenu = mSourceCodeMenu->addMenu(QStringLiteral("Rozmiar wcięcia"));

	QWidgetAction* sourceCodeIndentSizeAction = new QWidgetAction(sourceCodeIndentSizeMenu);
	sourceCodeIndentSizeAction->setDefaultWidget(mSourceCodeIndentSizeComboBox);

	mSourceCodeIndentSizeComboBox->addItems(QStringList() << "2" << "4" << "8" << "16");
	mSourceCodeIndentSizeComboBox->setCurrentIndex(mSourceCodeIndentSizeComboBox->findText(QString::number(getSourceCodeIndentSize())));

	sourceCodeIndentSizeMenu->addAction(sourceCodeIndentSizeAction);
}

void SourceCodeView::createConnections()
{
	connect(this,
		&QTableWidget::customContextMenuRequested,
		this,
		&SourceCodeView::onContextMenu);

	connect(mLineNumbersAction,
		&QAction::toggled,
		this,
		&SourceCodeView::onSetVisibleLineNumbers);

	connect(mSourceCodeFontSizeComboBox,
		static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged),
		this,
		static_cast<void(SourceCodeView::*)(const QString&)>(&SourceCodeView::onSetSourceCodeFontSize));

	connect(mSourceCodeIndentSizeComboBox,
		static_cast<void(QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged),
		this,
		static_cast<void(SourceCodeView::*)(const QString&)>(&SourceCodeView::onSetSourceCodeIndentSize));
}

void SourceCodeView::onContextMenu(const QPoint&)
{
	mSourceCodeMenu->exec(QCursor::pos());
}
