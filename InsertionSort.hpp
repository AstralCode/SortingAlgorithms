#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

#include "SortingAlgorithm.hpp"

class InsertionSort : public SortingAlgorithm
{
public:
	enum FunctionID
	{
		InsertionSortFunction
	};

	InsertionSort();

	void run(const QVector<int>& array, QVector<Instruction>& instructions);
	void run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter);
	void run(int array[], const int size);

private:
	void setSourceCode();
	void setVariables();
};

#endif // INSERTIONSORT_HPP
