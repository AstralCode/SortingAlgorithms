#include "SourceLine.hpp"


SourceLine::SourceLine(int indentSize, const QString& line) :
	mIndentSize{indentSize},
	mLine{line}
{

}

SourceLine& SourceLine::setLine(const QString& line)
{
	mLine = line;

	return *this;
}

SourceLine& SourceLine::setIndentSize(int indentSize)
{
	mIndentSize = indentSize;

	return *this;
}

int SourceLine::getIndentSize() const
{
	return mIndentSize;
}
