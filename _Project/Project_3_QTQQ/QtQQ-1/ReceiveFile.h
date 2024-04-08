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

	// 信息，根据传入的字符串进行设置
	void setMsg(QString& msgLabel);



signals:
	void refuseFile();		// 拒绝

private slots:
	void on_okBtn_clicked();		// 确定
	void on_cancelBtn_clicked();	// 取消

private:
	Ui::ReceiveFile ui;
};
