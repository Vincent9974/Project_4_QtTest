#pragma once

#include <QtWidgets/QWidget>
#include "ui_CCMainWindow.h"
#include "BasicWindow.h"


class CCMainWindow : public BasicWindow
{
	Q_OBJECT

public:
	CCMainWindow(QString account,bool isAccountLogin, QWidget *parent = Q_NULLPTR);
	~CCMainWindow();

	void setUserName(const QString& username);
	void setLevelPixmap(int level);
	void setHeadPixmap(const QString& headPath);
	void setStatusMenuIcon(const QString& statusPath);
	//���Ӧ�ò���
	QWidget* addOtherAppExtension(const QString& appPath, const QString& appName);
	void initContactTree();

private:
	void resizeEvent(QResizeEvent* event);
	void updateSeachStyle();//����������ʽ
	void initControl();
	QString getHeadPicturePath();
	void initTimer();//��ʼ����ʱ��
	void addCompanyDeps(QTreeWidgetItem* pRootGroupItem, int DepID);
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
	//QMap<QTreeWidgetItem*, QString> m_groupMap;

	bool m_isAccountLogin;
	QString m_account;    
};
