#pragma once

#include <QtWidgets/QDialog>
#include "ui_QtQQ_Server.h" // ���� UI ���ͷ�ļ�
#include "TcpServer.h" // ���� TCP ���������ͷ�ļ�
#include <QSqlQueryModel> // �������ݿ��ѯģ�͵�ͷ�ļ�
#include <QTimer> // ������ʱ�����ͷ�ļ�
#include <QUdpSocket>

class QtQQ_Server : public QDialog
{
	Q_OBJECT // ʹ�� Qt ��Ԫ����ϵͳ

public:
	QtQQ_Server(QWidget *parent = Q_NULLPTR); // ���캯��

private:
	// ˽�к�������
	void initTcpSocket(); // ��ʼ�� TCP Socket
	void initUdpSocket(); //��ʼ��UDP	

	int getCompDepID(); // ��ȡ��˾���� QQ ��
	void updateTableData(int depID = 0, int employeeID = 0); // ���±������
	bool connectMySql(); // ���ӵ� MySQL ���ݿ�
	void initComboBoxData(); // ��ʼ������������
	void setDepNameMap(); // ���ò�������ӳ��
	void setStatusMap(); // ����״̬ӳ��
	void setOnlineMap(); // ��������״̬ӳ��

private slots:
	// ˽�вۺ�������
	void onUDPbroadMsg(QByteArray& btData); // ���� UDP �㲥��Ϣ�Ĳۺ���
	void onRefresh(); // ˢ�����ݵĲۺ���
	void on_queryDepartmentBtn_clicked(); // ��ѯ���ŵĲۺ���
	void on_queryIDBtn_clicked(); // ��ѯ ID �Ĳۺ���
	void on_logoutBtn_clicked(); //ע��Ա��QQ��
	void on_selectPictureBtn_clicked(); //ѡ��Ա�����յ���
	void on_addBtn_clicked(); //����Ա��
	

private:
	Ui::QtQQ_ServerClass ui; // UI �����

	QTimer* m_timer; // ��ʱ������
	int m_compDepID; // ��˾���� QQ ��
	int m_depID; // ���� QQ ��
	int m_employeeID; // Ա�� QQ ��
	QString m_pixPath; //ͷ��·��
	QMap<QString, QString> m_statusMap; // ״̬ӳ��
	QMap<QString, QString> m_depNameMap; // ��������ӳ��
	QMap<QString, QString> m_onlineMap; // ����״̬ӳ��
	QSqlQueryModel m_queryInfoModel; // ��ѯ����Ա����Ϣ
	TcpServer* m_tcpServer;    // TCP ����������
	QUdpSocket* m_udpSender;   // udp�㲥
};
