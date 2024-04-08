#pragma once

#include <QtWidgets/QDialog>
#include "ui_QtQQ_Server.h" // 包含 UI 类的头文件
#include "TcpServer.h" // 包含 TCP 服务器类的头文件
#include <QSqlQueryModel> // 包含数据库查询模型的头文件
#include <QTimer> // 包含定时器类的头文件
#include <QUdpSocket>

class QtQQ_Server : public QDialog
{
	Q_OBJECT // 使用 Qt 的元对象系统

public:
	QtQQ_Server(QWidget *parent = Q_NULLPTR); // 构造函数

private:
	// 私有函数声明
	void initTcpSocket(); // 初始化 TCP Socket
	void initUdpSocket(); //初始化UDP	

	int getCompDepID(); // 获取公司部门 QQ 号
	void updateTableData(int depID = 0, int employeeID = 0); // 更新表格数据
	bool connectMySql(); // 连接到 MySQL 数据库
	void initComboBoxData(); // 初始化下拉框数据
	void setDepNameMap(); // 设置部门名称映射
	void setStatusMap(); // 设置状态映射
	void setOnlineMap(); // 设置在线状态映射

private slots:
	// 私有槽函数声明
	void onUDPbroadMsg(QByteArray& btData); // 处理 UDP 广播消息的槽函数
	void onRefresh(); // 刷新数据的槽函数
	void on_queryDepartmentBtn_clicked(); // 查询部门的槽函数
	void on_queryIDBtn_clicked(); // 查询 ID 的槽函数
	void on_logoutBtn_clicked(); //注销员工QQ号
	void on_selectPictureBtn_clicked(); //选择员工寸照店铺
	void on_addBtn_clicked(); //新增员工
	

private:
	Ui::QtQQ_ServerClass ui; // UI 类对象

	QTimer* m_timer; // 定时器对象
	int m_compDepID; // 公司部门 QQ 号
	int m_depID; // 部门 QQ 号
	int m_employeeID; // 员工 QQ 号
	QString m_pixPath; //头像路径
	QMap<QString, QString> m_statusMap; // 状态映射
	QMap<QString, QString> m_depNameMap; // 部门名称映射
	QMap<QString, QString> m_onlineMap; // 在线状态映射
	QSqlQueryModel m_queryInfoModel; // 查询所有员工信息
	TcpServer* m_tcpServer;    // TCP 服务器对象
	QUdpSocket* m_udpSender;   // udp广播
};
