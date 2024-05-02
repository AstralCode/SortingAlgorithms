#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include "SortingAlgorithm.hpp"

class MergeSort : public SortingAlgorithm
{
public:
	enum FunctionID
	{
		MergeSortFunction,
		MergeFunction
	};

	MergeSort();

	void run(const QVector<int>& array, QVector<Instruction>& instructions);
	void run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter);
	void run(int array[], const int size);

private:
	void setSourceCode();
	void setVariables();
	void mergeSort(QVector<int>& T, int p, int r, QVector<Instruction>& instructions);
	void mergeSort(QVector<int>& T, int p, int r, int& swapCounter, int& compareCounter, int& instructionCounter);
	void mergeSort(int T[], int p, int r);
	void merge(QVector<int>& T, int p, int q, int r, QVector<Instruction>& instructions);
	void merge(QVector<int>& T, int p, int q, int r, int& swapCounter, int& compareCounter, int& instructionCounter);
	void merge(int T[], int p, int q, int r);
};

#endif // MERGESORT_HPP
