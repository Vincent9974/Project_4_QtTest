#include <QProxyStyle>
#include <QPainter>
#include <QTimer>
#include <QEvent>
#include <QTreeWidgetItem>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

#include "CCMainWindow.h"
#include "SkinWindow.h"
#include "SysTray.h"
#include "NotifyManager.h"
#include "RootConcatItem.h"
#include "ContactItem.h"
#include "WindowManager.h"
#include "TalkWindowShell.h"


// �Զ��������ʽ�� CCMainCustomProxyStyle���̳��� QProxyStyle
class CCMainCustomProxyStyle : public QProxyStyle
{
public:
	// ��д drawPrimitive ����
	// ����ԭʼԪ�أ������߿�ȣ�����ǽ�����ο��Ԫ�أ���ֱ�ӷ��أ������л���
	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption* option,
		QPainter* painter, const QWidget* widget = nullptr) const
	{
		// ���Ԫ���ǽ�����ο��Ԫ�أ��򲻽��л��ƣ�ֱ�ӷ���
		if (element == PE_FrameFocusRect)
		{
			return;
		}
		else
		{
			// ��������£����û���� drawPrimitive ��������Ĭ�ϻ���
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}
};


CCMainWindow::CCMainWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);

	// ���ô��ڱ�־λΪ���ߴ��ڣ�ʹ�����������в���ʾ
	setWindowFlags(windowFlags() | Qt::Tool);


	// ������ʽ��ʹ�� "CCMainWindow" ��Ϊ��ʽ��ı�ʶ
	loadStyleSheet("CCMainWindow");

	initControl();
	initTimer();

}

CCMainWindow::~CCMainWindow()
{
}

void CCMainWindow::initControl()
{
	// �������οؼ�����ʽΪ�Զ�����ʽ
	ui.treeWidget->setStyle(new CCMainCustomProxyStyle);

	// �������οؼ��ļ���ͼ�ꡢͷ���״̬�˵�ͼ��
	setLevelPixmap(0);
	setHeadPixmap(":/Resources/MainWindow/girl.png");
	setStatusMenuIcon(":/Resources/MainWindow/StatusSucceeded.png");

	// ����ˮƽ���ֲ����һϵ������Ӧ����չͼ�굽������
	QHBoxLayout* appupLayout = new QHBoxLayout;
	appupLayout->setContentsMargins(0, 0, 0, 0);  // ���ò��ֵı߾�
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_7.png", "app_7"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_2.png", "app_2"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_3.png", "app_3"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_4.png", "app_4"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_5.png", "app_5"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_6.png", "app_6"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/skin.png", "app_skin"));
	appupLayout->addStretch();  // �����������ʹ�ؼ�ƽ���ֲ�
	appupLayout->setSpacing(2);  // ���ÿؼ�֮��ļ��
	// ������Ӧ�õ�Ӧ�ò�����
	ui.appWidget->setLayout(appupLayout);

	// �ڵײ����������һϵ������Ӧ����չͼ��
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_10.png", "app_10"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_8.png", "app_8"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_11.png", "app_11"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_9.png", "app_9"));
	ui.bottomLayout_up->addStretch();  // �����������ʹ�ؼ�ƽ���ֲ�

	initContactTree();

	//����ǩ��
	ui.lineEdit->installEventFilter(this);
	//��������
	ui.searchLineEdit->installEventFilter(this);

	// ������С���͹رհ�ť�Ĳۺ���
	connect(ui.sysmin, SIGNAL(clicked(bool)), this, SLOT(onShowMin(bool)));
	connect(ui.sysclose, SIGNAL(clicked(bool)), this, SLOT(onShowClose(bool)));

	connect(NotifyManager::getInstance(), &NotifyManager::signalSkinChanged, [this]()
	{
		updateSeachStyle();
	});

	SysTray* systray = new SysTray(this);
}

void CCMainWindow::setUserName(const QString & username)
{
	ui.nameLabel->adjustSize(); // ������ǩ����Ӧ�����ݴ�С

	// ͨ�� elidedText() ���������û�������Ӧ��ǩ�Ŀ�ȣ���ֹ�������û���������ʾ����
	QString name = ui.nameLabel->fontMetrics().elidedText(username, Qt::ElideRight, ui.nameLabel->width());

	ui.nameLabel->setText(name); // �����û���

}

