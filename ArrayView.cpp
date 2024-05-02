#include "ArrayView.hpp"

#include <QGraphicsScene>


ArrayView::ArrayView(QWidget* parent) :
	QGraphicsView{parent},
	mGraphicsScene{new QGraphicsScene},
	mCurrentArraySize{0}
{
	setMinimumSize(250, 150);
	setScene(mGraphicsScene);
	setBackgroundBrush(QBrush(Qt::black));
	setRenderHint(QPainter::Antialiasing);
}

ArrayView::ArrayView(int fixedArraySize, int maxValue, int arraySize, QWidget* parent) :
	ArrayView{parent}
{
	setArrayFixedSize(fixedArraySize, maxValue);
	onSetArraySize(arraySize);
}

void ArrayView::setArrayFixedSize(int size, int maxValue)
{
	const QSizeF elementSize{70.0, 20.0};
	QPointF position;

	maxValue = maxValue < 0 ? 0 : maxValue;
	size = size < 0 ? 0 : size;

	for(auto i = 0; i < size; ++i)
	{
		QSharedPointer<ArrayBlock> block{new ArrayBlock{QStringLiteral("T[") + QString::number(i) + QStringLiteral("]"), 0, maxValue, elementSize}};
		block->setPos(position);
		mBlocks.append(qMove(block));

		position.setX(position.x() + elementSize.width() + 5.0);
	}
}

void ArrayView::setArrayBlockColor(int index, const QColor& color)
{
	if(index > -1 && index < mCurrentArraySize)
	{
		mBlocks.at(index)->setElementColor(color);
		mBlocks.at(index)->update();
	}
}

void ArrayView::setArrayBlocksColor(const QPair<int, int>& blocks, const QColor& color)
{
	setArrayBlockColor(blocks.first, color);
	setArrayBlockColor(blocks.second, color);
}

void ArrayView::setArrayBlocksColor(const QVector<QPair<int, QColor> >& blocks)
{
	for(QPair<int, QColor> block : blocks)
		setArrayBlockColor(block.first, block.second);
}

void ArrayView::setArrayBlockColored(int index, bool colored)
{
	if(index > -1 && index < mCurrentArraySize)
	{
		mBlocks.at(index)->setColored(colored);
		mBlocks.at(index)->update();
	}
}

void ArrayView::setArrayBlocksColored(const QPair<int, int>& range)
{
	for(int i = 0; i < mCurrentArraySize; ++i)
		mBlocks.at(i)->setColored(false);

	if(range.first < 0 || range.second < 0)
		return;

	for(int i = range.first; i <= range.second; ++i)
		mBlocks.at(i)->setColored(true);
}

void ArrayView::resetArrayBlocks()
{
	for(int i = 0; i < mCurrentArraySize; ++i)
	{
		mBlocks.at(i)->reset();
		mBlocks.at(i)->update();
	}
}

void ArrayView::onSetArraySize(int size)
{
	if(size > -1 && size <= mBlocks.size() && size != mCurrentArraySize)
	{
		if(size > mCurrentArraySize)
		{
			for(int i = mCurrentArraySize; i < size; ++i)
				mGraphicsScene->addItem(mBlocks.at(i).data());
		}
		else
		{
			for(int i = mCurrentArraySize - 1; i >= size; --i)
			{
				mBlocks.at(i)->reset();
				mGraphicsScene->removeItem(mBlocks.at(i).data());
			}
		}

		mCurrentArraySize = size;
		mGraphicsScene->setSceneRect(mGraphicsScene->itemsBoundingRect());
	}
}

void ArrayView::onSetArrayBlockValue(int index, int value)
{
	if(index > -1 && index < mCurrentArraySize)
	{
		mBlocks.at(index)->setValue(value);
		mBlocks.at(index)->update();
	}
}

void ArrayView::onSetArrayBlockValues(const QVector<int>& values)
{
	for(int i = 0; i < values.size() && i < mCurrentArraySize; ++i)
		onSetArrayBlockValue(i, values[i]);
}

void ArrayView::resizeEvent(QResizeEvent*)
{
	QRectF sceneRect = mGraphicsScene->sceneRect();
	sceneRect.setWidth(sceneRect.width() + 45.0);
	sceneRect.setHeight(sceneRect.height() + 45.0);

	fitInView(sceneRect, Qt::KeepAspectRatio);
}
