#include "NotifyManager.h"
#include "CommonUtils.h"

// 初始化静态成员变量 instance，用于保存 NotifyManager 类的单例实例，默认为 nullptr
NotifyManager* NotifyManager::instance = nullptr;

NotifyManager::NotifyManager()
	:QObject(nullptr) // 调用 QObject 的构造函数，将父对象设置为 nullptr
{
}

NotifyManager::~NotifyManager()
{
}

// 获取 NotifyManager 类的单例实例
NotifyManager* NotifyManager::getInstance()
{
	// 如果 instance 为 nullptr，则创建一个新的 NotifyManager 对象
	if (instance == nullptr)
	{
		instance = new NotifyManager();
	}

	// 返回单例实例
	return instance;
}

// 通知其他窗口皮肤颜色的改变
void NotifyManager::notifyOtherWindowChangeSkin(const QColor& color)
{
	// 发射 signalSkinChanged 信号，并传递颜色参数
	emit signalSkinChanged(color);

	// 将默认皮肤颜色设置为指定的颜色
	CommonUtils::setDefaultSkinColor(color);

}
