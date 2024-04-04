#pragma once

#include <QWidget>
#include "TalkWindowShell.h"  // ���� TalkWindowShell ���ͷ�ļ�

#include "ui_TalkWindow.h"  // �������ɵ� UI �ļ���ͷ�ļ�

extern enum GroupType; 

class TalkWindow : public QWidget
{
	Q_OBJECT

public:
	TalkWindow(QWidget* parent, const QString& uid/*, GroupType groupType*/);  // ���캯�������ܸ�����ָ�롢UID �� GroupType ����
	~TalkWindow();  // ��������

public:
	void addEmotionImage(int emotionNum);  // ��ӱ���ͼ��ķ��������� emotionNum ����
	void setWindowName(const QString& name);  // ���ô������Ƶķ��������� name ����
	QString getTalkID();

private:
	void initControl();   // ��ʼ���ؼ���˽�з���
	void initGroupTalkStatus();
	int getCompDepID();  // ��ȡ����ID

	//void initCompanyTalk();  // ��ʼ����˾Ⱥ�����˽�з���
	//void initPersonelTalk();  // ��ʼ�����������˽�з���
	//void initDevelopmentTalk();  // ��ʼ���з����������˽�з���
	//void initMarketTalk();  // ��ʼ���г����������˽�з���

	void initPtoPTalk();   //��ʼ������
	void initTalkWindow(); //��ʼ��Ⱥ��
	


	void addPeopInfo(QTreeWidgetItem* pRootGroupItem,int employeeID);  // �����Ա��Ϣ��˽�з��������� QTreeWidgetItem ָ�����

private slots:
	void onSendBtnClicked(bool);  // ���Ͱ�ť����Ĳۺ��������ܲ����Ͳ���
	void onItemDoubleClicked(QTreeWidgetItem* item, int column);  // ��Ŀ˫���Ĳۺ��������� QTreeWidgetItem ָ��������в���

private:
	Ui::TalkWindow ui;  // UI �������

	QString m_talkId;   // ���촰�� ID

	bool m_isGroupTalk; //�Ƿ�Ⱥ��


	//GroupType m_groupType;  // ���촰��Ⱥ������

	// ���촰��Ⱥ������Աӳ��
	// ��ΪȺ���е� QTreeWidgetItem ָ�룬ֵΪ��Ӧ����Ա����
	QMap<QTreeWidgetItem*, QString> m_groupPeoMap;


};
