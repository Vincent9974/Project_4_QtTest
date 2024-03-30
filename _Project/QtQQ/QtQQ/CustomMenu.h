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
	// ����Զ���˵���ķ���
	// text���˵�����ʾ���ı�
	// icon���˵�����ʾ��ͼ��
	// Name���˵��������
	void addCustomMenu(const QString& text, const QString& icon, QString& name);

	// ��ȡָ���ı��Ĳ˵���ķ���
	QAction* getAction(const QString& text); // ͨ���˵������ʾ�ı���ȡ�˵���

private:
	// ����˵����ӳ�䣬��Ϊ�˵�����ı���ֵΪ��Ӧ�� QAction ָ��
	QMap<QString, QAction*> m_menuActionMap;
};
