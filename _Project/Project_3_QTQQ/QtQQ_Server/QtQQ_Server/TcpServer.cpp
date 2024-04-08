#include "TcpServer.h"
#include <QTcpSocket>
#include "TcpSocket.h"

TcpServer::TcpServer(int port) : m_port(port)
{
}

TcpServer::~TcpServer()
{
}

bool TcpServer::run()
{
	// 尝试监听指定端口的连接
	if (this->listen(QHostAddress::AnyIPv4, m_port))
	{
		// 如果监听成功，输出成功信息并返回 true
		qDebug() << QString::fromLocal8Bit("服务器成功监听端口 %1").arg(m_port);
		return true;
	}
	else
	{
		// 如果监听失败，输出失败信息并返回 false
		qDebug() << QString::fromLocal8Bit("服务器监听端口 %1 失败!").arg(m_port);
		return false;
	}
}


void TcpServer::incomingConnection(qintptr socketDescriptor)
{
	qDebug() << QString::fromLocal8Bit("新连接：") << socketDescriptor << endl;

	// 创建一个新的 TcpSocket 对象来处理新连接
	TcpSocket* tcpsocket = new TcpSocket();
	tcpsocket->setSocketDescriptor(socketDescriptor);
	tcpsocket->run();


	// 将信号与槽连接起来，以处理来自客户端的数据
	connect(tcpsocket, SIGNAL(signalGetDataFromClient(QByteArray&, int)),
		this, SLOT(SocketDataProcessing(QByteArray&, int)));

	// 将信号与槽连接起来，以处理客户端断开连接的情况
	connect(tcpsocket, SIGNAL(signalClientDisconnect(int)),
		this, SLOT(SocketDisconnected(int)));

	// 将新的 TcpSocket 对象添加到连接列表中
	m_tcpSocketConnectList.append(tcpsocket);
}


void TcpServer::SocketDisconnected(int descriptor)
{
	for (int i = 0; i < m_tcpSocketConnectList.count(); ++i)
	{
		QTcpSocket *item = m_tcpSocketConnectList.at(i);
		int itemDescriptor = item->socketDescriptor();

		//查找断开连接的socket
		if (itemDescriptor == descriptor || itemDescriptor == -1)
		{
			m_tcpSocketConnectList.removeAt(i);//断开的socket从链表中移除
			item->deleteLater();//回收资源
			qDebug() << QString::fromLocal8Bit("TcpSocket断开连接：") << descriptor << endl;
			return;
		}
	}
}

void TcpServer::SocketDataProcessing(QByteArray& SendData, int descriptor)
{
	
	for (int i = 0; i < m_tcpSocketConnectList.count(); ++i)
	{
		QTcpSocket *item = m_tcpSocketConnectList.at(i);
		if (item->socketDescriptor() == descriptor)
		{
			qDebug() << QString::fromLocal8Bit("来自IP:") << item->peerAddress().toString()
					 << QString::fromLocal8Bit("发来的数据：") << QString(SendData);

			emit signalTcpMsgComes(SendData);
		}
	}
}