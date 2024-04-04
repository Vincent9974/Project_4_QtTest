#pragma once

#include <QObject>

class NotifyManager : public QObject
{
	Q_OBJECT

public:
	NotifyManager();
	~NotifyManager();

signals:
	// 声明一个名为 signalSkinChanged 的信号，用于通知皮肤颜色的改变
	void signalSkinChanged(const QColor& color);

public:
	// 静态方法，用于获取 NotifyManager 类的单例实例
	static NotifyManager* getInstance();

	// 通知其他窗口皮肤颜色的改变
	void notifyOtherWindowChangeSkin(const QColor& color);

private:
	// 保存 NotifyManager 类的单例实例的静态指针
	static NotifyManager* instance;
};
