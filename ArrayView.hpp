#ifndef ARRAYVIEW_HPP
#define ARRAYVIEW_HPP

#include <QGraphicsView>
#include <QVector>

#include "ArrayBlock.hpp"

class QGraphicsScene;
class QResizeEvent;

class ArrayView : public QGraphicsView
{
	Q_OBJECT

public:
	explicit ArrayView(QWidget* parent = nullptr);
	explicit ArrayView(int fixedArraySize, int maxValue, int arraySize = 0, QWidget* parent = nullptr);

	void setArrayFixedSize(int size, int maxValue);
	void setArrayBlockColor(int index, const QColor& color);
	void setArrayBlocksColor(const QPair<int, int>& blocks, const QColor& color);
	void setArrayBlocksColor(const QVector<QPair<int, QColor> >& blocks);
	void setArrayBlockColored(int index, bool colored);
	void setArrayBlocksColored(const QPair<int, int>& range);
	void resetArrayBlocks();

public slots:
	void onSetArraySize(int size);
	void onSetArrayBlockValue(int index, int value);
	void onSetArrayBlockValues(const QVector<int>& values);

private:
	void resizeEvent(QResizeEvent* event);

	QGraphicsScene*	mGraphicsScene;
	QVector<ArrayBlock::Ptr> mBlocks;
	int	mCurrentArraySize;
};

#endif // ARRAYVIEW_HPP
