#include "UserLogin.h"
#include "CCMainWindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <qDebug>

QString gLoginEmployeeID;


UserLogin::UserLogin(QWidget *parent)
	: BasicWindow(parent) // ���� BasicWindow ��Ĺ��캯�����г�ʼ��
{
	ui.setupUi(this); // ���� UI

	// ���ô��ڹر�ʱ�Զ��ͷ�
	setAttribute(Qt::WA_DeleteOnClose);

	// ��ʼ��������
	initTitleBar();

	// ���ñ����������ͼ��
	setTitleBarTitle("", ":/Resources/MainWindow/qqlogoclassic.png");

	// ������ʽ��
	loadStyleSheet("UserLogin");

	// ��ʼ���ؼ�
	initControl();
}

UserLogin::~UserLogin()
{
}

void UserLogin::initControl()
{
	// ����ͷ���ǩ�����ô�С
	QLabel* headLabel = new QLabel(this);
	headLabel->setFixedSize(68, 68);

	// ����Բ��ͷ��
	QPixmap pix(":/Resources/MainWindow/head_mask.png");
	headLabel->setPixmap(getRoundImage(QPixmap(":/Resources/MainWindow/app/logo.ico"), pix, headLabel->size()));
	headLabel->move(width() / 2 - 34, ui.titleWidget->height() - 34);

	// ���ӵ�¼��ť�ĵ���ź���ۺ���
	connect(ui.loginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);

	if (!connectMySql()) // ����������ݿ�ʧ��
	{
		// ��ʾ��ʾ��Ϣ
		QMessageBox::information(NULL, QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�������ݿ�ʧ��"));

		// ֱ�ӹرճ���
		close();
	}
}

bool UserLogin::connectMySql()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setDatabaseName("qtqq");
	db.setHostName("127.0.0.1");
	db.setUserName("root");
	db.setPassword("123456");
	db.setPort(3306);

	QSqlError error = db.lastError();
	qDebug() << "Database error: " << error.text();

	

	if (error.isValid())//�������Ƿ���Ч
	{
		switch (error.type()) {
		case QSqlError::NoError:
			qDebug() << "�޴���";
			break;
		case QSqlError::ConnectionError://���Ӵ���
			qDebug() << error.text();
			break;
		case QSqlError::StatementError://������
			qDebug() << error.text();
			break;
		case QSqlError::TransactionError://�������
			qDebug() << error.text();
			break;
		default://δ֪����
			qDebug() << error.text();
			break;
		}
	}
	

	// �����ݿ�����
	if (db.open())
	{
		return true;
	}
	else
	{
		return false;
	}
}


void UserLogin::onLoginBtnClicked()
{
	bool isAccountLogin; //true�˺�, false QQ��
	QString strAccount; 
	// ��֤�˺ź�����
	if (!veryfyAccountCode(isAccountLogin, strAccount))
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("��ʾ"),
			QString::fromLocal8Bit("�˺Ż��������"));

		// ������������
		//ui.editUserAccount->setText("");
		//ui.editPassword->setText("");
		return;
	}

	// ���û��ĵ�¼״̬����Ϊ"�ѵ�¼"
	//QString strSqlStatus = QString("UPDATE tab_employee SET online = 2 WHERE employeeID = %1").arg(gLoginEmployeeID);
	//QSqlQuery queryStatus(strSqlStatus);
	//queryStatus.exec();

	// �رյ�¼����
	close();

	// ��������ʾ������
	CCMainWindow* mainWindow = new CCMainWindow(strAccount, isAccountLogin);
	mainWindow->show();
}

bool UserLogin::veryfyAccountCode(bool& isAccountLogin, QString& strAccount)
{
	// ��ȡ�û�������˺ź�����
	QString strAccountInput = ui.editUserAccount->text();
	QString strCodeInput = ui.editPassword->text();

	// ����Ա��ID��ѯ���ݿ��е�����
	QString strSqlCode = QString("SELECT code FROM tab_accounts WHERE employeeID = %1").arg(strAccountInput);
	QSqlQuery queryEmployeeID(strSqlCode);
	queryEmployeeID.exec();


	// �����ѯ�����
	if (queryEmployeeID.first())
	{
		// ��ȡ���ݿ��д洢������
		QString strCode = queryEmployeeID.value(0).toString();

		// �����������������ݿ��е�����ƥ��
		if (strCode == strCodeInput)
		{
			// ��¼�ɹ�������ȫ�ֱ���
			gLoginEmployeeID = strAccountInput;
			isAccountLogin = false; // ���ΪQQ��¼
			strAccount = strAccountInput; // ��¼�˺�
			return true;
		}
		else
		{
			return false; // ���벻ƥ�䣬��¼ʧ��
		}
	}

	// ���ͨ��Ա��ID��ѯ�������룬����ʹ���˺Ų�ѯ
	strSqlCode = QString("SELECT code,employeeID FROM tab_accounts WHERE account = '%1'").arg(strAccountInput);
	QSqlQuery queryAccount(strSqlCode);
	queryAccount.exec();

	if (queryAccount.first())
	{
		// ��ȡ���ݿ��д洢������
		QString strCode = queryAccount.value(0).toString();

		// �����������������ݿ��е�����ƥ��
		if (strCode == strCodeInput)
		{
			// ��¼�ɹ�������ȫ�ֱ���
			gLoginEmployeeID = queryAccount.value(1).toString();
			strAccount = strAccountInput; // ��¼�˺�
			isAccountLogin = true; // ���Ϊ�˺ŵ�¼
			return true;
		}
		else
		{
			return false; // ���벻ƥ�䣬��¼ʧ��
		}
	}

	// ��¼ʧ�ܣ�����false
	return false;
}





