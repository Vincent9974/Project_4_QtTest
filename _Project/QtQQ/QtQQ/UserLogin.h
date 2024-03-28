#pragma once

#include <QObject>

#include "BasicWindow.h"  // 包含 BasicWindow 类的头文件
#include "ui_UserLogin.h" // 包含 UserLogin 类的 UI 头文件

class UserLogin : public BasicWindow // 定义 UserLogin 类，继承自 BasicWindow 类
{
	Q_OBJECT // 使用 Qt 的元对象系统

public:
	UserLogin(QWidget *parent = Q_NULLPTR); // 构造函数，接受一个 QWidget* 类型的 parent 参数，默认为空指针
	~UserLogin(); // 析构函数

private slots:
	void onLoginBtnClicked(); // 槽函数，处理登录按钮点击事件

private:
	void initControl(); // 初始化控件的私有函数

private:
	Ui::UserLogin ui; // UserLogin 类的 UI 对象
};