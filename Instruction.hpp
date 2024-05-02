#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <QVector>
#include <QList>
#include <QPair>
#include <QColor>

class Instruction
{
public:
	Instruction() = default;
	Instruction(int lineNumber, QVector<int>& array, int compares, int swaps, int beginIndex = -10, int endIndex = -10);

	Instruction& setCurrentFunction(int functionID);
	Instruction& setCompareBlocks(int firstIndex, int secondIndex);
	Instruction& setSwapBlocks(int firstIndex, int secondIndex);
	Instruction& addMarkBlock(int index, const QColor& color);
	Instruction& addMarkBlocks(int firstIndex, int secondIndex, const QColor& color);
	Instruction& addVariable(const QString& variable, int value);
	int getLineNumber() const;
	int getCurrentFunction() const;
	const QVector<int>& getArray() const;
	const QVector<QPair<int, QColor> >& getMarkBlocks() const;
	const QPair<int, int>& getSortRangeBlocks() const;
	const QPair<int, int>& getSwapBlocks() const;
	const QPair<int, int>& getCompareBlocks() const;
	const QVector<QPair<QString, QString> >& getVariables() const;
	int getCompareCounter() const;
	int getSwapCounter() const;

private:
	int mLineNumber;
	int mFunctionID;
	QVector<int> mArray;
	QVector<QPair<int, QColor> > mMarkBlocks;
	QPair<int, int> mSortRangeBlocks;
	QPair<int, int> mCompareBlocks;
	QPair<int, int> mSwapBlocks;
	QVector<QPair<QString, QString>> mVariables;
	int mCompareCounter;
	int mSwapCounter;
};

#endif // INSTRUCTION_HPP
