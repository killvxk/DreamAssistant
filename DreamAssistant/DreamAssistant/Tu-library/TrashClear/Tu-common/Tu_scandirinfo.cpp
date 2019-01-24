#include "Tu_scandirinfo.h"
#include <QtAlgorithms>

ScanDirInfo::ScanDirInfo()
{
	bDefaultSelect = false; 
	bRSelect = false;      
}

ScanDirInfo::~ScanDirInfo()
{

}

void ScanDirInfo::clear()
{
	strDirectory.clear();
	strFriendName = ""; 
	strExtArray.clear();  
	strFilt.clear();; 
}

ScanDirInfo::ScanDirInfo(const ScanDirInfo& cpy)
{
	for (int i = 0; i < cpy.strDirectory.count(); ++i) {
		strDirectory.append(cpy.strDirectory.value(i));
	}

	for (int i = 0; i < cpy.strExtArray.count(); ++i) {
		strExtArray.append(cpy.strExtArray.value(i));
	}

	for (int i = 0; i < cpy.strFilt.count(); ++i) {
		strFilt.append(cpy.strFilt.value(i));
	}

	strFriendName  = cpy.strFriendName;
	bRecursive     = cpy.bRecursive;
	bDefaultSelect = cpy.bDefaultSelect;
	bRSelect       = cpy.bRSelect;
	iconName       = cpy.iconName;
	ulSize         = cpy.ulSize;
	id             = cpy.id;
	parent         = cpy.parent;
	bIsLeaf        = cpy.bIsLeaf;
}

ScanDirInfo& ScanDirInfo::operator= (const ScanDirInfo& cpy)
{
	for (int i = 0; i < cpy.strDirectory.count(); ++i) {
		strDirectory.append(cpy.strDirectory.value(i));
	}

	for (int i = 0; i < cpy.strExtArray.count(); ++i) {
		strExtArray.append(cpy.strExtArray.value(i));
	}

	for (int i = 0; i < cpy.strFilt.count(); ++i) {
		strFilt.append(cpy.strFilt.value(i));
	}

	strFriendName  = cpy.strFriendName;
	bRecursive     = cpy.bRecursive;
	bDefaultSelect = cpy.bDefaultSelect;
	bRSelect       = cpy.bRSelect;
	iconName       = cpy.iconName;
	ulSize         = cpy.ulSize;
	id             = cpy.id;
	parent         = cpy.parent;
	bIsLeaf        = cpy.bIsLeaf;

	return *this;
}

