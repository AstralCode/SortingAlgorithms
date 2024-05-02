#ifndef SOURCELINE_HPP
#define SOURCELINE_HPP

#include <QString>
#include <QVector>
#include <QList>

class SourceLine
{
public:
	SourceLine() = default;
	SourceLine(int indentSize, const QString& line);

	SourceLine& setLine(const QString& line);
	SourceLine& setIndentSize(int indentSize);

	int getIndentSize() const;

	operator QString() const
	{
		return mLine;
	}

	SourceLine& operator =(const QString& line)
	{
		mLine = line;

		return *this;
	}

private:
	int mIndentSize;
	QString mLine;
};

#endif // SOURCELINE_HPP
