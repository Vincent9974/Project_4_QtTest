#include "TalkWindowShell.h"
#include "CommonUtils.h"
#include "BasicWindow.h"
#include <QListWidget>
#include "TalkWindow.h"
#include "TalkWindowItem.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFile>
#include "UserLogin.h"

extern QString gLoginEmployeeID;

// TalkWindowShell ��Ĺ��캯��
TalkWindowShell::TalkWindowShell(QWidget *parent)
	: BasicWindow(parent) // ���ø��๹�캯�����г�ʼ��
{
	ui.setupUi(this); // ���� UI

	setAttribute(Qt::WA_DeleteOnClose); // �����ڹر�ʱɾ�����������
	initControl(); // ��ʼ���ؼ�

	// ����Ƿ������Ϣģ��� JavaScript �ļ�
	QFile file("Resources/MainWindow/MsgHtml/msgtmpl.js");

	// ��� JavaScript �ļ������ڻ�Ϊ�գ��򴴽��µ� JavaScript �ļ�
	if (!file.size())
	{
		// ��ȡԱ��ID�б�
		QStringList employeeIDList;
		getEmployeeID(employeeIDList);

		// �����µ� JavaScript �ļ�
		if (!createJSFile(employeeIDList))
		{
			// �������ʧ�ܣ��򵯳���ʾ����ʾ�û�
			QMessageBox::information(this,
				QString::fromLocal8Bit("��ʾ"),
				QString::fromLocal8Bit("JS�ļ�����ʧ��"));
		}
	}
}


// TalkWindowShell �����������
TalkWindowShell::~TalkWindowShell()
{
	delete m_emotionWindow; // ɾ�� m_emotionWindow ����
	m_emotionWindow = nullptr; // �ÿ�ָ��
}

// ���õ�ǰ��ʾ�Ĵ���
void TalkWindowShell::setCurrentWidget(QWidget* widget)
{
	ui.rightStackedWidget->setCurrentWidget(widget);
}

// ��ȡ�Ի��������ӳ���ϵ
const QMap<QListWidgetItem*, QWidget*>& TalkWindowShell::getTalkWindowItemMap() const
{
	return m_talkwindowItemMap;
}

// ��ʼ���ؼ�
void TalkWindowShell::initControl()
{
	loadStyleSheet("TalkWindow"); // ������ʽ��
	setWindowTitle(QString::fromLocal8Bit("���촰��1")); // ���ô��ڱ���

	m_emotionWindow = new EmotionWindow; // �������鴰�ڶ���
	m_emotionWindow->hide(); // ���ر��鴰��

	QList<int> leftWidgetSize; // ������ര�ڵĳ�ʼ��С
	leftWidgetSize << 154 << width() - 154;
	ui.splitter->setSizes(leftWidgetSize);

	ui.listWidget->setStyle(new CustomProxyStyle(this)); // �����б�ؼ����Զ�����ʽ

	// �����б�ؼ������ź���ۺ������Լ����鴰�ڱ��������ź���ۺ���
	connect(ui.listWidget, &QListWidget::itemClicked, this, &TalkWindowShell::onTalkWindowItemClicked);
	connect(m_emotionWindow, SIGNAL(signalEmotionItemClicked(int)), this, SLOT(onEmotionItemClicked(int)));
}

void TalkWindowShell::initTcpSocket()
{
	m_tcpClientSocket = new QTcpSocket(this);
	m_tcpClientSocket->connectToHost("127.0.0.1", gtcpPort);
}

void TalkWindowShell::getEmployeeID(QStringList& employeesList)
{
	// ����һ�� SQL ��ѯģ��
	QSqlQueryModel queryModel;
	// ���� SQL ��ѯ��䣬����Ϊ tab_employee �ı���ѡ��Ա��ID������״̬Ϊ1
	queryModel.setQuery("SELECT employeeID FROM tab_employees WHERE status = 1");

	// ��ȡ��ѯ����е���������Ա������
	int employeeNum = queryModel.rowCount();

	// ���ڴ洢��ѯ�������������
	QModelIndex index;
	// ������ѯ�����ÿһ��
	for (int i = 0; i < employeeNum; i++)
	{
		// ��ȡ��ǰ�еĵ�һ�����ݵ�����
		index = queryModel.index(i, 0);
		// ����ǰ�еĵ�һ������ת��Ϊ�ַ���������ӵ�Ա���б���
		employeesList << queryModel.data(index).toString();
	}
}


