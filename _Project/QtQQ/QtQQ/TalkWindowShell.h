#pragma once

#include "BasicWindow.h"
#include "EmotionWindow.h"
#include "TalkWindow.h"
#include "TalkWindowItem.h"
#include <QWidget>
#include <QMap>
#include "ui_TalkWindowShell.h"

class TalkWindow;
class TalkWindowItem;
class QListWidgetItem;
class EmotionWindow;

enum GroupType {
	COMPANY = 0, 
	PERSONELGROUP, 
	DEVELOPMENTGROUP, 
	MARKETGROUP, 
	PTOP 
};

class TalkWindowShell : public BasicWindow // �Ի���������࣬�̳��Ի���������
{
	Q_OBJECT

public:
	TalkWindowShell(QWidget *parent = Q_NULLPTR); // ���캯��
	~TalkWindowShell(); // ��������

public:
	// ����µĶԻ�����
	void addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, GroupType groupType);

	// ���õ�ǰ���ڲ���
	void setCurrentWidget(QWidget* widget);


	// ��ȡ�Ի�������ӳ��
	const QMap<QListWidgetItem*, QWidget*>& getTalkWindowItemMap() const; // ��ȡ�Ի�������ӳ��

private:
	void initControl(); // ��ʼ���ؼ�����

public slots:
	// ���鰴ť����ۺ���
	void onEmotionBtnClicked(bool);

private slots:
	// ���Ի����������ۺ���
	void onTalkWindowItemClicked(QListWidgetItem* item);

	// ���������ۺ���
	void onEmotionItemClicked(int emotionNum);


private:
	// �Ի�������ӳ��
	QMap<QListWidgetItem*, QWidget*> m_talkwindowItemMap;

	// ���鴰��ָ��
	EmotionWindow* m_emotionWindow;

	Ui::TalkWindowClass ui; // �Ի�����UI����
};
