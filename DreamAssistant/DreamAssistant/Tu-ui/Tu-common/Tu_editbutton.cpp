#include "Tu_editbutton.h"
#include <QHBoxLayout>
#include <QLineEdit>

EditButton::EditButton(QLineEdit *edit)
	: QPushButton(edit)
{
	QSize size = QSize(40, edit->sizeHint().height());

	setFocusPolicy(Qt::NoFocus);
	setFlat(true);
	setIcon(QIcon(":/res/plugins/shred/folder.png"));
	setIconSize(QSize(16, 16));
	setCursor(QCursor(Qt::PointingHandCursor));

	QHBoxLayout *layout = new QHBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addStretch();
	layout->addWidget(this);

	edit->setLayout(layout);
	edit->setTextMargins(0, 1, size.width(), 1);
}
