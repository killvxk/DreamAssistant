#ifndef TU_OPERATORREGEDIT_H
#define TU_OPERATORREGEDIT_H

#include <QString>
#include <windows.h>

class OPeratorRegedit
{
public:
	static LONG regOpenKeyExPrvg(HKEY hKey, QString lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);
	static HRESULT getRegistryValue(HKEY hRootKey, const QString contpszSubKeyName, const QString pszValueName,
							 DWORD* pdwType, BYTE* pszValue, DWORD* puValueSize);
};

#endif // TU_OPERATORREGEDIT_H
