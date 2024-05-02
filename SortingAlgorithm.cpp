#include "SortingAlgorithm.hpp"


SortingAlgorithm::SortingAlgorithm(const QString& name) :
	mName{name},
	mCompareCounter{0},
	mSwapCounter{0}
{

}

const QString& SortingAlgorithm::getName() const
{
	return mName;
}

const QVector<QList<SourceLine> >& SortingAlgorithm::getSourceCode() const
{
	return mSourceCode;
}

const QList<VariableInformation>& SortingAlgorithm::getVariableInformationList() const
{
	return mVariableInfoList;
}
