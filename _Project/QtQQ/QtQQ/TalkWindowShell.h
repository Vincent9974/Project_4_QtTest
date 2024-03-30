#pragma once

#include "ui_TalkWindowShell.h"
#include "BasicWindow.h"

#include <QWidget> // 包含QWidget头文件
#include <QMap> // 包含QMap头文件
#include "ui_TalkWindowShell.h" // 包含对话窗口外壳UI头文件

// 前置声明
class TalkWindow;
class TalkWindowItem;
class QListWidgetItem;
class EmotionWindow;

// 分组类型枚举
enum GroupType {
	COMPANY = 0, // 公司群组
	PERSONELGROUP, // 个人群组
	DEVELOPMENTGROUP, // 开发组
	MARKETGROUP, // 市场组
	PTOP // 同行之间私聊
};

class TalkWindowShell : public BasicWindow // 对话窗口外壳类，继承自基本窗口类
{
	Q_OBJECT

public:
	TalkWindowShell(QWidget *parent = Q_NULLPTR); // 构造函数
	~TalkWindowShell(); // 析构函数

public:
	// 添加新的对话窗口
	void addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, GroupType groupType);

	// 设置当前窗口部件
	void setCurrentWidget(QWidget* widget);

	// 获取对话窗口项映射
	const QMap<QListWidgetItem*, QWidget*>& getTalkWindowItemMap() const; // 获取对话窗口项映射

private:
	void initControl(); // 初始化控件方法

public slots:
	// 表情按钮点击槽函数
	void onEmotionBtnClicked(bool);

private slots:
	// 对话窗口项点击槽函数
	void onTalkWindowItemClicked(QListWidgetItem* item);

	// 表情项点击槽函数
	void onEmotionItemClicked(int emotionNum);

private:
	// 对话窗口项映射
	QMap<QListWidgetItem*, QWidget*> m_talkwindowItemMap;

	// 表情窗口指针
	EmotionWindow* m_emotionWindow;

	Ui::TalkWindowClass ui; // 对话窗口UI对象
};
