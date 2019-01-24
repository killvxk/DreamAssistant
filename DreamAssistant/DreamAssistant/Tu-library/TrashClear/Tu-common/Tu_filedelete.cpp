#include "Tu_filedelete.h"
#include "./Tu-common/Tu_trashdefine.h"

FileDelete::FileDelete()
{

}

FileDelete::~FileDelete()
{

}

int FileDelete::TrashFileDelete(const QString pszFullName)
{
	int nResult = -1;
	DWORD dwNewAttributes = 0;

	if (pszFullName.isEmpty()) {
		nResult = Delete_File_Failed;
		return nResult;
	}

	dwNewAttributes = ::GetFileAttributes(pszFullName.toStdWString().c_str());
	if (INVALID_FILE_ATTRIBUTES == dwNewAttributes) {
		nResult = Delete_File_Failed;
		return nResult;
	}

	// 去掉文件只读属性
	if (dwNewAttributes & FILE_ATTRIBUTE_READONLY) {
		dwNewAttributes &= ~FILE_ATTRIBUTE_READONLY;
	}

	::SetFileAttributes(pszFullName.toStdWString().c_str(), dwNewAttributes);
	nResult = ::DeleteFile(pszFullName.toStdWString().c_str());

	if (nResult)
		nResult = Delete_File_Success;
	else
		nResult = Delete_File_Failed;

	if (ERROR_FILE_NOT_FOUND == GetLastError())
		nResult = Delete_File_Success;

	return nResult;
}

bool FileDelete::MoveFile(QString lpExistingFileName, QString lpNewFileName, DWORD dwFlags)
{
	return ::MoveFileEx(lpExistingFileName.toStdWString().c_str(), lpNewFileName.toStdWString().c_str(), dwFlags);
}