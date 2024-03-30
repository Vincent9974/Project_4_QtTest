#pragma once

#include "ui_TalkWindowShell.h"
#include "BasicWindow.h"

#include <QWidget> // ����QWidgetͷ�ļ�
#include <QMap> // ����QMapͷ�ļ�
#include "ui_TalkWindowShell.h" // �����Ի��������UIͷ�ļ�

// ǰ������
class TalkWindow;
class TalkWindowItem;
class QListWidgetItem;
class EmotionWindow;

// ��������ö��
enum GroupType {
	COMPANY = 0, // ��˾Ⱥ��
	PERSONELGROUP, // ����Ⱥ��
	DEVELOPMENTGROUP, // ������
	MARKETGROUP, // �г���
	PTOP // ͬ��֮��˽��
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
	// �Ի����������ۺ���
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
