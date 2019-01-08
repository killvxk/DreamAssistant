#include "Tu_shredfile.h"
#include <QApplication>
#include <QDesktopWidget>

ShredFile::ShredFile(QObject *parent)
    :QObject(parent), shred_dialog(this)
{

}

ShredFile::~ShredFile()
{

}

QString ShredFile::getGuid()
{
    return "DREAM-SHRED";
}

QString ShredFile::getName()
{
    return tr("Shred File");
}

QString ShredFile::getDescribe()
{
    return tr("Delete files makes it unable to recover");
}

QString ShredFile::getPicture()
{
    return "shredder.png";
}

void ShredFile::doAction()
{
    int windowWidth = QApplication::desktop()->width();
    int windowHeight = QApplication::desktop()->height();

    shred_dialog.resetSkin();
    shred_dialog.move((windowWidth - 500) / 2, (windowHeight - 471) / 2);
    shred_dialog.show();
    shred_dialog.raise();
}
