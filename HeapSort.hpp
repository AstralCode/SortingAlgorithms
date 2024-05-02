#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include "SortingAlgorithm.hpp"

class HeapSort : public SortingAlgorithm
{
public:
	enum FunctionID
	{
		HeapSortFunction,
		BuildMaxHeapFunction,
		MaxHeapifyFunction
	};

	HeapSort();

	void run(const QVector<int>& array, QVector<Instruction>& instructions);
	void run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter);
	void run(int array[], const int size);

private:
	void setSourceCode();
	void setVariables();
	void heapSort(QVector<int>& T, const int R, QVector<Instruction>& instructions);
	void heapSort(QVector<int>& T, const int R, int& swapCounter, int& compareCounter, int& instructionCounter);
	void heapSort(int T[], const int R);
	void buildMaxHeap(QVector<int>& T, const int R, QVector<Instruction>& instructions);
	void buildMaxHeap(QVector<int>& T, const int R, int& swapCounter, int& compareCounter, int& instructionCounter);
	void buildMaxHeap(int T[], const int R);
	void maxHeapify(QVector<int>& T, const int R, int i, QVector<Instruction>& instructions);
	void maxHeapify(QVector<int>& T, const int R, int i, int& swapCounter, int& compareCounter, int& instructionCounter);
	void maxHeapify(int T[], const int R, int i);
};

#endif // HEAPSORT_HPP
