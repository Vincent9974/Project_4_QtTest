#include "QtQQ_Server.h"

#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QFileDialog>

const int gtcpPort = 8888;
const int gudpPort = 6666;

QtQQ_Server::QtQQ_Server(QWidget *parent)
    : QDialog(parent)
	,m_pixPath("")
{
    ui.setupUi(this);


	// ���ӵ� MySQL ���ݿ�
	if (!connectMySql())
	{
		QMessageBox::warning(NULL,
			QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�������ݿ�ʧ��!"));
		close();
		return;
	}

	setDepNameMap();
	setStatusMap();
	setOnlineMap();

	initComboBoxData();

	// ��ѯԱ����Ϣ
	m_queryInfoModel.setQuery("SELECT * FROM tab_employees");
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // ���ñ��Ϊֻ��ģʽ

	//��ʼ����ѯ��˾Ⱥ����Ա����Ϣ
	m_employeeID = 0;
	m_depID = getCompDepID();
	m_compDepID = m_depID;

	updateTableData();


	//��ʱˢ������
	m_timer = new QTimer(this);
	m_timer->setInterval(200);
	m_timer->start();
	connect(m_timer, &QTimer::timeout, this, &QtQQ_Server::onRefresh);

	initTcpSocket();
	initUdpSocket();
}

void QtQQ_Server::initTcpSocket()
{
	m_tcpServer = new TcpServer(gtcpPort);
	m_tcpServer->run();

	//�յ�tcp�ͻ��˷�������Ϣ�����udp�㲥
	connect(m_tcpServer,&TcpServer::signalTcpMsgComes,
		this, &QtQQ_Server::onUDPbroadMsg);
}

void QtQQ_Server::initUdpSocket()
{
	m_udpSender = new QUdpSocket(this);
}

void QtQQ_Server::onUDPbroadMsg(QByteArray& btData)
{
	for (quint16 port = gudpPort; port < gudpPort + 200; ++port)
	{
		m_udpSender->writeDatagram(btData, btData.size(), QHostAddress::Broadcast, port);

	}
}


// ���ӵ� MySQL ���ݿ�
bool QtQQ_Server::connectMySql()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setDatabaseName("qtqq"); // ���ݿ�����
	db.setHostName("localhost"); // ������
	db.setUserName("root"); // �û���
	db.setPassword("123456"); // ����
	db.setPort(3306); // �˿ں�

	if (db.open())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int QtQQ_Server::getCompDepID()
{
	QSqlQuery queryCompDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'")
		.arg(QString::fromLocal8Bit("��˾Ⱥ")));

	// ִ�� SQL ��ѯ
	queryCompDepID.exec();

	// �ƶ���ѯ�����ָ�뵽��һ����¼
	queryCompDepID.next();

	// ��ȡ��ѯ����е�һ�е�ֵ������˾���ŵ� departmentID����ת��Ϊ��������
	int compDepID = queryCompDepID.value(0).toInt();

	// ���ع�˾���ŵ� departmentID
	return compDepID;
}


// ���±������
void QtQQ_Server::updateTableData(int depID, int employeeID)
{
	ui.tableWidget->clear();

	// ���ݲ�ѯ������ȡԱ����Ϣ
	QString queryStr;
	if (depID && depID != m_compDepID) // ��ѯ����
	{
		queryStr = QString("SELECT * FROM tab_employees WHERE departmentID = %1").arg(depID);
	}
	else if (employeeID) // ��ȷ����
	{
		queryStr = QString("SELECT * FROM tab_employees WHERE employeeID = %1").arg(employeeID);
	}
	else // ��ѯ����
	{
		queryStr = QString("SELECT * FROM tab_employees");
	}


	// ���ò�ѯģ��
	m_queryInfoModel.setQuery(queryStr);

	// ��ȡ��ѯ���������������
	int rows = m_queryInfoModel.rowCount();
	int columns = m_queryInfoModel.columnCount();

	QModelIndex index; // ģ������

	// ���ñ������������
	ui.tableWidget->setRowCount(rows);
	ui.tableWidget->setColumnCount(columns);

	// ���ñ���б���
	QStringList headers;
	headers << QStringLiteral("����")
		<< QStringLiteral("����")
		<< QStringLiteral("Ա������")
		<< QStringLiteral("Ա��ǩ��")
		<< QStringLiteral("Ա��״̬")
		<< QStringLiteral("Ա��ͷ��")
		<< QStringLiteral("����״̬");
	ui.tableWidget->setHorizontalHeaderLabels(headers);

	// ���ñ���п�����Ӧ
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// ������ѯ��������������
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			index = m_queryInfoModel.index(i, j); // ��ȡģ������
			QString strData = m_queryInfoModel.data(index).toString(); // ��ȡ����

			// �����ֶ�������������������
			QSqlRecord record = m_queryInfoModel.record(i); // ��ǰ��¼
			QString strRecordName = record.fieldName(j); // �ֶ�����


			if (strRecordName == QLatin1String("departmentID"))
			{
				ui.tableWidget->setItem(i, j, new QTableWidgetItem(m_depNameMap.value(strData)));
				continue;
			}
			else if (strRecordName == QLatin1String("status"))
			{
				ui.tableWidget->setItem(i, j, new QTableWidgetItem(m_statusMap.value(strData)));
				continue;
			}
			else if (strRecordName == QLatin1String("online"))
			{
				ui.tableWidget->setItem(i, j, new QTableWidgetItem(m_onlineMap.value(strData)));
				continue;
			}

			ui.tableWidget->setItem(i, j, new QTableWidgetItem(strData));
		}
	}
}

