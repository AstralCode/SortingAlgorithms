#include "QuickSortHoare.hpp"

#include "Instruction.hpp"


QuickSortHoare::QuickSortHoare() :
	SortingAlgorithm{QStringLiteral("Sortowanie szybkie (Hoare)")},
	mXIndex{-1}
{
	setSourceCode();
	setVariables();
}

void QuickSortHoare::run(const QVector<int>& array, QVector<Instruction>& instructions)
{
	QVector<int> T(array);

	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter, 0, T.size() - 1).addVariable("i", -11).addVariable("j", -11).addVariable("p", 0).addVariable("r", T.size() - 1).addVariable("q", -11).addVariable("x", -11).setCurrentFunction(QuickSortFunction));
	quickSort(T, 0, T.size() - 1, instructions);
}

void QuickSortHoare::run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	QVector<int> T(array);

	++instructionCounter;
	quickSort(T, 0, T.size() - 1, swapCounter, compareCounter, instructionCounter);
}

void QuickSortHoare::run(int array[], const int size)
{
	quickSort(array, 0, size - 1);
}

void QuickSortHoare::setSourceCode()
{
	QList<SourceLine> quickSortFunctionSourceLines;

	quickSortFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void quickSort(int T[], int p, int r)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"if(p < r)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"int q = partition(T, p, r);"))
	<< SourceLine(2, QStringLiteral(		"quickSort(T, p, q);"))
	<< SourceLine(2, QStringLiteral(		"quickSort(T, q + 1, r);"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(quickSortFunctionSourceLines);

	QList<SourceLine> partitionFunctionSourceLines;

	partitionFunctionSourceLines
	<< SourceLine(0, QStringLiteral("int partition(int T[], int p, int r)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"int x = T[p];"))
	<< SourceLine(1, QStringLiteral(	"int i = p - 1;"))
	<< SourceLine(1, QStringLiteral(	"int j = r + 1;"))
	<< SourceLine(1, QStringLiteral(	"while(true)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"do"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"--j;"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(2, QStringLiteral(		"while(T[j] > x);"))
	<< SourceLine(2, QStringLiteral(		"do"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"++i;"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(2, QStringLiteral(		"while(T[i] < x);"))
	<< SourceLine(2, QStringLiteral(		"if(i < j)"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"std::swap(T[i], T[j]);"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(2, QStringLiteral(		"else"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"return j;"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(partitionFunctionSourceLines);
}

void QuickSortHoare::setVariables()
{
	mVariableInfoList
	<< VariableInformation(QStringLiteral("i"), Qt::blue)
	<< VariableInformation(QStringLiteral("j"), Qt::yellow)
	<< VariableInformation(QStringLiteral("p"), Qt::transparent)
	<< VariableInformation(QStringLiteral("r"), Qt::transparent)
	<< VariableInformation(QStringLiteral("q"), QColor(64, 0, 128))
	<< VariableInformation(QStringLiteral("x"), Qt::magenta);
}

void QuickSortHoare::quickSort(QVector<int>& T, int p, int r, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", -11).setCurrentFunction(QuickSortFunction));
	if(p < r)
	{
		instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", -11).setCurrentFunction(QuickSortFunction));
		int q = partition(T, p, r, instructions);
		instructions.push_back(Instruction(6, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", q).addVariable("x", -11).addMarkBlock(q, QColor(64, 0, 128)).setCurrentFunction(QuickSortFunction));
		quickSort(T, p, q, instructions);
		instructions.push_back(Instruction(7, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", q).addVariable("x", -11).addMarkBlock(q, QColor(64, 0, 128)));
		quickSort(T, q + 1, r, instructions);
	}
	instructions.push_back(Instruction(9, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", -11).addVariable("r", -11).addVariable("q", -11).addVariable("x", -11).setCurrentFunction(QuickSortFunction));
}

void QuickSortHoare::quickSort(QVector<int>& T, int p, int r, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	if(p < r)
	{
		++instructionCounter;
		int q = partition(T, p, r, swapCounter, compareCounter, instructionCounter);
		++instructionCounter;
		quickSort(T, p, q, swapCounter, compareCounter, instructionCounter);
		++instructionCounter;
		quickSort(T, q + 1, r, swapCounter, compareCounter, instructionCounter);
	}
}

void QuickSortHoare::quickSort(int T[], int p, int r)
{
	if(p < r)
	{
		int q = partition(T, p, r);

		quickSort(T, p, q);

		quickSort(T, q + 1, r);
	}
}

int QuickSortHoare::partition(QVector<int>& T, int p, int r, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).setCurrentFunction(PartitionFunction));

	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", -11));
	int x = T[p];
	mXIndex = p;
	instructions.push_back(Instruction(4, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(mXIndex, Qt::magenta));
	int i = p - 1;
	instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(mXIndex, Qt::magenta));
	int j = r + 1;
	instructions.push_back(Instruction(6, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(j, Qt::yellow).addMarkBlock(mXIndex, Qt::magenta));
	while(true)
	{
		do
		{
			instructions.push_back(Instruction(10, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(mXIndex, Qt::magenta));
			--j;
			instructions.push_back(Instruction(12, T, ++mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(mXIndex, Qt::magenta).setCompareBlocks(j, mXIndex));
		}
		while(T[j] > x);
		do
		{
			instructions.push_back(Instruction(15, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(mXIndex, Qt::magenta));
			++i;
			instructions.push_back(Instruction(17, T, ++mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(mXIndex, Qt::magenta).setCompareBlocks(i, mXIndex));
		}
		while(T[i] < x);
		instructions.push_back(Instruction(18, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(mXIndex, Qt::magenta));
		if(i < j)
		{
			if(i == mXIndex)
			{
				mXIndex = j;
			}

			instructions.push_back(Instruction(20, T, mCompareCounter, ++mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(mXIndex, Qt::magenta).setSwapBlocks(i, j));
			std::swap(T[i], T[j]);
		}
		else
		{
			instructions.push_back(Instruction(24, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(mXIndex, Qt::magenta).setCurrentFunction(PartitionFunction));
			return j;
		}
	}
}

int QuickSortHoare::partition(QVector<int>& T, int p, int r, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	int x = T[p];
	mXIndex = p;
	++instructionCounter;
	int i = p - 1;
	++instructionCounter;
	int j = r + 1;
	++instructionCounter;
	while(true)
	{
		do
		{
			++instructionCounter;
			--j;
			++instructionCounter;
			++compareCounter;
		}
		while(T[j] > x);
		do
		{
			++instructionCounter;
			++i;
			++instructionCounter;
			++compareCounter;
		}
		while(T[i] < x);
		++instructionCounter;
		if(i < j)
		{
			if(i == mXIndex)
			{
				mXIndex = j;
			}

			++instructionCounter;
			++swapCounter;
			std::swap(T[i], T[j]);
		}
		else
		{
			return j;
		}
	}
}

int QuickSortHoare::partition(int T[], int p, int r)
{
	int x = T[p];
	int i = p - 1;
	int j = r + 1;
	while(true)
	{
		do
		{
			--j;
		}
		while(T[j] > x);
		do
		{
			++i;
		}
		while(T[i] < x);
		if(i < j)
		{
			std::swap(T[i], T[j]);
		}
		else
		{
			return j;
		}
	}
}
