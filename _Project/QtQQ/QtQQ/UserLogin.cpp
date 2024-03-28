#include "UserLogin.h"
#include "CCMainWindow.h"

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
	headLabel->setPixmap(getRoundImage(QPixmap(":/Resources/MainWindow/girl.png"), pix, headLabel->size()));
	headLabel->move(width() / 2 - 34, ui.titleWidget->height() - 34);

	// 连接登录按钮的点击信号与槽函数
	connect(ui.loginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);
}

void UserLogin::onLoginBtnClicked()
{
	// 关闭登录窗口
	close();

	// 创建并显示主窗口
	CCMainWindow* mainWindow = new CCMainWindow;
	mainWindow->show();
}


