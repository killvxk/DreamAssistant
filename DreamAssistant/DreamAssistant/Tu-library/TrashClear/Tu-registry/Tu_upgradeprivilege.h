#ifndef TU_UPGRADEPRIVILEGE_H
#define TU_UPGRADEPRIVILEGE_H

#include "accctrl.h"

BOOL UpgradePrivilege(LPCTSTR key, SE_OBJECT_TYPE objectType);

BOOL UpgradePrivilege(HKEY hKey, LPTSTR lpSubKey);

#endif // TU_UPGRADEPRIVILEGE_H
