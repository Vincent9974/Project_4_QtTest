#pragma once

#include <QObject>

#include "BasicWindow.h"  // ���� BasicWindow ���ͷ�ļ�
#include "ui_UserLogin.h" // ���� UserLogin ��� UI ͷ�ļ�

class UserLogin : public BasicWindow // ���� UserLogin �࣬�̳��� BasicWindow ��
{
	Q_OBJECT // ʹ�� Qt ��Ԫ����ϵͳ

public:
	UserLogin(QWidget *parent = Q_NULLPTR); // ���캯��������һ�� QWidget* ���͵� parent ������Ĭ��Ϊ��ָ��
	~UserLogin(); // ��������

private slots:
	void onLoginBtnClicked(); // �ۺ����������¼��ť����¼�

private:
	void initControl(); // ��ʼ���ؼ���˽�к���

private:
	Ui::UserLogin ui; // UserLogin ��� UI ����
};