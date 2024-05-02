#include "Instruction.hpp"


Instruction::Instruction(int lineNumber, QVector<int>& array, int compares, int swaps, int beginIndex, int endIndex) :
	mLineNumber{lineNumber},
	mFunctionID{-1},
	mArray{array},
	mSortRangeBlocks{qMakePair(beginIndex, endIndex)},
	mCompareBlocks{qMakePair(-1, -1)},
	mSwapBlocks{qMakePair(-1, -1)},
	mCompareCounter{compares},
	mSwapCounter{swaps}
{
	if(mSortRangeBlocks.first == -10 && mSortRangeBlocks.second == -10)
	{
		mSortRangeBlocks.first = 0;
		mSortRangeBlocks.second = mArray.size() - 1;
	}
}

Instruction& Instruction::setCurrentFunction(int functionID)
{
	mFunctionID = functionID;

	return *this;
}

Instruction& Instruction::setCompareBlocks(int firstIndex, int secondIndex)
{
	mCompareBlocks = qMakePair(firstIndex, secondIndex);

	return *this;
}

Instruction& Instruction::setSwapBlocks(int firstIndex, int secondIndex)
{
	mSwapBlocks = qMakePair(firstIndex, secondIndex);

	return *this;
}

Instruction& Instruction::addMarkBlock(int index, const QColor& color)
{
	if(index < 0)
		return *this;

	mMarkBlocks.push_back(qMakePair(index, color));

	return *this;
}

Instruction& Instruction::addMarkBlocks(int firstIndex, int secondIndex, const QColor& color)
{
	if(firstIndex < 0)
		return *this;

	for(auto i = firstIndex; i <= secondIndex; ++i)
		mMarkBlocks.push_back(qMakePair(i, color));

	return *this;
}

Instruction& Instruction::addVariable(const QString& variable, int value)
{
	QString text = value != -11 ? QString::number(value) : "";

	mVariables.push_back(qMakePair(variable, text));

	return *this;
}

int Instruction::getLineNumber() const
{
	return mLineNumber;
}

int Instruction::getCurrentFunction() const
{
	return mFunctionID;
}

const QVector<int>& Instruction::getArray() const
{
	return mArray;
}

const QVector<QPair<int, QColor>>& Instruction::getMarkBlocks() const
{
	return mMarkBlocks;
}

const QPair<int, int>& Instruction::getSortRangeBlocks() const
{
	return mSortRangeBlocks;
}

const QPair<int, int>& Instruction::getSwapBlocks() const
{
	return mSwapBlocks;
}

const QPair<int, int>& Instruction::getCompareBlocks() const
{
	return mCompareBlocks;
}

const QVector<QPair<QString, QString>>& Instruction::getVariables() const
{
	return mVariables;
}

int Instruction::getCompareCounter() const
{
	return mCompareCounter;
}

int Instruction::getSwapCounter() const
{
	return mSwapCounter;
}
