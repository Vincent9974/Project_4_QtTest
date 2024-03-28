#include "UserLogin.h"
#include "CCMainWindow.h"

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
	headLabel->setPixmap(getRoundImage(QPixmap(":/Resources/MainWindow/girl.png"), pix, headLabel->size()));
	headLabel->move(width() / 2 - 34, ui.titleWidget->height() - 34);

	// ���ӵ�¼��ť�ĵ���ź���ۺ���
	connect(ui.loginBtn, &QPushButton::clicked, this, &UserLogin::onLoginBtnClicked);
}

void UserLogin::onLoginBtnClicked()
{
	// �رյ�¼����
	close();

	// ��������ʾ������
	CCMainWindow* mainWindow = new CCMainWindow;
	mainWindow->show();
}


