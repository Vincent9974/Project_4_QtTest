#pragma once

#include <QtWidgets/QWidget>
#include "ui_CCMainWindow.h"
#include "BasicWindow.h"


class CCMainWindow : public BasicWindow
{
	Q_OBJECT

public:
	CCMainWindow(QWidget *parent = Q_NULLPTR);
	~CCMainWindow();

	void setUserName(const QString& username);
	void setLevelPixmap(int level);
	void setHeadPixmap(const QString& headPath);
	void setStatusMenuIcon(const QString& statusPath);
	//添加应用部件
	QWidget* addOtherAppExtension(const QString& appPath, const QString& appName);
	void initContactTree();

private:
	void resizeEvent(QResizeEvent* event);
	void updateSeachStyle();//更新搜索样式
	void initControl();
	void initTimer();//初始化计时器
	void addCompanyDeps(QTreeWidgetItem* pRootGroupItem, const QString& sDeps);
	void mousePressEvent(QMouseEvent* event);

private slots:
	void onAppIconClicked();
	bool eventFilter(QObject* obj, QEvent* event);
	void onItemClicked(QTreeWidgetItem* item, int column);
	void onItemExpanded(QTreeWidgetItem* item);
	void onItemCollapsed(QTreeWidgetItem* item);
	void onItemDoubleClicked(QTreeWidgetItem* item, int column);

private:
	Ui::CCMainWindowClass ui;
	QMap<QTreeWidgetItem*, QString> m_groupMap;
};
