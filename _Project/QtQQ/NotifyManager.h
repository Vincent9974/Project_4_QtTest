#pragma once

#include <QObject>

class NotifyManager : public QObject
{
	Q_OBJECT

public:
	NotifyManager();
	~NotifyManager();

signals:
	// ����һ����Ϊ signalSkinChanged ���źţ�����֪ͨƤ����ɫ�ĸı�
	void signalSkinChanged(const QColor& color);

public:
	// ��̬���������ڻ�ȡ NotifyManager ��ĵ���ʵ��
	static NotifyManager* getInstance();

	// ֪ͨ��������Ƥ����ɫ�ĸı�
	void notifyOtherWindowChangeSkin(const QColor& color);

private:
	// ���� NotifyManager ��ĵ���ʵ���ľ�ָ̬��
	static NotifyManager* instance;
};