void CCMainWindow::setLevelPixmap(int level)
{
	// ����ͼ��
	// �밴ť��ͬ��С��������ͷ�����
	QPixmap levelPixmap(ui.levelBtn->size());
	levelPixmap.fill(Qt::transparent);

	// ����һ����ͼ���󣬻��Ƶ� levelPixmap ��
	QPainter painter(&levelPixmap);
	painter.drawPixmap(0, 4, QPixmap(":/Resources/MainWindow/lv.png"));

	int unitNum = level % 10;     // ���� ��λ������Χ 1-9
	int tenNum = level / 10;       // ���� ʮλ������Χ 10-99

	// ʮλ������ֵ��ͼ��Ƭ�Σ���ͼ����ȡ��һ������Ϊ��ʾ
	// ֻȡ��һλ��������Ҫȡȫ������Ϊ���𲻻ᳬ����λ��

	//ʮλ,��ȡͼƬ�еĲ��ֽ��л���
	// drawPixmap(���Ƶ�x�����Ƶ�y, ͼƬ��ͼƬ���Ͻ�x, ͼƬ���Ͻ�y, �������, �����߶�)

	painter.drawPixmap(10, 4, QPixmap(":/Resources/MainWindow/levelvalue.png"),
		tenNum * 6, 0, 6, 7);

	// ���Ƹ�λ������ֵ��ͼ��Ƭ��
	painter.drawPixmap(16, 4, QPixmap(":/Resources/MainWindow/levelvalue.png"),
		unitNum * 6, 0, 6, 7);

	// ���ð�ťͼ��
	ui.levelBtn->setIcon(levelPixmap);
	// ����ͼ���С
	ui.levelBtn->setIconSize(ui.levelBtn->size());
}

void CCMainWindow::setHeadPixmap(const QString & headPath)
{
	QPixmap pix;
	pix.load(":/Resources/MainWindow/head_mask.png");

	//���ñ�ǩͷ��
	ui.headLbael->setPixmap(getRoundImage(QPixmap(headPath),
		pix, ui.headLbael->size()));
}

void CCMainWindow::setStatusMenuIcon(const QString & statusPath)
{
	// ״̬ͼ��Ͱ�ť�ߴ�һ��
	QPixmap statusBtnPixmap(ui.stausBtn->size());
	statusBtnPixmap.fill(Qt::transparent);// ����Ϊ͸��

	QPainter painter(&statusBtnPixmap);
	painter.drawPixmap(4, 4, QPixmap(statusPath));

	// ����ͼ��
	ui.stausBtn->setIcon(statusBtnPixmap);
	ui.stausBtn->setIconSize(ui.stausBtn->size());
}

QWidget * CCMainWindow::addOtherAppExtension(const QString & appPath, const QString & appName)
{
	QPushButton* btn = new QPushButton(this); // ��ǰ����Ϊ������
	btn->setFixedSize(20, 20); // ���ð�ť�̶���СΪ 20x20

	QPixmap pixmap(btn->size());
	pixmap.fill(Qt::transparent); // ���Ϊ͸��

	QPainter painter(&pixmap);
	QPixmap appPixmap(appPath); // ����Ӧ��ͼ��

	// �������ͼ�����ʼλ��ʹ�������ʾ
	painter.drawPixmap((btn->width() - appPixmap.width()) / 2,
		(btn->height() - appPixmap.height()) / 2, appPixmap);

	btn->setIcon(pixmap); // ���ð�ťͼ��
	btn->setIconSize(btn->size()); // ����ͼ���С�밴ť��Сһ��
	btn->setObjectName(appName); // ���ö�����
	btn->setProperty("hasborder", true); // ���ô��б߿�����

	// ���Ӱ�ť����¼����ۺ���
	connect(btn, &QPushButton::clicked, this, &CCMainWindow::onAppIconClicked);

	return btn; // ���ش����İ�ť����
}

