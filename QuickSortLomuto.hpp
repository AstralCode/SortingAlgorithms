#ifndef QUICKSORTLOMUTO_HPP
#define QUICKSORTLOMUTO_HPP

#include "SortingAlgorithm.hpp"

class QuickSortLomuto : public SortingAlgorithm
{
public:
	enum FunctionID
	{
		QuickSortFunction,
		PartitionFunction
	};

	QuickSortLomuto();

	void run(const QVector<int>& array, QVector<Instruction>& instructions);
	void run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter);
	void run(int array[], const int size);

private:
	void setSourceCode();
	void setVariables();
	void quickSort(QVector<int>& T, int p, int r, QVector<Instruction>& instructions);
	void quickSort(QVector<int>& T, int p, int r, int& swapCounter, int& compareCounter, int& instructionCounter);
	void quickSort(int T[], int p, int r);
	int partition(QVector<int>& T, int p, int r, QVector<Instruction>& instructions);
	int partition(QVector<int>& T, int p, int r, int& swapCounter, int& compareCounter, int& instructionCounter);
	int partition(int T[], int p, int r);
};

#endif // QUICKSORTLOMUTO_HPP