bool TalkWindowShell::createJSFile(QStringList & employeeList)
{
	// ��ȡtxt�ļ�·��
	QString strFileTxt = "Resources/MainWindow/MsgHtml/msgtmpl.txt";
	QFile fileRead(strFileTxt);
	QString strFile; // ���ڴ洢��ȡ���ļ�����

	// �����ֻ��ģʽ�ɹ����ļ������ȡȫ������
	if (fileRead.open(QIODevice::ReadOnly))
	{
		strFile = fileRead.readAll();
		fileRead.close(); // �ر��ļ���ȡ��
	}
	else
	{
		// ����޷����ļ�����ʾ������ʾ��Ϣ������false
		QMessageBox::information(this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ȡ msgtmpl.txt ʧ��"));
		return false;
	}

	// �滻ģ���е�external0��appendHtml0Ϊʵ�ʵ���Ϣ��Ϣ
	QFile fileWrite("Resources/MainWindow/MsgHtml/msgtmpl.js");


	// ��д��ģʽ���ļ�������ɹ������д�����
	if (fileWrite.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		// ������Ҫ�滻��Դ����κ�ʵ����Ϣ�ĳ�ʼ��ֵ
		QString strSourceInitNull = "var external = null;";
		QString strSourceInit = "external = channel.objects.external;";
		QString strSourceNew =
			"new QWebChannel(qt.webChannelTransport,\
			function(channel) {\
			external = channel.objects.external;\
		}\
		); \
		";

		//����׷��recvHtml,�ű�����˫�����޷�ֱ�ӽ��и�ֵ
		QString strSourceRecvHtml;
		QFile fileRecvHtml("Resources/MainWindow/MsgHtml/recvHtml.txt");

		// ����ɹ��򿪽�����Ϣ���ļ������ȡȫ������
		if (fileRecvHtml.open(QIODevice::ReadOnly))
		{
			strSourceRecvHtml = fileRecvHtml.readAll();
			fileRecvHtml.close();
		}
		else
		{
			// ����޷����ļ�����ʾ������ʾ��Ϣ������false
			QMessageBox::information(this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("��ȡ recvHtml.txt ʧ��"));
			return false;
		}

		// ������Ҫ�滻���ַ���
		QString strReplaceInitNull;
		QString strReplaceInit;
		QString strReplaceNew;
		QString strReplaceRecvHtml;

		// ����Ա���б��滻��Ӧ���ַ���
		for (int i = 0; i < employeeList.length(); i++)
		{
			// �༭�滻��ĳ�ʼ��ֵ�ַ���
			QString strInitNull = strSourceInitNull;
			strInitNull.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceInitNull += strInitNull;
			strReplaceInitNull += "\n";

			// �༭�滻��ĳ�ʼ���ַ���
			QString strInit = strSourceInit;
			strInit.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceInit += strInit;
			strReplaceInit += "\n";

			// �༭�滻���newWebchannel�ַ���
			QString strNew = strSourceNew;
			strNew.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceNew += strNew;
			strReplaceNew += "\n";

			// �༭�滻���recvHtml�ַ���
			QString strRecvHtml = strSourceRecvHtml;
			strRecvHtml.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strRecvHtml.replace("recvHtml", QString("recvHtml_%1").arg(employeeList.at(i)));
			strReplaceRecvHtml += strRecvHtml;
			strReplaceRecvHtml += "\n";
		}

		// ʹ���滻����ַ����滻Դ�ļ��еĶ�Ӧ����
		strFile.replace(strSourceInitNull, strReplaceInitNull);
		strFile.replace(strSourceInit, strReplaceInit);
		strFile.replace(strSourceNew, strReplaceNew);
		strFile.replace(strSourceRecvHtml, strReplaceRecvHtml);

		// ���滻�������д���ļ�
		QTextStream stream(&fileWrite);
		stream << strFile;
		fileWrite.close(); // �ر��ļ�д����

		return true; // ����true��ʾ�����ɹ�
	}
	else
	{
		qDebug() << "File open failed. Error: " << fileWrite.errorString();
		// ����޷����ļ�����ʾ������ʾ��Ϣ������false
		QMessageBox::information(this,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("д�� msgtmpl.js ʧ��"));
		return false;
	}
}

// �ı����ݰ��ĸ�ʽ��Ⱥ�ı�־ + ����ϢԱ��QQ�� + ����ϢQQ�� + ��Ϣ���� + ���ݳ��� + ����
// �������ݰ���ʽ�� Ⱥ�ı�־ + ����ϢԱ��QQ�ţ�ȺQQ�ţ� + ����ϢԱ��QQ�� + ��Ϣ���� + ������� + images + ����
void TalkWindowShell::updateSendTcpMsg(QString & strData, int & msgType, QString fileName)
{
	// ��ȡ��ǰ�Ի���
	TalkWindow* curTalkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget());
	// ��ȡ�Ի�ID
	QString talkID = curTalkWindow->getTalkID();

	// Ⱥ�ı�־
	QString strGroupFlag;
	QString strSend;


	if (talkID.length() == 4) // Ⱥ��ID����Ϊ4
	{
		// Ⱥ�ı�־Ϊ1
		strGroupFlag = "1";
	}
	else
	{
		strGroupFlag = "0";
	}

	// ��ȡ���ݳ���
	int nstrDataLength = strData.length();
	int dataLength = QString::number(nstrDataLength).length();

	QString strdataLength;


	if (msgType == 1) // �ı���Ϣ
	{
		if (dataLength < 5)
		{
			strdataLength = QString(5 - dataLength, '0') + QString::number(nstrDataLength);
		}
		else if (dataLength == 5)
		{
			strdataLength = QString::number(nstrDataLength);
		}
		else
		{
			QMessageBox::information(this,
				QString::fromLocal8Bit("��ʾ"),
				QString::fromLocal8Bit("���ݳ��ȳ�������"));
		}

		// �ı����ݰ��ĸ�ʽ��Ⱥ�ı�־ + ����ϢԱ��QQ�� + ����ϢQQ�� + ��Ϣ���� + ���ݳ��� + ����
		strSend = strGroupFlag + gLoginEmployeeID + talkID + "1" + strdataLength + strData;
	}
	else if (msgType == 0) // ͼƬ��Ϣ
	{
		// �������ݰ���ʽ�� Ⱥ�ı�־ + ����ϢԱ��QQ�ţ�ȺQQ�ţ� + ����ϢԱ��QQ�� + ��Ϣ���� + ������� + images + ����
		strSend = strGroupFlag + gLoginEmployeeID + talkID + "0" + strData;
	}
	else if (msgType == 2) // �ļ���Ϣ
	{
		// �ļ����ݰ���ʽ�� Ⱥ�ı�־ + ����ϢԱ��QQ�ţ�ȺQQ�ţ� 
		// + ����ϢԱ��QQ��  + ��Ϣ����(2) + �ļ����� + "bytes" 
		// + �ļ����� + ��data_begin��+ �ļ�����

		QByteArray bt = strData.toUtf8();
		QString strLength = QString::number(bt.length());

		strSend = strGroupFlag + gLoginEmployeeID + talkID + "2" + strLength
			+ "bytes" + fileName + "data_begin" + strData;
	}

	QByteArray dataBt;
	dataBt.resize(strSend.length());
	dataBt = strSend.toUtf8();

	m_tcpClientSocket->write(dataBt);
}