void CCMainWindow::initContactTree()
{
	// ���Ӹ�������¼��źŵ��ۺ���
	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onItemClicked(QTreeWidgetItem*, int)));
	connect(ui.treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(onItemExpanded(QTreeWidgetItem*)));
	connect(ui.treeWidget, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(onItemCollapsed(QTreeWidgetItem*)));
	connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem*, int)));

	// �������ڵ�
	QTreeWidgetItem* pRootGroupItem = new QTreeWidgetItem;
	pRootGroupItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	pRootGroupItem->setData(0, Qt::UserRole, 0);

	// ����RootContactItemʵ������������Ϊ�������ڵ�Ĳ���
	RootContactItem* pItemName = new RootContactItem(true, ui.treeWidget);
	QString strGroupName = QString::fromLocal8Bit("������ϵ��");
	pItemName->setText(strGroupName);

	// �����ڵ���ӵ����У������䲼������ΪRootContactItem
	ui.treeWidget->addTopLevelItem(pRootGroupItem);
	ui.treeWidget->setItemWidget(pRootGroupItem, 0, pItemName);

	// ��˾�����б�
	QStringList sComDeps;

	sComDeps << QString::fromLocal8Bit("��˾Ⱥ");
	sComDeps << QString::fromLocal8Bit("���²�");
	sComDeps << QString::fromLocal8Bit("�г���");
	sComDeps << QString::fromLocal8Bit("�з���");



	// ������˾�����б���ӵ����ڵ�
	for (int i = 0; i < sComDeps.length(); i++)
	{
		addCompanyDeps(pRootGroupItem, sComDeps.at(i));
	}
}

void CCMainWindow::initTimer()
{
	QTimer* timer = new QTimer(this);
	timer->setInterval(500);
	connect(timer, &QTimer::timeout, [this]() {
		static int level = 0;
		if (level == 99)
		{
			level = 0;
		}
		level++;
		setLevelPixmap(level);
	});
	timer->start();
}


void CCMainWindow::addCompanyDeps(QTreeWidgetItem* pRootGroupItem, const QString& sDeps)
{
	// ����һ���µ�����
	QTreeWidgetItem* pChild = new QTreeWidgetItem;

	// ����ͷ��� pixmap
	QPixmap pix;
	pix.load(":/Resources/MainWindow/head_mask.png");

	// ����������Զ������ݣ����ڱ�ʶ����Ϊ����
	pChild->setData(0, Qt::UserRole, 1);

	// ���������Ψһ��ʶ��ID��ת��Ϊ�ַ������ʹ洢
	pChild->setData(0, Qt::UserRole + 1, QString::number(reinterpret_cast<qulonglong>(pChild)));

	// ������ϵ���������ͷ����û���
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);
	pContactItem->setHeadPixmap(getRoundImage(QPixmap(":/Resources/MainWindow/girl.png"), pix, pContactItem->getHeadLabelSize()));
	pContactItem->setUserName(sDeps);

	// ��������ӵ�������
	pRootGroupItem->addChild(pChild);

	// ����ϵ��������Ϊ����Ĳ���
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);

	// �����������Ӧ�Ĳ�������ӳ���ϵ�洢�� m_groupMap ��
	m_groupMap.insert(pChild, sDeps);
}

void CCMainWindow::mousePressEvent(QMouseEvent * event)
{
	if (qApp->widgetAt(event->pos()) != ui.searchLineEdit && ui.searchLineEdit->hasFocus())
	{
		ui.searchLineEdit->clearFocus();
	}

	else if (qApp->widgetAt(event->pos()) != ui.lineEdit && ui.lineEdit->hasFocus())
	{
		ui.lineEdit->clearFocus();
	}

	BasicWindow::mousePressEvent(event);
}


void CCMainWindow::resizeEvent(QResizeEvent * event)
{
	// �ڵ������ڴ�Сʱ�����û���ΪĬ��ֵ
	setUserName(QString::fromLocal8Bit("Vincent"));

	// ���û���� resizeEvent ������ȷ�������Ĵ��ڵ�����Ϊ
	BasicWindow::resizeEvent(event);
}

void CCMainWindow::updateSeachStyle()
{
	ui.searchWidget->setStyleSheet(QString("QWidget#searchWidget{background-color:rgba(%1,%2,%3,50);border-bottom:1px solid rgba(%1,%2,%3,30)}\
																		QPushButton#searchBtn{border-image:url(:/Resources/MainWindow/search/search_icon.png)}")
		.arg(m_colorBackGround.red())
		.arg(m_colorBackGround.green())
		.arg(m_colorBackGround.blue()));
}

