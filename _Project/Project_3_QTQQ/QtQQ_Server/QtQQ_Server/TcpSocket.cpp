#include "TcpSocket.h"

TcpSocket::TcpSocket()
{
}

TcpSocket::~TcpSocket()
{
}

void TcpSocket::run()
{
	// 获取当前套接字的描述符（套接字描述符是操作系统分配给套接字的唯一标识符）
	m_descriptor = this->socketDescriptor();

	// 连接 readyRead() 信号到 onReceiveData() 槽函数，用于处理接收到的数据
	connect(this, SIGNAL(readyRead()), this, SLOT(onReceiveData()));
	// 连接 disconnected() 信号到 onClientDisconnect() 槽函数，用于处理客户端断开连接的情况
	connect(this, SIGNAL(disconnected()), this, SLOT(onClientDisconnect()));
}

void TcpSocket::onClientDisconnect()
{
	emit signalClientDisconnect(m_descriptor);
}

void TcpSocket::onReceiveData()
{
	// 读取套接字中的所有可用数据
	QByteArray buffer = this->readAll();

	// 如果接收到的数据不为空
	if (!buffer.isEmpty())
	{
		// 将接收到的数据转换为字符串（使用本地字符集）
		QString strData = QString::fromLocal8Bit(buffer);

		// 发送接收到了客户端数据的信号
		emit signalGetDataFromClient(buffer, m_descriptor);
	}

}