// ���ò�������ӳ��
void QtQQ_Server::setDepNameMap()
{
	m_depNameMap.insert(QStringLiteral("2001"), QStringLiteral("���²�"));
	m_depNameMap.insert(QStringLiteral("2002"), QStringLiteral("�г���"));
	m_depNameMap.insert(QStringLiteral("2003"), QStringLiteral("�з���"));
}

// ����״̬ӳ��
void QtQQ_Server::setStatusMap()
{
	m_statusMap.insert(QStringLiteral("1"), QStringLiteral("��Ч"));
	m_statusMap.insert(QStringLiteral("0"), QStringLiteral("��Ч"));
}

// ��������״̬ӳ��
void QtQQ_Server::setOnlineMap()
{
	m_onlineMap.insert(QStringLiteral("1"), QStringLiteral("����"));
	m_onlineMap.insert(QStringLiteral("2"), QStringLiteral("����"));
	m_onlineMap.insert(QStringLiteral("3"), QStringLiteral("æµ"));
}

// ��ʼ������������
void QtQQ_Server::initComboBoxData()
{
	QString itemText; // ���������ı�

	// ��ȡ���������б����ö�Ӧ�Ĳ��� ID
	QSqlQueryModel queryDepModel;
	queryDepModel.setQuery("SELECT * FROM tab_department");
	int depCounts = queryDepModel.rowCount() - 1; // ��������(��ȥ��Ⱥ)


	for (int i = 0; i < depCounts; i++)
	{
		itemText = ui.employeeDepBox->itemText(i);
		QSqlQuery queryDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'").arg(itemText));
		queryDepID.exec();
		queryDepID.first();

		ui.employeeDepBox->setItemData(i, queryDepID.value(0).toInt());
	}

	// ��һ��"��˾Ⱥ" ����
	for (int i = 0; i < depCounts + 1; i++)
	{
		itemText = ui.departmentBox->itemText(i);
		QSqlQuery queryDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'").arg(itemText));
		queryDepID.exec();
		queryDepID.first();

		ui.departmentBox->setItemData(i, queryDepID.value(0).toInt());
	}
}


// ��ʱˢ�±������
void QtQQ_Server::onRefresh()
{
	updateTableData(m_depID, m_employeeID);
}

// ���Ų�ѯ��ť����¼�
void QtQQ_Server::on_queryDepartmentBtn_clicked()
{
	ui.queryIDLineEdit->clear();
	m_employeeID = 0;
	m_depID = ui.departmentBox->currentData().toInt();
	updateTableData(m_depID);
}

// Ա����ѯ��ť����¼�
void QtQQ_Server::on_queryIDBtn_clicked()
{
	ui.departmentBox->setCurrentIndex(0);
	m_depID = m_compDepID;

	// ���Ա��QQ������Ƿ�Ϊ��
	if (!ui.queryIDLineEdit->text().length())
	{
		QMessageBox::information(this,
			QStringLiteral("��ʾ"),
			QStringLiteral("������Ա��QQ��"));
		ui.queryIDLineEdit->setFocus();
		return;
	}

	// ��ȡ�û������Ա��QQ��
	int employeeID = ui.queryIDLineEdit->text().toInt();

	// ��ѯԱ����Ϣ
	QSqlQuery queryInfo(QString("SELECT * FROM tab_employees WHERE employeeID = %1").arg(employeeID));
	queryInfo.exec();
	if (!queryInfo.next())
	{
		QMessageBox::information(this,
			QStringLiteral("��ʾ"),
			QStringLiteral("�����Ա��QQ�Ų�����"));
		ui.queryIDLineEdit->setFocus();
		return;
	}
	else
	{
		m_employeeID = employeeID;
	}

}

