#include "InformationWindow.hpp"

#include <QLabel>
#include <QDate>
#include <QIcon>
#include <QVBoxLayout>
#include <QHBoxLayout>

InformationWindow::InformationWindow() :
	QDialog{nullptr, Qt::MSWindowsFixedSizeDialogHint},
	mIconLabel{new QLabel},
	mMainTitleLabel{new QLabel},
	mInformationLabel{new QLabel}
{
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(QStringLiteral("Informacje"));
	setWindowIcon(QIcon(QStringLiteral(":/Resources/Information.png")));
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setContextMenuPolicy(Qt::NoContextMenu);

	createWidgets();
	createLayout();

	exec();
}

void InformationWindow::createWidgets()
{
	mIconLabel->setPixmap(QPixmap(QStringLiteral(":/Resources/Ascending.png")));

	mMainTitleLabel->setTextFormat(Qt::RichText);
	mMainTitleLabel->setTextInteractionFlags(Qt::NoTextInteraction);
	mMainTitleLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	mMainTitleLabel->setText(
		"<p><span style=\" font-size:14pt; font-weight:600;\">Algorytmy sortowania</span></p>"
		"<p><span style=\" font-size:8pt;\">Komputerowy Program Dydaktyczny</span></p>"
	);

	mInformationLabel->setTextFormat(Qt::RichText);
	mInformationLabel->setTextInteractionFlags(Qt::NoTextInteraction);
	mInformationLabel->setAlignment(Qt::AlignHCenter);
	mInformationLabel->setText(QStringLiteral("<p><span style=\"font-size:10pt;\">Bartosz Górski</span></p>"));
}

void InformationWindow::createLayout()
{
	QFrame* line = new QFrame;
	line->setFrameShape(QFrame::HLine);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setSpacing(6);
	mainLayout->setContentsMargins(10, 10, 10, 10);

	QHBoxLayout* topSideLayout = new QHBoxLayout;
	topSideLayout->setSpacing(15);
	topSideLayout->addWidget(mIconLabel);
	topSideLayout->addWidget(mMainTitleLabel);
	topSideLayout->addStretch();

	mainLayout->addLayout(topSideLayout);
	mainLayout->addWidget(line);
	mainLayout->addWidget(mInformationLabel);

	setLayout(mainLayout);
}
