#include "Tu_upgradeprivilege.h"

#include <assert.h>
#include <string>
#include <aclapi.h>

// ʹ��key�ַ�����ʾ��ע������Ȩ��������SYSTEM��ADMINISTRATOR�˺Ŷ���KEY_ALL_ACCESS
// users�˺�����KEY_READ
BOOL UpgradePrivilege(LPCTSTR key, SE_OBJECT_TYPE objectType)
{
	if (NULL == key) {
		return FALSE;
	}

	LPTSTR ptstrKey = const_cast<LPTSTR>(key);
	PACL pNewDacl = NULL;
	PACL pOrgDacl = NULL;
	BOOL bRet = FALSE;
	BOOL bRetCode = FALSE;
	LONG lRet = 0;
	PSECURITY_DESCRIPTOR pSD = NULL;
	EXPLICIT_ACCESS eas[3] = { 0 };

	ACL_SIZE_INFORMATION aclSize = { 0 };
	ACCESS_DENIED_ACE* pACE = NULL;

	lRet = ::GetNamedSecurityInfo(ptstrKey, objectType, DACL_SECURITY_INFORMATION, NULL, NULL, &pOrgDacl, NULL, &pSD);

	if (ERROR_SUCCESS != lRet || NULL == pOrgDacl) { // ����ǹ����ļ�,��ȡ���ǿ�ָ��
		goto Exit0;
	}

	// �������е�acl,ȥ��denied_ace
	bool bContinue = true;

	while (bContinue)
	{
		bRetCode = ::GetAclInformation(pOrgDacl, &aclSize, sizeof(aclSize), AclSizeInformation);
		if (!bRetCode) {
			goto Exit0;
		}

		if (0 == aclSize.AceCount) {
			break;
		}

		for (ULONG lIndex = 0; lIndex < aclSize.AceCount; lIndex++)
		{
			pACE = NULL;
			if (!::GetAce(pOrgDacl, lIndex, (PVOID*)&pACE)) {
				goto Exit0;
			}

			if (pACE->Header.AceType == ACCESS_DENIED_ACE_TYPE) {
				if (0 == ::DeleteAce(pOrgDacl, lIndex)) { // ɾ��denied_ace
					goto Exit0;  // ʧ����
				} else {
					break;       // �ɹ��ˣ���ace����Ŀ������б仯��Ҫ���¿�ʼ��ѯ
				}
			}

			if (lIndex == aclSize.AceCount - 1) {
				bContinue = false;
			}
		}
	}

	DWORD  AdmAccessPermissions = 0;
	DWORD  SysAccessPermissions = 0;
	DWORD  UsrAccessPermissions = 0;

	if (objectType == SE_FILE_OBJECT) {
		AdmAccessPermissions = FILE_ALL_ACCESS;
		SysAccessPermissions = FILE_ALL_ACCESS;
		UsrAccessPermissions = FILE_GENERIC_READ | FILE_GENERIC_WRITE;
	} else if (objectType == SE_REGISTRY_KEY) {
		AdmAccessPermissions = KEY_ALL_ACCESS;
		SysAccessPermissions = KEY_ALL_ACCESS;
		UsrAccessPermissions = KEY_READ; // | KEY_WRITE;
	} else {
		// Ŀǰ objectType ֻ֧�ֲ���ע�����ļ���Ȩ��
		assert(0);
	}

	::BuildExplicitAccessWithName(&eas[0],
								  L"Administrators",
								  AdmAccessPermissions,
								  SET_ACCESS,
								  SUB_CONTAINERS_AND_OBJECTS_INHERIT);
	::BuildExplicitAccessWithName(&eas[1],
								  L"System",
								  SysAccessPermissions,
								  SET_ACCESS,
								  SUB_CONTAINERS_AND_OBJECTS_INHERIT);
	::BuildExplicitAccessWithName(&eas[2],
								  L"Users",
								  UsrAccessPermissions,
								  SET_ACCESS,
								  SUB_CONTAINERS_AND_OBJECTS_INHERIT);

	lRet = ::SetEntriesInAcl(3, eas, pOrgDacl, &pNewDacl);
	if (ERROR_SUCCESS != lRet)
		goto Exit0;

	lRet = ::SetNamedSecurityInfo(ptstrKey,
								  objectType,
								  DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION,
								  NULL, NULL, pNewDacl, NULL);

	if (ERROR_SUCCESS != lRet) {
		goto Exit0;
	}

	bRet = TRUE;

Exit0:
	if (NULL != pNewDacl) {
		::LocalFree(pNewDacl);
	}

	if (NULL != pSD) {
		::LocalFree(pSD);
	}

	return bRet;
}

BOOL UpgradePrivilege(HKEY hKey, LPTSTR lpSubKey)
{
	std::wstring tstrKey;

	if (hKey == HKEY_LOCAL_MACHINE)
		tstrKey = L"MACHINE\\";
	else if (hKey == HKEY_CURRENT_USER)
		tstrKey = L"CURRENT_USER\\";
	else if (hKey == HKEY_CLASSES_ROOT)
		tstrKey = L"CLASSES_ROOT\\";
	else if (hKey == HKEY_USERS)
		tstrKey = L"USERS\\";
	else if (HKEY_CURRENT_CONFIG)
		tstrKey = L"CONFIG\\";
	else
		return FALSE;

	if (lpSubKey)
		tstrKey += lpSubKey;

	return UpgradePrivilege(tstrKey.c_str(), SE_REGISTRY_KEY);
}
