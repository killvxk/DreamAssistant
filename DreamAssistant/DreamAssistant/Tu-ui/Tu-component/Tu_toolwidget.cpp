#include "Tu_toolwidget.h"
#include <QHBoxLayout>
#include <QSignalMapper>

ToolWidget::ToolWidget(QWidget *parent)
	: QWidget(parent)
{
	setFixedSize(900, 47);
	setAutoFillBackground(true);

	QPalette palette;
	palette.setColor(QPalette::Background, QColor(233, 238, 241)); //#e9eef1
	this->setPalette(palette);

	QStringList icon_list;
	QStringList text_list;
	icon_list << ":/res/tool/home" << ":/res/tool/cleanup" << ":/res/tool/evaluation" << ":/res/tool/feature" << ":/res/tool/toolkits";
	text_list << tr("Home") << tr("Cleanup") << tr("Evaluation") << tr("Feature") << tr("Toolkits");

	QHBoxLayout *button_layout = new QHBoxLayout;
	QSignalMapper *signal_mapper = new QSignalMapper(this);
	for (int i = 0; i < icon_list.size(); i++) {
		ToolButton *tool_button = new ToolButton(icon_list.at(i), text_list.at(i));
		tool_button->setFixedSize(180, 47);
		button_list.append(tool_button);
		connect(tool_button, &ToolButton::clicked, signal_mapper, static_cast<void(QSignalMapper::*)(void)>(&QSignalMapper::map));

		signal_mapper->setMapping(tool_button, QString::number(i, 10));
		button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
	}
	this->switchSelectedPageIndex(0);
	connect(signal_mapper, static_cast<void(QSignalMapper::*)(const QString &)>(&QSignalMapper::mapped), this, &ToolWidget::switchSelectedPageIndex);

	button_layout->addStretch();
	button_layout->setSpacing(8);
	button_layout->setMargin(0);
	button_layout->setContentsMargins(15, 0, 15, 0);

	setLayout(button_layout);
}

ToolWidget::~ToolWidget()
{

}

void ToolWidget::switchSelectedPageIndex(QString index)
{
	bool ok;
	int current_index = index.toInt(&ok, 10);

	for (int i = 0; i < button_list.count(); i++) {
		ToolButton *tool_button = button_list.at(i);
		if (current_index == i) {
			tool_button->setMousePress(true);
		} else {
			tool_button->setMousePress(false);
		}
	}
	emit sig_turnCurrentPage(current_index);
}

void ToolWidget::showBoxTool()
{
	this->switchSelectedPageIndex("4");
}

