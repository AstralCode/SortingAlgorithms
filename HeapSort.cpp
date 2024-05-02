#include "HeapSort.hpp"

#include "Instruction.hpp"


HeapSort::HeapSort() :
	SortingAlgorithm(QStringLiteral("Sortowanie przez kopcowanie"))
{
	setSourceCode();
	setVariables();
}

void HeapSort::run(const QVector<int>& array, QVector<Instruction>& instructions)
{
	QVector<int> T(array);

	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter, 0, T.size() - 1).addVariable("i", -11).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", T.size() - 1).setCurrentFunction(HeapSortFunction));
	heapSort(T, T.size() - 1, instructions);
}

void HeapSort::run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	QVector<int> T(array);

	++instructionCounter;
	heapSort(T, T.size() - 1, swapCounter, compareCounter, instructionCounter);
}

void HeapSort::run(int array[], const int size)
{
	heapSort(array, size - 1);
}

void HeapSort::setSourceCode()
{
	QList<SourceLine> heapSortFunctionSourceLines;

	heapSortFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void heapSort(int T[], const int R)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"buildMaxHeap(T, R);"))
	<< SourceLine(1, QStringLiteral(	"for(int i = R; i > 0;)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"std::swap(T[0], T[i]);"))
	<< SourceLine(2, QStringLiteral(		"--i;"))
	<< SourceLine(2, QStringLiteral(		"maxHeapify(T, i, 0);"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(heapSortFunctionSourceLines);

	QList<SourceLine> buildMaxHeapFunctionSourceLines;

	buildMaxHeapFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void buildMaxHeap(int T[], const int R)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"for(int i = R / 2; i >= 0; --i)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"maxHeapify(T, R, i);"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(buildMaxHeapFunctionSourceLines);

	QList<SourceLine> maxHeapifyFunctionSourceLines;

	maxHeapifyFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void maxHeapify(int T[], const int R, int i)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"int l = (i << 1) + 1;"))
	<< SourceLine(1, QStringLiteral(	"int r = (i << 1) + 2;"))
	<< SourceLine(1, QStringLiteral(	"int m;"))
	<< SourceLine(1, QStringLiteral(	"if(l <= R && T[l] > T[i])"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"m = l;"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(1, QStringLiteral(	"else"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"m = i;"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(1, QStringLiteral(	"if(r <= R && T[r] > T[m])"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"m = r;"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(1, QStringLiteral(	"if(m != i)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"std::swap(T[i], T[m]);"))
	<< SourceLine(2, QStringLiteral(		"maxHeapify(T, R, m);"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(maxHeapifyFunctionSourceLines);
}

void HeapSort::setVariables()
{
	mVariableInfoList
	<< VariableInformation(QStringLiteral("i"), Qt::blue)
	<< VariableInformation(QStringLiteral("l"), QColor(64, 0, 128))
	<< VariableInformation(QStringLiteral("r"), Qt::magenta)
	<< VariableInformation(QStringLiteral("m"), Qt::yellow)
	<< VariableInformation(QStringLiteral("R"), Qt::transparent);
}

void HeapSort::heapSort(QVector<int>& T, const int R, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).setCurrentFunction(HeapSortFunction));
	buildMaxHeap(T, R, instructions);
	instructions.push_back(Instruction(4, T, mCompareCounter, mSwapCounter).addVariable("i", R).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(R, Qt::blue).setCurrentFunction(HeapSortFunction));
	for(int i = R; i > 0;)
	{
		instructions.push_back(Instruction(6, T, mCompareCounter, ++mSwapCounter).addVariable("i", i).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).setSwapBlocks(0, i));
		std::swap(T[0], T[i]);
		instructions.push_back(Instruction(7, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue));
		--i;
		instructions.push_back(Instruction(8, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).setCurrentFunction(HeapSortFunction));
		maxHeapify(T, i, 0, instructions);
		instructions.push_back(Instruction(4, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).setCurrentFunction(HeapSortFunction));
	}
	instructions.push_back(Instruction(10, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", -11).setCurrentFunction(HeapSortFunction));
}

void HeapSort::heapSort(QVector<int>& T, const int R, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	buildMaxHeap(T, R, swapCounter, compareCounter, instructionCounter);
	++instructionCounter;
	++instructionCounter;
	for(int i = R; i > 0;)
	{
		++instructionCounter;
		++swapCounter;
		std::swap(T[0], T[i]);
		++instructionCounter;
		--i;
		++instructionCounter;
		maxHeapify(T, i, 0, swapCounter, compareCounter, instructionCounter);
		++instructionCounter;
	}
}

void HeapSort::heapSort(int T[], const int R)
{
	buildMaxHeap(T, R);

	for(int i = R; i > 0;)
	{
		std::swap(T[0], T[i]);

		--i;

		maxHeapify(T, i, 0);
	}
}


void HeapSort::buildMaxHeap(QVector<int>& T, const int R, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).setCurrentFunction(BuildMaxHeapFunction));

	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", R / 2).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(R / 2, Qt::blue));
	for(int i = R / 2; i >= 0; --i)
	{
		instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).setCurrentFunction(BuildMaxHeapFunction));
		maxHeapify(T, R, i, instructions);
		instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", i - 1).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(i - 1, Qt::blue).setCurrentFunction(BuildMaxHeapFunction));
	}
	instructions.push_back(Instruction(7, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", -11).setCurrentFunction(BuildMaxHeapFunction));
}

void HeapSort::buildMaxHeap(QVector<int>& T, const int R, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	for(int i = R / 2; i >= 0; --i)
	{
		++instructionCounter;
		maxHeapify(T, R, i, swapCounter, compareCounter, instructionCounter);
		++instructionCounter;
		++instructionCounter;
	}
}

void HeapSort::buildMaxHeap(int T[], const int R)
{
	for(int i = R / 2; i >= 0; --i)
	{
		maxHeapify(T, R, i);
	}
}

void HeapSort::maxHeapify(QVector<int>& T, const int R, int i, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).setCurrentFunction(MaxHeapifyFunction));

	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue));
	int l = (i << 1) + 1;
	instructions.push_back(Instruction(4, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", -11).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).addMarkBlock(l, QColor(64, 0, 128)));
	int r = (i << 1) + 2;
	instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).addMarkBlock(l, QColor(64, 0, 128)).addMarkBlock(r, Qt::magenta));
	int m;
	instructions.push_back(Instruction(6, T, (l <= R) ? ++mCompareCounter : mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).addMarkBlock(r, Qt::magenta).setCompareBlocks((l <= R) ? l : -1, i));
	if(l <= R && T[l] > T[i])
	{
		instructions.push_back(Instruction(8, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).addMarkBlock(l, QColor(64, 0, 128)).addMarkBlock(r, Qt::magenta));
		m = l;
	}
	else
	{
		instructions.push_back(Instruction(12, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", -11).addVariable("R", R).addMarkBlock(l, QColor(64, 0, 128)).addMarkBlock(r, Qt::magenta).addMarkBlock(i, Qt::blue));
		m = i;
	}
	instructions.push_back(Instruction(14, T, (r <= R) ? ++mCompareCounter : mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", m).addVariable("R", R).addMarkBlock(l, QColor(64, 0, 128)).addMarkBlock(m, Qt::yellow).setCompareBlocks((r <= R) ? r : -1, m));
	if(r <= R && T[r] > T[m])
	{
		instructions.push_back(Instruction(16, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", -11).addVariable("R", R).addMarkBlock(i, Qt::blue).addMarkBlock(m, Qt::yellow));
		m = r;
	}
	instructions.push_back(Instruction(18, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", m).addVariable("R", R).addMarkBlock(i, Qt::blue).addMarkBlock(l, QColor(64, 0, 128)).addMarkBlock(r, Qt::magenta));
	if(m != i)
	{
		instructions.push_back(Instruction(20, T, mCompareCounter, ++mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", m).addVariable("R", R).addMarkBlock(l, QColor(64, 0, 128)).addMarkBlock(r, Qt::magenta).setSwapBlocks(i, m));
		std::swap(T[i], T[m]);
		instructions.push_back(Instruction(21, T, mCompareCounter, mSwapCounter).addVariable("i", i).addVariable("l", l).addVariable("r", r).addVariable("m", m).addVariable("R", R).addMarkBlock(l, QColor(64, 0, 128)).addMarkBlock(r, Qt::magenta).addMarkBlock(m, Qt::yellow).setCurrentFunction(MaxHeapifyFunction));
		maxHeapify(T, R, m, instructions);
	}

	instructions.push_back(Instruction(23, T, mCompareCounter, mSwapCounter).addVariable("i", -11).addVariable("l", -11).addVariable("r", -11).addVariable("m", -11).addVariable("R", -11).addMarkBlock(i, Qt::blue).addMarkBlock(l, QColor(64, 0, 128)).addMarkBlock(r, Qt::magenta).setCurrentFunction(MaxHeapifyFunction));
}

void HeapSort::maxHeapify(QVector<int>& T, const int R, int i,  int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	int l = (i << 1) + 1;
	++instructionCounter;
	int r = (i << 1) + 2;
	int m;
	++instructionCounter;
	++instructionCounter;
	++compareCounter;
	if(l <= R && T[l] > T[i])
	{
		++instructionCounter;
		m = l;
	}
	else
	{
		++instructionCounter;
		m = i;
	}
	++compareCounter;
	if(r <= R && T[r] > T[m])
	{
		++instructionCounter;
		m = r;
	}
	++instructionCounter;
	if(m != i)
	{
		++instructionCounter;
		++swapCounter;
		std::swap(T[i], T[m]);
		++instructionCounter;
		maxHeapify(T, R, m, swapCounter, compareCounter, instructionCounter);
	}
}

void HeapSort::maxHeapify(int T[], const int R, int i)
{
	int l = (i << 1) + 1;

	int r = (i << 1) + 2;

	int m;

	if(l <= R && T[l] > T[i])
	{
		m = l;
	}
	else
	{
		m = i;
	}

	if(r <= R && T[r] > T[m])
	{
		m = r;
	}

	if(m != i)
	{
		std::swap(T[i], T[m]);

		maxHeapify(T, R, m);
	}
}
