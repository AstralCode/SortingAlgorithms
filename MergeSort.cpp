#include "MergeSort.hpp"

#include "Instruction.hpp"


MergeSort::MergeSort() :
	SortingAlgorithm{QStringLiteral("Sortowanie przez scalanie")}
{
	setSourceCode();
	setVariables();
}

void MergeSort::run(const QVector<int>& array, QVector<Instruction>& instructions)
{
	QVector<int> T(array);

	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter, 0, T.size() - 1).addVariable("i", -11).addVariable("j", -11).addVariable("p", 0).addVariable("r", array.size() - 1).addVariable("k", -11).addVariable("q", -11).addVariable("x", -11).addVariable("y", -11).setCurrentFunction(MergeSortFunction));
	mergeSort(T, 0, array.size() - 1, instructions);
}

void MergeSort::run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	QVector<int> T(array);

	++instructionCounter;
	mergeSort(T, 0, array.size() - 1, swapCounter, compareCounter, instructionCounter);
}

void MergeSort::run(int array[], const int size)
{
	mergeSort(array, 0, size - 1);
}

void MergeSort::setSourceCode()
{
	QList<SourceLine> mergeSortFunctionSourceLines;

	mergeSortFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void mergeSort(int T[], int p, int r)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"if(p < r)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"int q = (p + r) / 2;"))
	<< SourceLine(2, QStringLiteral(		"mergeSort(T, p, q);"))
	<< SourceLine(2, QStringLiteral(		"mergeSort(T, q + 1, r);"))
	<< SourceLine(2, QStringLiteral(		"merge(T, p, q, r);"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(mergeSortFunctionSourceLines);

	QList<SourceLine> mergeFunctionSourceLines;

	mergeFunctionSourceLines
	<< SourceLine(0, QStringLiteral("void merge(int T[], int p, int q, int r)"))
	<< SourceLine(0, QStringLiteral("{"))
	<< SourceLine(1, QStringLiteral(	"const int x = q - p + 1;"))
	<< SourceLine(1, QStringLiteral(	"const int y = r - q;"))
	<< SourceLine(1, QStringLiteral(	"int* L = new int[x + 1];"))
	<< SourceLine(1, QStringLiteral(	"int* R = new int[y + 1];"))
	<< SourceLine(1, QStringLiteral(	"for(int i = 0; i < x; ++i)"))
	<< SourceLine(2, QStringLiteral(		"L[i] = T[p + i];"))
	<< SourceLine(1, QStringLiteral(	"for(int i = 0; i < y; ++i)"))
	<< SourceLine(2, QStringLiteral(		"R[i] = T[q + 1 + i];"))
	<< SourceLine(1, QStringLiteral(	"L[x] = R[y] = INT_MAX;"))
	<< SourceLine(1, QStringLiteral(	"int i = 0, j = 0, k = p;"))
	<< SourceLine(1, QStringLiteral(	"while(k <= r)"))
	<< SourceLine(1, QStringLiteral(	"{"))
	<< SourceLine(2, QStringLiteral(		"if(L[i] <= R[j])"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"T[k] = L[i];"))
	<< SourceLine(3, QStringLiteral(			"++i;"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(2, QStringLiteral(		"else"))
	<< SourceLine(2, QStringLiteral(		"{"))
	<< SourceLine(3, QStringLiteral(			"T[k] = R[j];"))
	<< SourceLine(3, QStringLiteral(			"++j;"))
	<< SourceLine(2, QStringLiteral(		"}"))
	<< SourceLine(2, QStringLiteral(		"++k;"))
	<< SourceLine(1, QStringLiteral(	"}"))
	<< SourceLine(0, QStringLiteral("}"));

	mSourceCode.push_back(mergeFunctionSourceLines);
}

void MergeSort::setVariables()
{
	mVariableInfoList
	<< VariableInformation(QStringLiteral("i"), Qt::blue)
	<< VariableInformation(QStringLiteral("j"), Qt::yellow)
	<< VariableInformation(QStringLiteral("p"), Qt::transparent)
	<< VariableInformation(QStringLiteral("r"), Qt::transparent)
	<< VariableInformation(QStringLiteral("k"), Qt::transparent)
	<< VariableInformation(QStringLiteral("q"), QColor(64, 0, 128))
	<< VariableInformation(QStringLiteral("x"), Qt::transparent)
	<< VariableInformation(QStringLiteral("y"), Qt::transparent);
}

void MergeSort::mergeSort(QVector<int>& T, int p, int r, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", -11).addVariable("x", -11).addVariable("y", -11).setCurrentFunction(MergeSortFunction));
	if(p < r)
	{
		instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", -11).addVariable("x", -11).addVariable("y", -11));
		int q = (p + r) / 2;
		instructions.push_back(Instruction(6, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", -11).addVariable("y", -11).addMarkBlock(q, QColor(64, 0, 128)));
		mergeSort(T, p, q, instructions);
		instructions.push_back(Instruction(7, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", -11).addVariable("y", -11).addMarkBlock(q, QColor(64, 0, 128)));
		mergeSort(T, q + 1, r, instructions);
		instructions.push_back(Instruction(8, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", -11).addVariable("y", -11).addMarkBlock(q, QColor(64, 0, 128)).addMarkBlock(q, QColor(64, 0, 128)).setCurrentFunction(MergeSortFunction));
		merge(T, p, q, r, instructions);
	}
	instructions.push_back(Instruction(10, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", -11).addVariable("r", -11).addVariable("k", -11).addVariable("q", -11).addVariable("x", -11).addVariable("y", -11).setCurrentFunction(MergeSortFunction));
}

void MergeSort::mergeSort(QVector<int>& T, int p, int r, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	if(p < r)
	{
		++instructionCounter;
		int q = (p + r) / 2;
		++instructionCounter;
		mergeSort(T, p, q, swapCounter, compareCounter, instructionCounter);
		++instructionCounter;
		mergeSort(T, q + 1, r, swapCounter, compareCounter, instructionCounter);
		++instructionCounter;
		merge(T, p, q, r, swapCounter, compareCounter, instructionCounter);
	}
}

void MergeSort::mergeSort(int array[], int p, int r)
{
	if(p < r)
	{
		int q = (p + r) / 2;

		mergeSort(array, p, q);

		mergeSort(array, q + 1, r);

		merge(array, p, q, r);
	}
}

void MergeSort::merge(QVector<int>& T, int p, int q, int r, QVector<Instruction>& instructions)
{
	instructions.push_back(Instruction(1, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", -11).addVariable("y", -11).setCurrentFunction(MergeFunction));

	instructions.push_back(Instruction(3, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", -11).addVariable("y", -11));
	const int x = q - p + 1;
	instructions.push_back(Instruction(4, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", -11));
	const int y = r - q;
	instructions.push_back(Instruction(5, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	int* L = new int[x + 1];
	instructions.push_back(Instruction(6, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	int* R = new int[y + 1];
	instructions.push_back(Instruction(7, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", 0).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	for(int i = 0; i < x; ++i)
	{
		instructions.push_back(Instruction(8, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
		L[i] = T[p + i];
		instructions.push_back(Instruction(7, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i + 1).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	}
	instructions.push_back(Instruction(9, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", 0).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	for(int i = 0; i < y; ++i)
	{
		instructions.push_back(Instruction(10, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
		R[i] = T[q + 1 + i];
		instructions.push_back(Instruction(9, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i + 1).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	}
	instructions.push_back(Instruction(11, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	L[x] = R[y] = INT_MAX;
	instructions.push_back(Instruction(12, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", p).addVariable("r", r).addVariable("k", -11).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	int i = 0, j = 0, k = p;
	instructions.push_back(Instruction(13, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("k", k = p).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	while(k <= r)
	{
		instructions.push_back(Instruction(15, T, ++mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("k", k).addVariable("q", q).addVariable("x", x).addVariable("y", y).setCompareBlocks((p + i) < (x + 1) ? p + i : -1, (q + 1 + j) < (y + 1) ? q + 1 + j : -1));
		if(L[i] <= R[j])
		{
			instructions.push_back(Instruction(17, T, mCompareCounter, ++mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("k", k).addVariable("q", q).addVariable("x", x).addVariable("y", y).setSwapBlocks(k, p + i));
			T[k] = L[i];
			instructions.push_back(Instruction(18, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("k", k).addVariable("q", q).addVariable("x", x).addVariable("y", y));
			++i;
		}
		else
		{
			instructions.push_back(Instruction(22, T, mCompareCounter, ++mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("k", k).addVariable("q", q).addVariable("x", x).addVariable("y", y).setSwapBlocks(k, q + 1 + j));
			T[k] = R[j];
			instructions.push_back(Instruction(23, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("k", k).addVariable("q", q).addVariable("x", x).addVariable("y", y));
			++j;
		}
		instructions.push_back(Instruction(25, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("k", k).addVariable("q", q).addVariable("x", x).addVariable("y", y));
		++k;
		instructions.push_back(Instruction(13, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", i).addVariable("j", j).addVariable("p", p).addVariable("r", r).addVariable("k", k).addVariable("q", q).addVariable("x", x).addVariable("y", y));
	}

	delete [] L;

	delete [] R;
	instructions.push_back(Instruction(27, T, mCompareCounter, mSwapCounter, p, r).addVariable("i", -11).addVariable("j", -11).addVariable("p", -11).addVariable("r", -11).addVariable("k", -11).addVariable("q", -11).addVariable("x", -11).addVariable("y", -11).setCurrentFunction(MergeFunction));
}

void MergeSort::merge(QVector<int>& T, int p, int q, int r, int& swapCounter, int& compareCounter, int& instructionCounter)
{
	++instructionCounter;
	const int x = q - p + 1;
	++instructionCounter;
	const int y = r - q;
	++instructionCounter;
	int* L = new int[x + 1];
	++instructionCounter;
	int* R = new int[y + 1];
	++instructionCounter;
	for(int i = 0; i < x; ++i)
	{
		++instructionCounter;
		L[i] = T[p + i];
		++instructionCounter;
		++instructionCounter;
	}
	++instructionCounter;
	for(int i = 0; i < y; ++i)
	{
		++instructionCounter;
		R[i] = T[q + 1 + i];
		++instructionCounter;
		++instructionCounter;
	}
	++instructionCounter;
	L[x] = R[y] = INT_MAX;
	++instructionCounter;
	int i = 0, j = 0, k = p;
	++instructionCounter;
	while(k <= r)
	{
		++instructionCounter;
		++compareCounter;
		if(L[i] <= R[j])
		{
			++instructionCounter;
			++swapCounter;
			T[k] = L[i];
			++instructionCounter;
			++i;
		}
		else
		{
			++instructionCounter;
			++swapCounter;
			T[k] = R[j];
			++instructionCounter;
			++j;
		}
		++instructionCounter;
		++k;
		++instructionCounter;
	}
}

void MergeSort::merge(int T[], int p, int q, int r)
{
	const int x = q - p + 1;

	const int y = r - q;

	int* L = new int[x + 1];

	int* R = new int[y + 1];

	for(int i = 0; i < x; ++i)
	{
		L[i] = T[p + i];
	}

	for(int i = 0; i < y; ++i)
	{
		R[i] = T[q + 1 + i];
	}

	L[x] = R[y] = INT_MAX;

	int i = 0, j = 0, k = p;

	while(k <= r)
	{
		if(L[i] <= R[j])
		{
			T[k] = L[i];

			++i;
		}
		else
		{
			T[k] = R[j];

			++j;
		}
		++k;
	}

	delete [] L;

	delete [] R;
}
