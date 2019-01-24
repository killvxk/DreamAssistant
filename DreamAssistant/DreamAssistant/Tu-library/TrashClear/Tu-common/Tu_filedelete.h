#ifndef TU_FILEDELETE_H
#define TU_FILEDELETE_H

#include <QString>
#include <windows.h>
#include "../Tu-core/Tu_singleton.h"

class FileDelete
{
	SINGLETON(FileDelete)
public:
	int TrashFileDelete(const QString pszFullName);
	bool MoveFile(QString lpExistingFileName, QString lpNewFileName, DWORD dwFlags);
};

#endif // TU_FILEDELETE_H
