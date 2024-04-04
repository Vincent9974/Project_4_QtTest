#include "CustomMenu.h"
#include "CommonUtils.h"

CustomMenu::CustomMenu(QWidget *parent)
	: QMenu(parent)
{
	setAttribute(Qt::WA_TranslucentBackground); // 设置菜单为透明背景
	CommonUtils::loadStyleSheet(this, "Menu"); // 载入菜单的样式表
}

CustomMenu::~CustomMenu()
{
}

void CustomMenu::addCustomMenu(const QString & text, const QString & icon, QString & name)
{
	// 添加新的自定义菜单项，包括图标和名称
	QAction* pAction = addAction(QIcon(icon), name);
	m_menuActionMap.insert(text, pAction); // 将菜单项文本和对应的 QAction 指针插入映射中

}

QAction * CustomMenu::getAction(const QString & text)
{
	return m_menuActionMap[text];
}
