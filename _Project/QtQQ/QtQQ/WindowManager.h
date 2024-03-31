#pragma once

#include <QObject>
#include "TalkWindowShell.h"

// 声明窗口管理器类
class WindowManager : public QObject
{
	Q_OBJECT

public:
	// 构造函数和析构函数
	WindowManager();
	~WindowManager();

public:
	// 查找窗口对象
	QWidget* findWindowName(const QString& qsWindowName);

	// 删除窗口对象
	void deleteWindowName(const QString& qsWindowName);

	// 添加窗口对象
	void addWindowName(const QString& qsWindowName, QWidget* qWidget);

	// 添加新的聊天窗口
	// uid：用户ID，groupType：群组类型，默认为公司，strPeople：人员信息，默认为空
	void addNewTalkWindow(const QString& uid, GroupType groupType = COMPANY, const QString& strPeople = "");

	// 获取窗口管理器实例
	static WindowManager* getInstance();

private:
	// 聊天窗口管理器对象指针
	TalkWindowShell* m_talkwindowshell;

	// 窗口对象映射，键为窗口名称，值为窗口对象指针
	QMap<QString, QWidget*> m_windowMap;
};
