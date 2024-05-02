#ifndef SOURCECODEVIEW_HPP
#define SOURCECODEVIEW_HPP

#include <QTableWidget>

class QAction;
class QMenu;
class QComboBox;

class SourceLine;

class SourceCodeView : public QTableWidget
{
	Q_OBJECT

public:
	explicit SourceCodeView(QWidget* parent = nullptr);

	void setSourceCode(const QString& caption, const QVector<QList<SourceLine>>& sourceCode);
	void setCurrentSourceCode(int index);
	int getSourceCodeFontSize() const;
	int getSourceCodeIndentSize() const;
	int getCurrentHighlightLine() const;

public slots:
	void onSetSourceCodeIndentSize(int indentSize);
	void onSetSourceCodeIndentSize(const QString& size);
	void onSetSourceCodeFontSize(int size);
	void onSetSourceCodeFontSize(const QString& size);
	void onSetCurrentHighlightLine(int line);
	void onSetVisibleLineNumbers(bool visible);

private slots:
	void onContextMenu(const QPoint& Position);

private:
	void createActions();
	void createConnections();

	int mSourceCodeIndentSize;
	QFont mSourceCodeFont;
	int mCurrentSourceCode;
	int mCurrentHighlightLine;
	const QVector<QList<SourceLine>>* mSourceCode;
	QAction* mLineNumbersAction;
	QMenu* mSourceCodeMenu;
	QComboBox* mSourceCodeFontSizeComboBox;
	QComboBox* mSourceCodeIndentSizeComboBox;
};

#endif // SOURCECODEVIEW_HPP
