#ifndef SORTINGALGORITHM_HPP
#define SORTINGALGORITHM_HPP

#include <QSharedPointer>

#include "SourceLine.hpp"
#include "VariableInformation.hpp"

class Instruction;

class SortingAlgorithm
{
public:
	using Ptr = QSharedPointer<SortingAlgorithm>;

	SortingAlgorithm(const QString& name);
	virtual ~SortingAlgorithm() = default;

	virtual void run(const QVector<int>& array, QVector<Instruction>& instructions) = 0;
	virtual void run(const QVector<int> &array, int& swapCounter, int& compareCounter, int& instructionCounter) = 0;
	virtual void run(int array[], const int size) = 0;

	const QString& getName() const;
	const QVector<QList<SourceLine>>& getSourceCode() const;
	const QList<VariableInformation>& getVariableInformationList() const;

protected:
	virtual void setSourceCode() = 0;
	virtual void setVariables() = 0;

protected:
	QString mName;
	QVector<QList<SourceLine> > mSourceCode;
	QList<VariableInformation> mVariableInfoList;
	int mCompareCounter;
	int mSwapCounter;
};

#endif // SORTINGALGORITHM_HPP
