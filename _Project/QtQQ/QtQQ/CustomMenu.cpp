#include "CustomMenu.h"
#include "CommonUtils.h"

CustomMenu::CustomMenu(QWidget *parent)
	: QMenu(parent)
{
	setAttribute(Qt::WA_TranslucentBackground); // ���ò˵�Ϊ͸������
	CommonUtils::loadStyleSheet(this, "Menu"); // ����˵�����ʽ��
}

CustomMenu::~CustomMenu()
{
}

void CustomMenu::addCustomMenu(const QString & text, const QString & icon, QString & name)
{
	// ����µ��Զ���˵������ͼ�������
	QAction* pAction = addAction(QIcon(icon), name);
	m_menuActionMap.insert(text, pAction); // ���˵����ı��Ͷ�Ӧ�� QAction ָ�����ӳ����

}

QAction * CustomMenu::getAction(const QString & text)
{
	return m_menuActionMap[text];
}
