#include "InsertionSort.hpp"

#include "Instruction.hpp"


InsertionSort::InsertionSort() :
	SortingAlgorithm{QStringLiteral("Sortowanie przez wstawianie")}
{
	setSourceCode();
	setVariables();
}

void InsertionSort::run(const QVector<int>& array, QVector<Instruction>& instructions)
{
	QVector<int> T(array);

	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", -11).addVariable("k", -11).addVariable("R", T.size()));

	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", 1).addVariable("k", -11).addVariable("R", T.size()).addMarkBlock(1, Qt::yellow));
	for(int j = 1; j < T.size(); ++j)
	{
		instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", j).addVariable("k", -11).addVariable("R", T.size()).addMarkBlock(j, Qt::yellow));
		int k = T[j];
		instructions.push_back(Instruction(6, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", j).addVariable("k", k).addVariable("R", T.size()).addMarkBlock(j, Qt::yellow));
		int i = j - 1;
		instructions.push_back(Instruction(7, T, (i > -1 ? ++mCompareCounter : mCompareCounter), mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("k", k).addVariable("R", T.size()).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow));
		while(i > -1 && T[i] > k)
		{
			instructions.push_back(Instruction(9, T, mCompareCounter, ++mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("k", k).addVariable("R", T.size()).addMarkBlock(j, Qt::yellow).setSwapBlocks(i + 1, i));
			T[i + 1] = T[i];
			instructions.push_back(Instruction(10, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("k", k).addVariable("R", T.size()).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow));
			--i;
			instructions.push_back(Instruction(7, T, (i > -1 ? ++mCompareCounter : mCompareCounter), mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("k", k).addVariable("R", T.size()).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow));
		}
		instructions.push_back(Instruction(12, T, mCompareCounter, ++mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("k", k).addVariable("R", T.size()).addMarkBlock(i + 1, Qt::blue).addMarkBlock(j, Qt::yellow));
		T[i + 1] = k;
		instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", j + 1).addVariable("k", -11).addVariable("R", T.size()).addMarkBlock(j + 1, Qt::yellow));
	}
	instructions.push_back(Instruction(14, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", -11).addVariable("k", -11).addVariable("R", -11));
}

void InsertionSort::run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	QVector<int> T(array);

	++instructionCounter;
	++instructionCounter;
	for(int j = 1; j < T.size(); ++j)
	{
		++instructionCounter;
		int k = T[j];
		++instructionCounter;
		int i = j - 1;
		++instructionCounter;
		++instructionCounter;
		++compareCounter;
		while(i > -1 && T[i] > k)
		{
			++instructionCounter;
			++swapCounter;
			T[i + 1] = T[i];
			++instructionCounter;
			--i;
			++instructionCounter;
			++instructionCounter;
			++compareCounter;
		}
		++instructionCounter;
		++swapCounter;
		T[i + 1] = k;
		++instructionCounter;
		++instructionCounter;
	}
}

void InsertionSort::run(int array[], const int size)
{
	for(int j = 1; j < size; ++j)
	{
		int k = array[j];
		int i = j - 1;
		while(i > -1 && array[i] > k)
		{
			array[i + 1] = array[i];

			--i;
		}
		array[i + 1] = k;
	}
}

void InsertionSort::setSourceCode()
{
	QList<SourceLine> insertionSortFunctionSourceLines;

	insertionSortFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void insertionSort(int T[], const int R)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"for(int j = 1; j < R; ++j)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"int k = T[j];"))
	<< SourceLine(2, QStringLiteral(		"int i = j - 1;"))
	<< SourceLine(2, QStringLiteral(		"while(i > -1 && T[i] > k)"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"T[i + 1] = T[i];"))
	<< SourceLine(3, QStringLiteral(			"--i;"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(2, QStringLiteral(		"T[i + 1] = k;"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(insertionSortFunctionSourceLines);
}

void InsertionSort::setVariables()
{
	mVariableInfoList
	<< VariableInformation(QStringLiteral("i"), Qt::blue)
	<< VariableInformation(QStringLiteral("j"), Qt::yellow)
	<< VariableInformation(QStringLiteral("k"), Qt::transparent)
	<< VariableInformation(QStringLiteral("R"), Qt::transparent);
}
