#include "UserLogin.h"
#include "CCMainWindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <qDebug>

QString gLoginEmployeeID;


UserLogin::UserLogin(QWidget *parent)
	: BasicWindow(parent) // 调用 BasicWindow 类的构造函数进行初始化
{
	ui.setupUi(this); // 设置 UI

	// 设置窗口关闭时自动释放
	setAttribute(Qt::WA_DeleteOnClose);

	// 初始化标题栏
	initTitleBar();

	// 设置标题栏标题和图标
	setTitleBarTitle("", ":/Resources/MainWindow/qqlogoclassic.png");

	// 加载样式表
	loadStyleSheet("UserLogin");

	// 初始化控件
	initControl();
}

UserLogin::~UserLogin()
{
}

void UserLogin::initControl()
{
	// 创建头像标签并设置大小
	QLabel* headLabel = new QLabel(this);
	headLabel->setFixedSize(68, 68);

	// 创建圆形头像
	QPixmap pix(":/Resources/MainWindow/head_mask.png");
	headLabel->setPixmap(getRoundImage(QPixmap(":/Resources/MainWindow/app/logo.ico"), pix, headLabel->size()));
	headLabel->move(width() / 2 - 34, ui.titleWidget->height() - 34);

	// 连接登录按钮的点击信号与槽函数
	connect(ui.loginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);

	if (!connectMySql()) // 如果连接数据库失败
	{
		// 显示提示信息
		QMessageBox::information(NULL, QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("连接数据库失败"));

		// 直接关闭程序
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

	

	if (error.isValid())//检测错误是否有效
	{
		switch (error.type()) {
		case QSqlError::NoError:
			qDebug() << "无错误";
			break;
		case QSqlError::ConnectionError://连接错误
			qDebug() << error.text();
			break;
		case QSqlError::StatementError://语句错误
			qDebug() << error.text();
			break;
		case QSqlError::TransactionError://事务错误
			qDebug() << error.text();
			break;
		default://未知错误
			qDebug() << error.text();
			break;
		}
	}
	

	// 打开数据库连接
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
	bool isAccountLogin; //true账号, false QQ号
	QString strAccount; 
	// 验证账号和密码
	if (!veryfyAccountCode(isAccountLogin, strAccount))
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("账号或密码错误"));

		// 清空输入框内容
		//ui.editUserAccount->setText("");
		//ui.editPassword->setText("");
		return;
	}

	// 将用户的登录状态更新为"已登录"
	//QString strSqlStatus = QString("UPDATE tab_employee SET online = 2 WHERE employeeID = %1").arg(gLoginEmployeeID);
	//QSqlQuery queryStatus(strSqlStatus);
	//queryStatus.exec();

	// 关闭登录窗口
	close();

	// 创建并显示主窗口
	CCMainWindow* mainWindow = new CCMainWindow(strAccount, isAccountLogin);
	mainWindow->show();
}

bool UserLogin::veryfyAccountCode(bool& isAccountLogin, QString& strAccount)
{
	// 获取用户输入的账号和密码
	QString strAccountInput = ui.editUserAccount->text();
	QString strCodeInput = ui.editPassword->text();

	// 根据员工ID查询数据库中的密码
	QString strSqlCode = QString("SELECT code FROM tab_accounts WHERE employeeID = %1").arg(strAccountInput);
	QSqlQuery queryEmployeeID(strSqlCode);
	queryEmployeeID.exec();


	// 如果查询到结果
	if (queryEmployeeID.first())
	{
		// 获取数据库中存储的密码
		QString strCode = queryEmployeeID.value(0).toString();

		// 如果输入的密码与数据库中的密码匹配
		if (strCode == strCodeInput)
		{
			// 登录成功，设置全局变量
			gLoginEmployeeID = strAccountInput;
			isAccountLogin = false; // 标记为QQ登录
			strAccount = strAccountInput; // 记录账号
			return true;
		}
		else
		{
			return false; // 密码不匹配，登录失败
		}
	}

	// 如果通过员工ID查询不到密码，则尝试使用账号查询
	strSqlCode = QString("SELECT code,employeeID FROM tab_accounts WHERE account = '%1'").arg(strAccountInput);
	QSqlQuery queryAccount(strSqlCode);
	queryAccount.exec();

	if (queryAccount.first())
	{
		// 获取数据库中存储的密码
		QString strCode = queryAccount.value(0).toString();

		// 如果输入的密码与数据库中的密码匹配
		if (strCode == strCodeInput)
		{
			// 登录成功，设置全局变量
			gLoginEmployeeID = queryAccount.value(1).toString();
			strAccount = strAccountInput; // 记录账号
			isAccountLogin = true; // 标记为账号登录
			return true;
		}
		else
		{
			return false; // 密码不匹配，登录失败
		}
	}

	// 登录失败，返回false
	return false;
}





