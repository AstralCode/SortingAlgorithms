#ifndef SORTINGALGORITHMTYPE_HPP
#define SORTINGALGORITHMTYPE_HPP

#include <QVariant>

enum class SortingAlgorithmType
{
	InsertionSort,
	SelectionSort,
	BubbleSort,
	MergeSort,
	HeapSort,
	QuickSortHoare,
	QuickSortLomuto
};

Q_DECLARE_METATYPE(SortingAlgorithmType)

#endif // SORTINGALGORITHMTYPE_HPP
