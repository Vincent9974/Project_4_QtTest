#include "TcpSocket.h"

TcpSocket::TcpSocket()
{
}

TcpSocket::~TcpSocket()
{
}

void TcpSocket::run()
{
	// ��ȡ��ǰ�׽��ֵ����������׽����������ǲ���ϵͳ������׽��ֵ�Ψһ��ʶ����
	m_descriptor = this->socketDescriptor();

	// ���� readyRead() �źŵ� onReceiveData() �ۺ��������ڴ�����յ�������
	connect(this, SIGNAL(readyRead()), this, SLOT(onReceiveData()));
	// ���� disconnected() �źŵ� onClientDisconnect() �ۺ��������ڴ���ͻ��˶Ͽ����ӵ����
	connect(this, SIGNAL(disconnected()), this, SLOT(onClientDisconnect()));
}

void TcpSocket::onClientDisconnect()
{
	emit signalClientDisconnect(m_descriptor);
}

void TcpSocket::onReceiveData()
{
	// ��ȡ�׽����е����п�������
	QByteArray buffer = this->readAll();

	// ������յ������ݲ�Ϊ��
	if (!buffer.isEmpty())
	{
		// �����յ�������ת��Ϊ�ַ�����ʹ�ñ����ַ�����
		QString strData = QString::fromLocal8Bit(buffer);

		// ���ͽ��յ��˿ͻ������ݵ��ź�
		emit signalGetDataFromClient(buffer, m_descriptor);
	}

}


