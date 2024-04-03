#pragma once

#include <QObject>
#include "TalkWindowShell.h"

// �������ڹ�������
class WindowManager : public QObject
{
	Q_OBJECT

public:
	// ���캯������������
	WindowManager();
	~WindowManager();

public:
	// ���Ҵ��ڶ���
	QWidget* findWindowName(const QString& qsWindowName);

	// ɾ�����ڶ���
	void deleteWindowName(const QString& qsWindowName);

	// ��Ӵ��ڶ���
	void addWindowName(const QString& qsWindowName, QWidget* qWidget);

	// ����µ����촰��
	// uid���û�ID��groupType��Ⱥ�����ͣ�Ĭ��Ϊ��˾��strPeople����Ա��Ϣ��Ĭ��Ϊ��
	void addNewTalkWindow(const QString& uid, GroupType groupType = COMPANY, const QString& strPeople = "");

	// ��ȡ���ڹ�����ʵ��
	static WindowManager* getInstance();

private:
	// ���촰�ڹ���������ָ��
	TalkWindowShell* m_talkwindowshell;

	// ���ڶ���ӳ�䣬��Ϊ�������ƣ�ֵΪ���ڶ���ָ��
	QMap<QString, QWidget*> m_windowMap;
};
