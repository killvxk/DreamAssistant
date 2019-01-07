#ifndef TU_COMMON_H
#define TU_COMMON_H

#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>

inline QString sizeToString(int size)
{
	float trashSize = 0;
	QString text;

    if (size > 1024 * 1024 * 1024) {
        trashSize = size / (float)(1024 * 1024 * 1024);
        text = QString::number(trashSize, 'f', 2).append("TB");
    } else if(size > 1024 * 1024) {
		trashSize = size / (float)(1024 * 1024);
		text = QString::number(trashSize, 'f', 2).append("GB");
	} else if (size > 1024) {
		trashSize = size / (float)1024;
		text = QString::number(trashSize, 'f', 2).append("MB");
	} else {
		text = QString::number(size).append("KB");
	}

	return text;
}

inline QStringList filterSkin()
{
    QStringList skinlist;
    QString path = QCoreApplication::applicationDirPath().append("/skin/default/");
    QString path2 = QCoreApplication::applicationDirPath().append("/skin/custom/");

    QDir picdir(path);
    picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    picdir.setSorting(QDir::Size | QDir::Reversed);

    QDir picdir2(path2);
    picdir2.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    picdir2.setSorting(QDir::Size | QDir::Reversed);

    QStringList filters;
    filters << "*.jpg" << "*.png";
    picdir.setNameFilters(filters);
    picdir2.setNameFilters(filters);

    QFileInfoList list = picdir.entryInfoList();
    QFileInfoList list2 = picdir2.entryInfoList();

    if (list.size() > 0 && list2.size() > 0) {
        for (int j = 0; j < list.size(); ++j) {
            QFileInfo fileInfo = list.at(j);
            skinlist << path + fileInfo.fileName();
        }
        for (int k = 0; k < list2.size(); ++k) {
            QFileInfo fileInfo = list2.at(k);
            skinlist << path2 + fileInfo.fileName();
        }
    } else {
        if (list.size() > 0) {
            for (int j = 0; j < list.size(); ++j) {
                QFileInfo fileInfo = list.at(j);
                skinlist << path + fileInfo.fileName();
            }
        } else if (list2.size() > 0) {
            for (int m = 0; m < list2.size(); ++m) {
                QFileInfo fileInfo = list2.at(m);
                skinlist << path2 + fileInfo.fileName();
            }
        }
    }
    return skinlist;
}

inline QString appStyle()
{
    QFile qss(":/res/dream.qss");
    qss.open(QFile::ReadOnly);
    QString style = qss.readAll();
    qss.close();

    return style;
}

#endif // TU_COMMON_H
