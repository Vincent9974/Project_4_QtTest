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
	// ���Լ���ָ���˿ڵ�����
	if (this->listen(QHostAddress::AnyIPv4, m_port))
	{
		// ��������ɹ�������ɹ���Ϣ������ true
		qDebug() << QString::fromLocal8Bit("�������ɹ������˿� %1").arg(m_port);
		return true;
	}
	else
	{
		// �������ʧ�ܣ����ʧ����Ϣ������ false
		qDebug() << QString::fromLocal8Bit("�����������˿� %1 ʧ��!").arg(m_port);
		return false;
	}
}


void TcpServer::incomingConnection(qintptr socketDescriptor)
{
	qDebug() << QString::fromLocal8Bit("�����ӣ�") << socketDescriptor << endl;

	// ����һ���µ� TcpSocket ����������������
	TcpSocket* tcpsocket = new TcpSocket();
	tcpsocket->setSocketDescriptor(socketDescriptor);
	tcpsocket->run();


	// ���ź���������������Դ������Կͻ��˵�����
	connect(tcpsocket, SIGNAL(signalGetDataFromClient(QByteArray&, int)),
		this, SLOT(SocketDataProcessing(QByteArray&, int)));

	// ���ź���������������Դ���ͻ��˶Ͽ����ӵ����
	connect(tcpsocket, SIGNAL(signalClientDisconnect(int)),
		this, SLOT(SocketDisconnected(int)));

	// ���µ� TcpSocket ������ӵ������б���
	m_tcpSocketConnectList.append(tcpsocket);
}


void TcpServer::SocketDisconnected(int descriptor)
{
	for (int i = 0; i < m_tcpSocketConnectList.count(); ++i)
	{
		QTcpSocket *item = m_tcpSocketConnectList.at(i);
		int itemDescriptor = item->socketDescriptor();

		//���ҶϿ����ӵ�socket
		if (itemDescriptor == descriptor || itemDescriptor == -1)
		{
			m_tcpSocketConnectList.removeAt(i);//�Ͽ���socket���������Ƴ�
			item->deleteLater();//������Դ
			qDebug() << QString::fromLocal8Bit("TcpSocket�Ͽ����ӣ�") << descriptor << endl;
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
			qDebug() << QString::fromLocal8Bit("����IP:") << item->peerAddress().toString()
					 << QString::fromLocal8Bit("���������ݣ�") << QString(SendData);

			emit signalTcpMsgComes(SendData);
		}
	}
}