#pragma once

#include "BasicWindow.h"
#include "ui_ReceiveFile.h"
#include "TalkWindowShell.h"

class ReceiveFile : public BasicWindow
{
	Q_OBJECT

public:
	ReceiveFile(QWidget *parent = Q_NULLPTR);
	~ReceiveFile();

	// ��Ϣ�����ݴ�����ַ�����������
	void setMsg(QString& msgLabel);



signals:
	void refuseFile();		// �ܾ�

private slots:
	void on_okBtn_clicked();		// ȷ��
	void on_cancelBtn_clicked();	// ȡ��

private:
	Ui::ReceiveFile ui;
};