bool CCMainWindow::eventFilter(QObject * obj, QEvent * event)
{
	// �ж��¼������Ķ����Ƿ�Ϊ������
	if (ui.searchLineEdit == obj)
	{
		// �ж��¼������Ƿ�Ϊ��ȡ�����¼�
		if (event->type() == QEvent::FocusIn)
		{
			// �޸��������������ť����ʽ����Ӧ�����ȡ�¼�
			// ��������ı�����ɫ����Ϊ��ɫ��ͬʱ����������ť�Ĳ�ͬ״̬�µı߿���ʽ
			ui.searchWidget->setStyleSheet(QString("QWidget#searchWidget{background-color:rgb(255,255,255);border-bottom:1px solid rgba(%1,%2,%3,100)} \
                QPushButton#searchBtn{border-image:url(:/Resources/MainWindow/search/main_search_deldown.png)} \
                QPushButton#searchBtn:hover{border-image:url(:/Resources/MainWindow/search/main_search_delhighlight.png)} \
                QPushButton#searchBtn:pressed{border-image:url(:/Resources/MainWindow/search/main_search_delhighdown.png)}")
				.arg(m_colorBackGround.red())
				.arg(m_colorBackGround.green())
				.arg(m_colorBackGround.blue()));
		}
		// ����¼�����Ϊʧȥ�����¼�
		else if (event->type() == QEvent::FocusOut)
		{
			// ���ú����ָ��������ԭʼ��ʽ
			updateSeachStyle();
		}
	}

	// ����false��ʾ�¼���������ݸ�Ŀ�������д���
	return false;
}

void CCMainWindow::onItemClicked(QTreeWidgetItem* item, int column)
{
	// �жϱ���������Ƿ�Ϊ���ͨ���Զ����������ж�
	bool bIsChild = item->data(0, Qt::UserRole).toBool();

	// �����������������
	if (!bIsChild)
	{
		// �л�����������չ��״̬���۵�/չ����
		item->setExpanded(!item->isExpanded());
	}
}


void CCMainWindow::onItemExpanded(QTreeWidgetItem * item)
{
	// �ж��Ƿ�Ϊ����
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		// ���Խ�QWidgetָ��ת��ΪRootContactItemָ��
		// ʹ��dynamic_cast���а�ȫ��ָ������ת��
		RootContactItem* prootItem = dynamic_cast<RootContactItem*>(ui.treeWidget->itemWidget(item, 0));

		// ����ɹ�ת��ΪRootContactItemָ�룬������չ��״̬
		if (prootItem)
		{
			prootItem->setExpanded(true);
		}
	}
}

void CCMainWindow::onItemCollapsed(QTreeWidgetItem * item)
{
	// �������Ƿ�Ϊ����
	bool bIsChild = item->data(0, Qt::UserRole).toBool();

	// ������������ִ�к�������
	if (!bIsChild)
	{
		// ���������С����ת��ΪRootContactItem���͵�ָ��
		RootContactItem* prootItem = dynamic_cast<RootContactItem*>(ui.treeWidget->itemWidget(item, 0));

		// ���ת���ɹ���˵�������Ǹ��ڵ�
		if (prootItem)
		{
			// �����ڵ��չ��״̬����Ϊfalse�����۵�����
			prootItem->setExpanded(false);

		}
	}
}

void CCMainWindow::onItemDoubleClicked(QTreeWidgetItem * item, int column)
{
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if(bIsChild)
	{
		QString strGroup = m_groupMap.value(item);
		if (strGroup == QString::fromLocal8Bit("��˾Ⱥ"))
		{
			WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), COMPANY);
			qDebug() << "Group is ��˾Ⱥ";
		}
		else if (strGroup == QString::fromLocal8Bit("���²�"))
		{
			WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), PERSONELGROUP);
		}
		else if (strGroup == QString::fromLocal8Bit("�г���"))
		{
			WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), MARKETGROUP);
		}
		else if (strGroup == QString::fromLocal8Bit("�з���"))
		{
			WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), DEVELOPMENTGROUP);
		}
	}
}


void CCMainWindow::onAppIconClicked()
{
	if (sender()->objectName() == "app_skin")
	{
		SkinWindow* skinWindow = new SkinWindow;
		skinWindow->show();
	}
}