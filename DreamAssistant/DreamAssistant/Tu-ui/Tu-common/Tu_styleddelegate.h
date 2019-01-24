#ifndef TU_STYLEDDELEGATE_H
#define TU_STYLEDDELEGATE_H

#include <QStyledItemDelegate>

class StyledDelegate : public QStyledItemDelegate
{
	Q_OBJECT
public:
	explicit StyledDelegate(QWidget *parent = Q_NULLPTR);
	~StyledDelegate();

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TU_STYLEDDELEGATE_H
