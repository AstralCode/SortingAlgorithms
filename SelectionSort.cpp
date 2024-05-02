#include "SelectionSort.hpp"

#include "Instruction.hpp"


SelectionSort::SelectionSort() :
	SortingAlgorithm{QStringLiteral("Sortowanie przez wybieranie")}
{
	setSourceCode();
	setVariables();
}

void SelectionSort::run(const QVector<int>& array, QVector<Instruction>& instructions)
{
	QVector<int> T(array);

	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", -11).addVariable("m", -11).addVariable("R", T.size()));

	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", 0).addVariable("m", -11).addVariable("R", T.size()).addMarkBlock(0, Qt::yellow));
	for(int j = 0; j < array.size() - 1; j++)
	{
		instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", j).addVariable("m", -11).addVariable("R", T.size()).addMarkBlock(j, Qt::yellow));
		int m = j;
		instructions.push_back(Instruction(6, T, mCompareCounter, mSwapCounter).addVariable("i", j + 1).addVariable("j", j).addVariable("m", m).addVariable("R", T.size()).addMarkBlock(j + 1, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(m, Qt::magenta));
		for(int i = j + 1; i < array.size(); i++)
		{
			instructions.push_back(Instruction(8, T, ++mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("m", m).addVariable("R", T.size()).addMarkBlock(j, Qt::yellow).setCompareBlocks(i, m));
			if(T[i] < T[m])
			{
				instructions.push_back(Instruction(10, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("j", j).addVariable("m", m).addVariable("R", T.size()).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(m, Qt::magenta));
				m = i;
			}
			instructions.push_back(Instruction(6, T, mCompareCounter, mSwapCounter).addVariable("i", i + 1).addVariable("j", j).addVariable("m", m).addVariable("R", T.size()).addMarkBlock(i + 1, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(m, Qt::magenta));
		}
		instructions.push_back(Instruction(13, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", j).addVariable("m", m).addVariable("R", T.size()).addMarkBlock(j, Qt::yellow).addMarkBlock(m, Qt::magenta));
		if(m != j)
		{
			instructions.push_back(Instruction(15, T, mCompareCounter, ++mSwapCounter).addVariable("i", -11).addVariable("j", j).addVariable("m", m).addVariable("R", T.size()).setSwapBlocks(j, m));
			std::swap(T[j], T[m]);
		}
		instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", j + 1).addVariable("m", -11).addVariable("R", T.size()).addMarkBlock(j + 1, Qt::yellow));
	}
	instructions.push_back(Instruction(18, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("j", -11).addVariable("m", -11).addVariable("R", -11));
}

void SelectionSort::run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	QVector<int> T(array);

	++instructionCounter;
	++instructionCounter;
	for(int j = 0; j < array.size() - 1; j++)
	{
		++instructionCounter;
		int m = j;
		++instructionCounter;
		++instructionCounter;
		for(int i = j + 1; i < array.size(); i++)
		{
			++instructionCounter;
			++compareCounter;
			if(T[i] < T[m])
			{
				++instructionCounter;
				m = i;
			}
			++instructionCounter;
			++instructionCounter;
		}
		++instructionCounter;
		++compareCounter;
		if(m != j)
		{
			++instructionCounter;
			++swapCounter;
			std::swap(T[j], T[m]);
		}
		++instructionCounter;
		++instructionCounter;
	}
}

void SelectionSort::run(int array[], const int size)
{
	for(int j = 0; j < size - 1; j++)
	{
		int m = j;
		for(int i = j + 1; i < size; i++)
		{
			if(array[i] < array[m])
			{
				m = i;
			}
		}
		if(m != j)
		{
			std::swap(array[j], array[m]);
		}
	}
}

void SelectionSort::setSourceCode()
{
	QList<SourceLine> selectionSortFunctionSourceLines;

	selectionSortFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void selectionSort(int T[], const int R)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"for(int j = 0; j < R - 1; ++j)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"int m = j;"))
	<< SourceLine(2, QStringLiteral(		"for(int i = j + 1; i < R; ++i)"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"if(T[i] < T[m])"))
	<< SourceLine(3, QStringLiteral(			"{"))
	<< SourceLine(4, QStringLiteral(				"m = i;"))
	<< SourceLine(3, QStringLiteral(			"}"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(2, QStringLiteral(		"if(m != j)"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"std::swap(T[j], T[m]);"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(selectionSortFunctionSourceLines);
}

void SelectionSort::setVariables()
{
	mVariableInfoList
	<< VariableInformation(QStringLiteral("i"), Qt::blue)
	<< VariableInformation(QStringLiteral("j"), Qt::yellow)
	<< VariableInformation(QStringLiteral("m"), Qt::magenta)
	<< VariableInformation(QStringLiteral("R"), Qt::transparent);
}
