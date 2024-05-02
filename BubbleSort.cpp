#include "BubbleSort.hpp"

#include "Instruction.hpp"


BubbleSort::BubbleSort() :
	SortingAlgorithm{QStringLiteral("Sortowanie bąbelkowe")}
{
	setSourceCode();
	setVariables();
}

void BubbleSort::run(const QVector<int>& array, QVector<Instruction>& instructions)
{
	QVector<int> T{array};

	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", -11).addVariable("R", T.size()));
	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", 0).addVariable("R", T.size()).addMarkBlock(0, Qt::yellow));

	for(int j = 0; j < T.size() - 1; ++j)
	{
		instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter).addVariable("i", T.size() - 1).addVariable("j", j).addVariable("R", T.size()).addMarkBlock(T.size() - 1, Qt::blue).addMarkBlock(j, Qt::yellow));
		for(int i = T.size() - 1; i > j; --i)
		{
			instructions.push_back(Instruction(7, T, ++mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("R", T.size()).addMarkBlock(j, Qt::yellow).setCompareBlocks(i, i - 1));
			if(T[i] < T[i - 1])
			{
				instructions.push_back(Instruction(9, T, mCompareCounter, ++mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("R", T.size()).addMarkBlock(j, Qt::yellow).setSwapBlocks(i, i - 1));
				std::swap(T[i], T[i - 1]);
			}
			instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter).addVariable("i", i - 1).addVariable("j", j).addVariable("R", T.size()).addMarkBlock(i - 1, Qt::blue).addMarkBlock(j, Qt::yellow));
		}
		instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", j + 1).addVariable("R", T.size()).addMarkBlock(j + 1, Qt::yellow));
	}
	instructions.push_back(Instruction(13, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", -11).addVariable("R", -11));
}

void BubbleSort::run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	QVector<int> T(array);

	++instructionCounter;
	++instructionCounter;
	for(int j = 0; j < T.size() - 1; ++j)
	{
		++instructionCounter;
		++instructionCounter;
		for(int i = T.size() - 1; i > j; --i)
		{
			++instructionCounter;
			++compareCounter;
			if(T[i] < T[i - 1])
			{
				++instructionCounter;
				++swapCounter;
				std::swap(T[i], T[i - 1]);
			}
			++instructionCounter;
			++instructionCounter;
		}
		++instructionCounter;
		++instructionCounter;
	}
}

void BubbleSort::run(int array[], const int Size)
{
	for(int j = 0; j < Size - 1; ++j)
	{
		for(int i = Size - 1; i > j; --i)
		{
			if(array[i] < array[i - 1])
				std::swap(array[i], array[i - 1]);
		}
	}
}

void BubbleSort::setSourceCode()
{
	QList<SourceLine> bubbleSortFunctionSourceLines;

	bubbleSortFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void bubbleSort(int T[], const int R)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"for(int j = 0; j < R - 1; ++j)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"for(int i = R - 1; i > j; --i)"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"if(T[i] < T[i - 1])"))
	<< SourceLine(3, QStringLiteral(			"{"))
	<< SourceLine(4, QStringLiteral(				"std::swap(T[i], T[i - 1]);"))
	<< SourceLine(3, QStringLiteral(			"}"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(bubbleSortFunctionSourceLines);
}

void BubbleSort::setVariables()
{
	mVariableInfoList
	<< VariableInformation(QStringLiteral("i"), Qt::blue)
	<< VariableInformation(QStringLiteral("j"), Qt::yellow)
	<< VariableInformation(QStringLiteral("R"), Qt::transparent);
}
