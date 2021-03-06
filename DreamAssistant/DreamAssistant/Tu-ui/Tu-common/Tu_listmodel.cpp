#include "Tu_listmodel.h"
#include <QIcon>

ListModel::ListModel()
{

}

ListModel::~ListModel()
{

}

QModelIndex	ListModel::index(int row, int column, const QModelIndex & parent) const
{
	if (row >= 0 && row < rowCount() && column >= 0 && column < columnCount()) {
		QStandardItem* item = m_data.at(row);
		return createIndex(row, column, (void *)(item));
	}

	return QModelIndex();
}

int ListModel::rowCount(const QModelIndex & parent) const
{
	return m_data.count();
}

int ListModel::columnCount(const QModelIndex & parent) const
{
	return m_title.count();
}

bool ListModel::insertRows(int row, int count, const QModelIndex & parent)
{
	beginInsertRows(QModelIndex(), row, row + count - 1);
	for (int i = 0; i < count; ++i) {
		QStandardItem *item = new QStandardItem();
		m_data.insert(row, item);
	}
	endInsertRows();

	return true;
}

bool ListModel::insertColumns(int column, int count, const QModelIndex &)
{
	return true;
}

bool ListModel::removeRows(int row, int count, const QModelIndex & parent)
{
	return true;
}

bool ListModel::removeColumns(int column, int count, const QModelIndex & parent)
{
	return true;
}

QVariant ListModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	if (role == Qt::DisplayRole) {
		QStandardItem* item = m_data.at(index.row());
		return QVariant(item->text());
	}

	if (role == Qt::DecorationRole) {
		QStandardItem* item = m_data.at(index.row());
		return QVariant(item->icon());
	}

	if (role == Qt::WhatsThisRole) {
		QStandardItem* item = m_data.at(index.row());
		return item->toolTip();
	}

	return QVariant();
}

bool ListModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (index.isValid() && role == Qt::EditRole) {
		QStandardItem* item = m_data.at(index.row());
		item->setText(value.toString());
		emit dataChanged(index, index);
		return true;
	}

	if (role == Qt::DecorationRole) {
		QStandardItem* item = m_data.at(index.row());
		item->setIcon(value.value<QIcon>());
		return true;
	}

	if (role == Qt::WhatsThisRole) {
		QStandardItem* item = m_data.at(index.row());
		item->setToolTip(value.toString());
		return true;
	}

	return false;
}

QVariant ListModel::headerData(int section, Qt::Orientation  orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		return m_title.at(0);
	}

	return QVariant();
}

