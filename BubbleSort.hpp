#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

#include "SortingAlgorithm.hpp"

class BubbleSort : public SortingAlgorithm
{
public:
	enum FunctionID
	{
		BubbleSortFunction
	};

	BubbleSort();

	void run(const QVector<int>& array, QVector<Instruction>& instructions);
	void run(const QVector<int>& array, int& swapCounter, int& compareCounter, int& instructionCounter);
	void run(int array[], const int Size);

private:
	void setSourceCode();
	void setVariables();
};

#endif // BUBBLESORT_HPP