void QtQQ_Server::on_logoutBtn_clicked()
{
	ui.queryIDLineEdit->clear(); // ���Ա��ID��ѯ������
	ui.departmentBox->setCurrentIndex(0); // ������������ѡ��������Ϊ��һ��

	// ���ע��Ա��ID��ѯ��Ϊ�գ�����ʾ����Ա��ID
	if (!ui.logoutIDLineEdit->text().length())
	{
		QMessageBox::information(this,
			QStringLiteral("��ʾ"),
			QStringLiteral("������Ա��ID"));
		ui.logoutIDLineEdit->setFocus();
		return;
	}

	// ��ȡ�����Ա��ID
	int employeeID = ui.logoutIDLineEdit->text().toInt();

	// ��ѯԱ����Ϣ�Ƿ���ڣ��������������ʾ������ȷ��Ա��ID
	QSqlQuery queryInfo(QString("SELECT employee_name FROM tab_employees WHERE employeeID = %1").arg(employeeID));
	queryInfo.exec();
	if (!queryInfo.next())
	{
		QMessageBox::information(this,
			QStringLiteral("��ʾ"),
			QStringLiteral("��������ȷ��Ա��ID"));
		ui.logoutIDLineEdit->setFocus();
		return;
	}
	else
	{
		// ע������,�������ݿ���Ա��״̬Ϊ��ְ״̬��status=0��
		QSqlQuery sqlUpdate(QString("UPDATE tab_employees SET status = 0 WHERE employeeID = %1").arg(employeeID));
		sqlUpdate.exec();

		// ��ȡԱ������
		QString strName = queryInfo.value(0).toString();

		// ������ʾ��Ϣ����ʾ�ɹ�ע����Ա��������QQ��
		QMessageBox::information(this,
			QStringLiteral("��ʾ"),
			QStringLiteral("Ա�� %1 ��ҵ��QQ:%2 �ѳɹ�ע��")
			.arg(strName)
			.arg(employeeID));

		ui.logoutIDLineEdit->clear(); // ���ע��Ա��ID��ѯ������
	}
}

void QtQQ_Server::on_selectPictureBtn_clicked()
{
	// ��ȡѡ���ͷ��·�� 
	m_pixPath = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("ѡ��ͷ��"),
		".",
		"*.png;;*.jpg"
	);


	// ���δѡ��ͷ���򷵻� 
	if (!m_pixPath.size())
	{
		return;
	}

	// ��ʾͷ�񲢵�����С 
	QPixmap pixmap;
	pixmap.load(m_pixPath);

	// �����Ⱥ͸߶ȵı��� 
	qreal widthRatio = (qreal)ui.headLabel->width() / (qreal)pixmap.width();
	qreal heightRatio = (qreal)ui.headLabel->height() / (qreal)pixmap.height();

	// ���ݱ���������С 
	QSize size(pixmap.width() * widthRatio, pixmap.height() * heightRatio);
	ui.headLabel->setPixmap(pixmap.scaled(size));
}


void QtQQ_Server::on_addBtn_clicked()
{
	// ����Ƿ�������Ա������
	QString strName = ui.nameLineEdit->text();
	if (!strName.size())
	{
		QMessageBox::information(this,
			QStringLiteral("��ʾ"),
			QStringLiteral("������Ա������"));
		ui.nameLineEdit->setFocus();
		return;
	}

	// ����Ƿ�ѡ����Ա��ͷ��
	if (!m_pixPath.size())
	{
		QMessageBox::information(this,
			QStringLiteral("��ʾ"),
			QStringLiteral("��ѡ��Ա��ͷ��·��"));
		return;
	}

	// �����ݿ��������Ա����Ϣ
	// ��ȡԱ������QQ��
	QSqlQuery maxEmployeeID("SELECT MAX(employeeID) FROM tab_employees");
	maxEmployeeID.exec();
	maxEmployeeID.next();

	int employeeID = maxEmployeeID.value(0).toInt() + 1;

	// ��ȡԱ����������ID
	int depID = ui.employeeDepBox->currentData().toInt();

	// ��ͼƬ·���е���б���滻Ϊ��б���γɺϷ�·��
	m_pixPath.replace("/", "\\\\");

	// ִ�в������
	QSqlQuery insertSql(QString("INSERT INTO tab_employees(departmentID,employeeID,employee_name,picture) \
        VALUES(%1,%2,'%3','%4')")
		.arg(depID)
		.arg(employeeID)
		.arg(strName)
		.arg(m_pixPath));

	insertSql.exec();
	QMessageBox::information(this,
		QStringLiteral("��ʾ"),
		QStringLiteral("���Ա���ɹ�"));
	m_pixPath = "";
	ui.nameLineEdit->clear();
	ui.headLabel->setText(QStringLiteral("  Ա��ͷ��  "));
}
