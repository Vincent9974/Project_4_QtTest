#pragma once

#include <QMenu>
#include <QMap>
class CustomMenu : public QMenu
{
	Q_OBJECT

public:
	CustomMenu(QWidget *parent=nullptr);
	~CustomMenu();
public:
	// 添加自定义菜单项的方法
	// text：菜单项显示的文本
	// icon：菜单项显示的图标
	// Name：菜单项的名称
	void addCustomMenu(const QString& text, const QString& icon, QString& name);

	// 获取指定文本的菜单项的方法
	QAction* getAction(const QString& text); // 通过菜单项的显示文本获取菜单项

private:
	// 储存菜单项的映射，键为菜单项的文本，值为对应的 QAction 指针
	QMap<QString, QAction*> m_menuActionMap;
};
