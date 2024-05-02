#ifndef ARRAYBLOCK_HPP
#define ARRAYBLOCK_HPP

#include <QGraphicsItem>
#include <QSharedPointer>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QStaticText>

class ArrayBlock : public QGraphicsItem
{
public:
	using Ptr = QSharedPointer<ArrayBlock>;

	ArrayBlock(int maxValue, const QSizeF& elementSize, qreal spacing = 5.0);
	ArrayBlock(int index, int value, int elementCount, const QSizeF& elementSize, qreal spacing = 5.0);
	ArrayBlock(const QString& Index, int value, int maxValue, const QSizeF& elementSize, qreal spacing = 5.0);

	void setIndex(const QString& Index);
	void setIndex(int index);
	void setElementFrameColor(const QColor& Color, Qt::PenStyle style = Qt::DotLine);
	void setElementColor(const QColor& Color);
	void setValue(int value);
	void setColored(bool colored);
	void reset();
	void update();
	int getValue() const;
	bool isColored() const;
	QRectF boundingRect() const;

private:
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* Option, QWidget* widget);

	QStaticText	mIndex;
	int	mMaxValue;
	QSizeF mElementSize;
	qreal mSpacing;
	QSizeF mSize;
	int mValue;
	QPen mPen;
	QBrush mBrush;
	bool mColored;
};

#endif // ARRAYBLOCK_HPP
