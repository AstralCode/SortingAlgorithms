#include "ArrayBlock.hpp"

#include <QPainter>


ArrayBlock::ArrayBlock(int maxValue, const QSizeF& elementSize, qreal spacing) :
	ArrayBlock(QStringLiteral(""), 0, maxValue, elementSize, spacing)
{

}

ArrayBlock::ArrayBlock(int index, int value, int elementCount, const QSizeF& elementSize, qreal spacing) :
	ArrayBlock(QString::number(index), value, elementCount, elementSize, spacing)
{

}

ArrayBlock::ArrayBlock(const QString& Index, int value, int maxValue, const QSizeF& elementSize, qreal spacing) :
	mIndex{Index},
	mMaxValue{maxValue},
	mElementSize{elementSize},
	mSpacing{spacing},
	mPen{Qt::green},
	mBrush{Qt::green},
	mColored{true}
{
	constexpr auto topMargin = 60.0;

	mSize.setWidth(mElementSize.width());
	mSize.setHeight(mElementSize.height() * mMaxValue + mSpacing * (mMaxValue - 1) + topMargin);

	mPen.setStyle(Qt::DotLine);

	mIndex.setTextWidth(mElementSize.width());
	mIndex.setTextOption(QTextOption(Qt::AlignCenter));

	setValue(value);
}

void ArrayBlock::setValue(int value)
{
	if(value > -1 && value <= mMaxValue)
		mValue = value;
}

void ArrayBlock::setIndex(const QString& index)
{
	mIndex.setText(index);
}

void ArrayBlock::setIndex(int index)
{
	setIndex(QString::number(index));
}

void ArrayBlock::setColored(bool colored)
{
	mColored = colored;
}

void ArrayBlock::reset()
{
	setElementFrameColor(Qt::green);
	setElementColor(Qt::green);
	setValue(0);

	mColored = true;
}

void ArrayBlock::update()
{
	QGraphicsItem::update(boundingRect());
}

int ArrayBlock::getValue() const
{
	return mValue;
}

bool ArrayBlock::isColored() const
{
	return mColored;
}

QRectF ArrayBlock::boundingRect() const
{
	return QRectF(QPointF(), mSize);
}

void ArrayBlock::setElementFrameColor(const QColor& color, Qt::PenStyle style)
{
	mPen.setColor(color);
	mPen.setStyle(style);
}

void ArrayBlock::setElementColor(const QColor& color)
{
	mBrush.setColor(color);
}

void ArrayBlock::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
	const QPen notColoredPenColor{Qt::transparent};
	const QBrush transparentBrushColor{Qt::transparent};
	const QSizeF informationElement{mElementSize.width(), 22.0};

	QBrush notColoredBrushColor{mBrush};
	notColoredBrushColor.setColor(Qt::lightGray);

	QPen informationElementFont(mColored ? mPen : notColoredPenColor);
	informationElementFont.setColor(mColored ? Qt::white : Qt::lightGray);

	QPointF position(0.0, mSize.height() - informationElement.height());

	painter->setFont(QFont(QStringLiteral("Courier New"), 16, QFont::Normal));
	painter->setPen(informationElementFont);
	painter->setBrush(transparentBrushColor);
	painter->drawStaticText(position, mIndex);

	QPen informationElementRectPen{mPen};

	if(mColored)
	{
		informationElementRectPen.setColor(mBrush.color());
	}
	else
	{
		informationElementRectPen.setColor(Qt::lightGray);
	}

	painter->setPen(informationElementRectPen);
	position.setY(position.y() - (informationElement.height() + 5.0));
	painter->drawRect(QRectF(position, informationElement));
	painter->setPen(informationElementFont);
	painter->drawText(QRectF(position, informationElement), Qt::AlignCenter, QString::number(mValue));
	painter->setPen(mColored ? mPen : notColoredPenColor);
	position.setY(position.y() - (mElementSize.height() + 8.0));

	for(auto i{0}; i < mMaxValue; ++i)
	{
		if(i < mValue)
		{
			painter->setBrush(mColored ? mBrush : notColoredBrushColor);
		}
		else
		{
			painter->setBrush(transparentBrushColor);
		}

		painter->drawRect(QRectF(position, mElementSize));
		position.setY(position.y() - (mElementSize.height() + mSpacing));
	}
}
