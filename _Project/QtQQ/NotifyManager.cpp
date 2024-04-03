#include "NotifyManager.h"
#include "CommonUtils.h"

// ��ʼ����̬��Ա���� instance�����ڱ��� NotifyManager ��ĵ���ʵ����Ĭ��Ϊ nullptr
NotifyManager* NotifyManager::instance = nullptr;

NotifyManager::NotifyManager()
	:QObject(nullptr) // ���� QObject �Ĺ��캯����������������Ϊ nullptr
{
}

NotifyManager::~NotifyManager()
{
}

// ��ȡ NotifyManager ��ĵ���ʵ��
NotifyManager* NotifyManager::getInstance()
{
	// ��� instance Ϊ nullptr���򴴽�һ���µ� NotifyManager ����
	if (instance == nullptr)
	{
		instance = new NotifyManager();
	}

	// ���ص���ʵ��
	return instance;
}

// ֪ͨ��������Ƥ����ɫ�ĸı�
void NotifyManager::notifyOtherWindowChangeSkin(const QColor& color)
{
	// ���� signalSkinChanged �źţ���������ɫ����
	emit signalSkinChanged(color);

	// ��Ĭ��Ƥ����ɫ����Ϊָ������ɫ
	CommonUtils::setDefaultSkinColor(color);

}