// �� TalkWindowShell ����ӶԻ����ںͶ�Ӧ����
void TalkWindowShell::addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, const QString& uid/*, GroupType groupType*/)
{
	ui.rightStackedWidget->addWidget(talkWindow);

	// ��ӱ��鴰�ڵ��ź����ӣ������鴰������ʱ���������촰�ڵı��鰴ť״̬
	connect(m_emotionWindow, SIGNAL(signalEmotionWindowHide()),
		talkWindow, SLOT(onSetEmotionBtnStatus()));

	// ����һ���б��������ʾ������б���
	QListWidgetItem* aItem = new QListWidgetItem(ui.listWidget);

	// ���б��������촰�ڽ���ӳ��
	m_talkwindowItemMap.insert(aItem, talkWindow);

	aItem->setSelected(true);   // Ĭ��ѡ��

	//�ж�Ⱥ�ĵ���
	QSqlQueryModel sqlDepModel;
	QString strQuery = QString("SELECT picture FROM tab_department WHERE departmentID = %1").arg(uid);
	sqlDepModel.setQuery(strQuery);
	int rows = sqlDepModel.rowCount();          // ��ȡ����

	// �ж���Ⱥ�黹�Ǹ��ˣ��������Ϊ0����˵���Ǹ���
	if (rows == 0)
	{
		strQuery = QString("SELECT picture FROM tab_employees WHERE employeeID = %1").arg(uid);
		sqlDepModel.setQuery(strQuery);
	}

	QModelIndex index;
	index = sqlDepModel.index(0, 0);        // ��ȡ��һ�е�һ��

	QImage img;
	// ����ͷ��ͼƬ
	img.load(sqlDepModel.data(index).toString());

	// ����ͷ��
	talkWindowItem->setHeadPixmap(QPixmap::fromImage(img));
	// ����б���
	ui.listWidget->addItem(aItem);
	// �����б���Ĵ��ڲ���
	ui.listWidget->setItemWidget(aItem, talkWindowItem);

	// �����б������¼�
	onTalkWindowItemClicked(aItem);

	// ��ӹرհ�ť���ź����ӣ�ʵ�ֹرմ��ڵĹ���
	connect(talkWindowItem, &TalkWindowItem::signalCloseClicked, [talkWindowItem, talkWindow, aItem, this]()
	{
		// ��ӳ�����Ƴ��б���
		m_talkwindowItemMap.remove(aItem);     // ɾ��ӳ��
		talkWindow->close();                                    // �ر����촰��
		// ���б����Ƴ��б���
		ui.listWidget->takeItem(ui.listWidget->row(aItem));
		delete talkWindowItem;

		// ���Ҳ಼�����Ƴ����촰��
		ui.rightStackedWidget->removeWidget(talkWindow);

		// ���û�����촰���ˣ���ر�������
		if (ui.rightStackedWidget->count() < 1)
		{
			close();
		}
	});

}

