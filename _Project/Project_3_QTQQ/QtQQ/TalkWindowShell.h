#pragma once

#include "BasicWindow.h"
#include "EmotionWindow.h"
#include "TalkWindow.h"
#include "TalkWindowItem.h"
#include <QWidget>
#include <QMap>
#include "ui_TalkWindowShell.h"
#include <QTcpSocket>

class TalkWindow;
class TalkWindowItem;
class QListWidgetItem;
class EmotionWindow;

// TCP 
const int gtcpPort = 8888;
// UDP 
const int gudpPort = 6666;

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
	void addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, const QString& uid/*, GroupType groupType*/);

	// ���õ�ǰ���ڲ���
	void setCurrentWidget(QWidget* widget);


	// ��ȡ�Ի�������ӳ��
	const QMap<QListWidgetItem*, QWidget*>& getTalkWindowItemMap() const; // ��ȡ�Ի�������ӳ��

private:
	void initControl(); // ��ʼ���ؼ�����
	void initTcpSocket(); //��ʼ��TCP
	void getEmployeeID(QStringList& employeesList);//��ȡ����Ա��QQ��ID
	bool createJSFile(QStringList& employeeList);  

public slots:
	// ���鰴ť����ۺ���
	void onEmotionBtnClicked(bool);
	// �ͻ��˷���TCP����(����,��������,�ļ�)
	void updateSendTcpMsg(QString& strData, int &msgType, QString fileName ="");

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

private:
	QTcpSocket *m_tcpClientSocket;   //TCP�ͻ���
};
