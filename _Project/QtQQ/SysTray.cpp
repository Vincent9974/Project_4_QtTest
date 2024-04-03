#include "SysTray.h"
#include "CustomMenu.h"

SysTray::SysTray(QWidget *parent)
	: m_parent(parent)
	,QSystemTrayIcon(parent)
{
	initSystemTray();
	show();
}

SysTray::~SysTray()
{
}


void SysTray::initSystemTray() // ��ʼ��ϵͳ����ͼ��ķ���
{
	// ����ϵͳ����ͼ�����ʾ��Ϣ
	setToolTip(QStringLiteral("QQ-Vincent"));

	// ����ϵͳ����ͼ���ͼ��
	setIcon(QIcon(":/Resources/MainWindow/app/logo.ico"));

	// ����ϵͳ����ͼ��ļ����¼�����Ӧ�Ĳۺ���
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(onIconActivated(QSystemTrayIcon::ActivationReason)));
}

void SysTray::addSystrayMenu()
{
	CustomMenu* customMenu = new CustomMenu(m_parent);
	// ���Զ���˵�����Ӳ˵��������ͼ����ı�
	customMenu->addCustomMenu("onShow", ":/Resources/MainWindow/app/logo.ico",
		QStringLiteral("��ʾ"));
	customMenu->addCustomMenu("onQuit", ":/Resources/MainWindow/app/page_close_btn_hover.png",
		QStringLiteral("�˳�"));

	// ���Ӳ˵���Ĵ����¼�����Ӧ�Ĳۺ���
	connect(customMenu->getAction("onShow"), SIGNAL(triggered(bool)),
		m_parent, SLOT(onShowNormal(bool)));
	connect(customMenu->getAction("onQuit"), SIGNAL(triggered(bool)),
		m_parent, SLOT(onShowQuit(bool)));
	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		m_parent, SLOT(showNormal())); // ˫��ϵͳ����ͼ����ʾ����


	// ������Ҽ����λ�õ����Զ���˵�
	customMenu->exec(QCursor::pos());

	// �ͷ��Զ���˵����ڴ棬�����ڴ�й©
	delete customMenu;
	customMenu = nullptr;
}


void SysTray::onIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::Trigger)
	{
		m_parent->show();
		m_parent->activateWindow();
	}
	else if (reason == QSystemTrayIcon::Context)
	{
		addSystrayMenu();
	}
}
