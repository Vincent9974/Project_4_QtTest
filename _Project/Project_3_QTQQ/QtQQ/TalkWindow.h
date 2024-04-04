#pragma once

#include <QWidget>
#include "TalkWindowShell.h"  // 包含 TalkWindowShell 类的头文件

#include "ui_TalkWindow.h"  // 包含生成的 UI 文件的头文件

extern enum GroupType; 

class TalkWindow : public QWidget
{
	Q_OBJECT

public:
	TalkWindow(QWidget* parent, const QString& uid/*, GroupType groupType*/);  // 构造函数，接受父部件指针、UID 和 GroupType 参数
	~TalkWindow();  // 析构函数

public:
	void addEmotionImage(int emotionNum);  // 添加表情图像的方法，接受 emotionNum 参数
	void setWindowName(const QString& name);  // 设置窗口名称的方法，接受 name 参数
	QString getTalkID();

private:
	void initControl();   // 初始化控件的私有方法
	void initGroupTalkStatus();
	int getCompDepID();  // 获取部门ID

	//void initCompanyTalk();  // 初始化公司群聊天的私有方法
	//void initPersonelTalk();  // 初始化个人聊天的私有方法
	//void initDevelopmentTalk();  // 初始化研发部门聊天的私有方法
	//void initMarketTalk();  // 初始化市场部门聊天的私有方法

	void initPtoPTalk();   //初始化单聊
	void initTalkWindow(); //初始化群聊
	


	void addPeopInfo(QTreeWidgetItem* pRootGroupItem,int employeeID);  // 添加人员信息的私有方法，接受 QTreeWidgetItem 指针参数

private slots:
	void onSendBtnClicked(bool);  // 发送按钮点击的槽函数，接受布尔型参数
	void onItemDoubleClicked(QTreeWidgetItem* item, int column);  // 项目双击的槽函数，接受 QTreeWidgetItem 指针和整数列参数

private:
	Ui::TalkWindow ui;  // UI 界面对象

	QString m_talkId;   // 聊天窗口 ID

	bool m_isGroupTalk; //是否群聊


	//GroupType m_groupType;  // 聊天窗口群组类型

	// 聊天窗口群组与人员映射
	// 键为群组中的 QTreeWidgetItem 指针，值为相应的人员名称
	QMap<QTreeWidgetItem*, QString> m_groupPeoMap;


};
