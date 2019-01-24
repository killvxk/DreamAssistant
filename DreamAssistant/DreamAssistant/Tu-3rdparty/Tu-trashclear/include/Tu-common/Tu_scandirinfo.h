#ifndef TU_SCANDIRINFO_H
#define TU_SCANDIRINFO_H

#include <QStringList>

class ScanDirInfo
{
public:
	ScanDirInfo();
	~ScanDirInfo();

	ScanDirInfo(const ScanDirInfo& cpy);
	ScanDirInfo& operator= (const ScanDirInfo& cpy);

	void clear();

public:
	QStringList strDirectory;    // 查找目录
	QString strFriendName;       // 显示名称
	QStringList strExtArray;     // 需要查找的文件扩展名
	QStringList strFilt;         // 要被过滤的文件夹

	bool bRecursive;             // 是否查找子目录
	bool bDefaultSelect;         // 默认选项
	bool bRSelect;               // 推荐选项

	QString iconName;            // 图标名称
	quint64 ulSize;

	int id;                      // 执行id
	int parent;

	bool bIsLeaf;                // 是否为叶子节点
};

#endif // TU_SCANDIRINFO_H
