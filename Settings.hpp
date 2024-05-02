#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QVector>

#include "SortingAlgorithmType.hpp"

struct Settings
{
	static constexpr auto ArrayFixedSize = 10;
	static constexpr auto ArrayMaximumValue = 10;

	Settings();

	SortingAlgorithmType mSortingAlgorithm;
	QVector<int> mArray;
	bool mRepeatedValues;
};

inline Settings::Settings() :
	mSortingAlgorithm{SortingAlgorithmType::BubbleSort},
	mArray{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}},
	mRepeatedValues{false}
{

}

#endif // SETTINGS_HPP