// ������鰴ť����¼�
void TalkWindowShell::onEmotionBtnClicked(bool)
{
	m_emotionWindow->setVisible(!m_emotionWindow->isVisible()); // �л����鴰�ڵĿɼ���

	// �����鴰���ƶ������ʵ�λ��
	QPoint emotionPoint = this->mapToGlobal(QPoint(0, 0));
	emotionPoint.setX(emotionPoint.x() + 170);
	emotionPoint.setY(emotionPoint.y() + 220);
	m_emotionWindow->move(emotionPoint);
}

// ������������¼�
void TalkWindowShell::onEmotionItemClicked(int emotionNum)
{
	TalkWindow* curTalkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget()); // ��ȡ��ǰ��ʾ�ĶԻ�����
	if (curTalkWindow) // �жϵ�ǰ�Ի������Ƿ���Ч
	{
		curTalkWindow->addEmotionImage(emotionNum); // ��ǰ�Ի�������ӱ���ͼƬ
	}
}

// ����Ի����������¼�
void TalkWindowShell::onTalkWindowItemClicked(QListWidgetItem* item)
{
	QWidget* talkWindowWidget = m_talkwindowItemMap.find(item).value(); // ��ȡ��Ӧ�ĶԻ�����
	ui.rightStackedWidget->setCurrentWidget(talkWindowWidget); // ���õ�ǰ��ʾ�Ĵ���Ϊ�Ի�����
}
