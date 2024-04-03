#pragma once

#include "BasicWindow.h"
#include "EmotionWindow.h"
#include "TalkWindow.h"
#include "TalkWindowItem.h"
#include <QWidget>
#include <QMap>
#include "ui_TalkWindowShell.h"

class TalkWindow;
class TalkWindowItem;
class QListWidgetItem;
class EmotionWindow;

enum GroupType {
	COMPANY = 0, 
	PERSONELGROUP, 
	DEVELOPMENTGROUP, 
	MARKETGROUP, 
	PTOP 
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
	// 左侧对话窗口项点击槽函数
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
