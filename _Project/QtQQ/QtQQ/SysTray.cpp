#include "SysTray.h"
#include "CustomMenu.h"

SysTray::SysTray(QWidget *parent)
	: m_parent(parent)
	,QSystemTrayIcon(parent)
{
	initSystemTray();
	show();
}

SysTray::~SysTray()
{
}


void SysTray::initSystemTray() // 初始化系统托盘图标的方法
{
	// 设置系统托盘图标的提示信息
	setToolTip(QStringLiteral("QQ-Vincent"));

	// 设置系统托盘图标的图标
	setIcon(QIcon(":/Resources/MainWindow/app/logo.ico"));

	// 连接系统托盘图标的激活事件到对应的槽函数
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(onIconActivated(QSystemTrayIcon::ActivationReason)));
}

void SysTray::addSystrayMenu()
{
	CustomMenu* customMenu = new CustomMenu(m_parent);
	// 向自定义菜单中添加菜单项，并设置图标和文本
	customMenu->addCustomMenu("onShow", ":/Resources/MainWindow/app/logo.ico",
		QStringLiteral("显示"));
	customMenu->addCustomMenu("onQuit", ":/Resources/MainWindow/app/page_close_btn_hover.png",
		QStringLiteral("退出"));

	// 连接菜单项的触发事件到对应的槽函数
	connect(customMenu->getAction("onShow"), SIGNAL(triggered(bool)),
		m_parent, SLOT(onShowNormal(bool)));
	connect(customMenu->getAction("onQuit"), SIGNAL(triggered(bool)),
		m_parent, SLOT(onShowQuit(bool)));
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		m_parent, SLOT(showNormal())); // 双击系统托盘图标显示窗口


	// 在鼠标右键点击位置弹出自定义菜单
	customMenu->exec(QCursor::pos());

	// 释放自定义菜单的内存，避免内存泄漏
	delete customMenu;
	customMenu = nullptr;
}


void SysTray::onIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger)
	{
		m_parent->show();
		m_parent->activateWindow();
	}
	else if (reason == QSystemTrayIcon::Context)
	{
		addSystrayMenu();
	}
}
