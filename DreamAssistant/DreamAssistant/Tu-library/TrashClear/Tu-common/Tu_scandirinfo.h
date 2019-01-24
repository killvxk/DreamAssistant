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
	QStringList strDirectory;    // ����Ŀ¼
	QString strFriendName;       // ��ʾ����
	QStringList strExtArray;     // ��Ҫ���ҵ��ļ���չ��
	QStringList strFilt;         // Ҫ�����˵��ļ���

	bool bRecursive;             // �Ƿ������Ŀ¼
	bool bDefaultSelect;         // Ĭ��ѡ��
	bool bRSelect;               // �Ƽ�ѡ��

	QString iconName;            // ͼ������
	quint64 ulSize;

	int id;                      // ִ��id
	int parent;

	bool bIsLeaf;                // �Ƿ�ΪҶ�ӽڵ�
};

#endif // TU_SCANDIRINFO_H
