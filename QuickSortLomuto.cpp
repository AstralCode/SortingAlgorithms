#include "QuickSortLomuto.hpp"

#include "Instruction.hpp"


QuickSortLomuto::QuickSortLomuto() :
	SortingAlgorithm{QStringLiteral("Sortowanie szybkie (Lomuto)")}
{
	setSourceCode();
	setVariables();
}

void QuickSortLomuto::run(const QVector<int>& array, QVector<Instruction>& instructions)
{
	QVector<int> T(array);

	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter, 0, T.size() - 1).addVariable("i", -11).addVariable("j", -11).addVariable("p", 0).addVariable("r", T.size() - 1).addVariable("q", -11).addVariable("x", -11).setCurrentFunction(QuickSortFunction));
	quickSort(T, 0, T.size() - 1, instructions);
}

void QuickSortLomuto::run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	QVector<int> T(array);

	++instructionCounter;
	quickSort(T, 0, T.size() - 1, swapCounter, compareCounter, instructionCounter);
}

void QuickSortLomuto::run(int array[], const int size)
{
	quickSort(array, 0, size - 1);
}

void QuickSortLomuto::setSourceCode()
{
	QList<SourceLine> quickSortFunctionSourceLines;

	quickSortFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void quickSort(int T[], int p, int r)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"if(p < r)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"int q = partition(T, p, r);"))
	<< SourceLine(2, QStringLiteral(		"quickSort(T, p, q - 1);"))
	<< SourceLine(2, QStringLiteral(		"quickSort(T, q + 1, r);"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(quickSortFunctionSourceLines);

	QList<SourceLine> partitionFunctionSourceLines;

	partitionFunctionSourceLines
	<< SourceLine(0, QStringLiteral("int partition(int T[], int p, int r)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"int x = T[r];"))
	<< SourceLine(1, QStringLiteral(	"int i = p - 1;"))
	<< SourceLine(1, QStringLiteral(	"for(int j = p; j < r; ++j)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"if(T[j] <= x)"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"++i;"))
	<< SourceLine(3, QStringLiteral(			"std::swap(T[i], T[j]);"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(1, QStringLiteral(	"std::swap(T[i + 1], T[r]);"))
	<< SourceLine(1, QStringLiteral(	"return i + 1;"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(partitionFunctionSourceLines);
}

void QuickSortLomuto::setVariables()
{
	mVariableInfoList
	<< VariableInformation(QStringLiteral("i"), Qt::blue)
	<< VariableInformation(QStringLiteral("j"), Qt::yellow)
	<< VariableInformation(QStringLiteral("p"), Qt::transparent)
	<< VariableInformation(QStringLiteral("r"), Qt::transparent)
	<< VariableInformation(QStringLiteral("q"), QColor(64, 0, 128))
	<< VariableInformation(QStringLiteral("x"), Qt::magenta);
}

void QuickSortLomuto::quickSort(QVector<int>& T, int p, int r, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", -11).setCurrentFunction(QuickSortFunction));
	if(p < r)
	{
		instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", -11).setCurrentFunction(QuickSortFunction));
		int q = partition(T, p, r, instructions);
		instructions.push_back(Instruction(6, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", q).addVariable("x", -11).addMarkBlock(q, QColor(64, 0, 128)).setCurrentFunction(QuickSortFunction));
		quickSort(T, p, q - 1, instructions);
		instructions.push_back(Instruction(7, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", q).addVariable("x", -11).addMarkBlock(q, QColor(64, 0, 128)));
		quickSort(T, q + 1, r, instructions);
	}
	instructions.push_back(Instruction(9, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", -11).addVariable("r", -11).addVariable("q", -11).addVariable("x", -11).setCurrentFunction(QuickSortFunction));
}

void QuickSortLomuto::quickSort(QVector<int>& T, int p, int r, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	if(p < r)
	{
		++instructionCounter;
		int q = partition(T, p, r, swapCounter, compareCounter, instructionCounter);
		++instructionCounter;
		quickSort(T, p, q - 1, swapCounter, compareCounter, instructionCounter);
		++instructionCounter;
		quickSort(T, q + 1, r, swapCounter, compareCounter, instructionCounter);
	}
}

void QuickSortLomuto::quickSort(int T[], int p, int r)
{
	if(p < r)
	{
		int q = partition(T, p, r);

		quickSort(T, p, q - 1);

		quickSort(T, q + 1, r);
	}
}

int QuickSortLomuto::partition(QVector<int>& T, int p, int r, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).setCurrentFunction(PartitionFunction));

	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", -11));
	int x = T[r];
	instructions.push_back(Instruction(4, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(r, Qt::magenta));
	int i = p - 1;
	instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", p).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(p, Qt::yellow).addMarkBlock(r, Qt::magenta));
	for(int j = p; j < r; ++j)
	{
		instructions.push_back(Instruction(7, T, ++mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock((i >= p ? i : -1), Qt::blue).setCompareBlocks(j, r).addMarkBlock(r, Qt::magenta));
		if(T[j] <= x)
		{
			instructions.push_back(Instruction(9, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock((i >= p ? i : -1), Qt::blue).addMarkBlock(j, Qt::yellow).addMarkBlock(r, Qt::magenta));
			++i;
			instructions.push_back(Instruction(10, T, mCompareCounter, ++mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).setSwapBlocks(i, j).addMarkBlock(r, Qt::magenta));
			std::swap(T[i], T[j]);
		}
		instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j + 1).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock((i >= p ? i : -1), Qt::blue).addMarkBlock(j + 1, Qt::yellow).addMarkBlock(r, Qt::magenta));
	}
	instructions.push_back(Instruction(13, T, mCompareCounter, ++mSwapCounter, p, r).addVariable("i", i).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).setSwapBlocks(i + 1, r));
	std::swap(T[i + 1], T[r]);
	instructions.push_back(Instruction(14, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("q", -11).addVariable("x", x).addMarkBlock(i, Qt::blue).addMarkBlock(r, Qt::magenta).setCurrentFunction(PartitionFunction));
	return i + 1;
}

int QuickSortLomuto::partition(QVector<int>& T, int p, int r, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	int x = T[r];
	++instructionCounter;
	int i = p - 1;
	++instructionCounter;
	++instructionCounter;
	for(int j = p; j < r; ++j)
	{
		++instructionCounter;
		++compareCounter;
		if(T[j] <= x)
		{
			++instructionCounter;
			++i;
			++instructionCounter;
			std::swap(T[i], T[j]);
		}
		++instructionCounter;
		++instructionCounter;
	}
	++instructionCounter;
	++swapCounter;
	std::swap(T[i + 1], T[r]);

	return i + 1;
}

int QuickSortLomuto::partition(int T[], int p, int r)
{
	int x = T[r];

	int i = p - 1;

	for(int j = p; j < r; ++j)
	{
		if(T[j] <= x)
		{
			++i;

			std::swap(T[i], T[j]);
		}
	}

	std::swap(T[i + 1], T[r]);

	return i + 1;
}
