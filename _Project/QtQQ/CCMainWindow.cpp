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


// 自定义代理样式类 CCMainCustomProxyStyle，继承自 QProxyStyle
class CCMainCustomProxyStyle : public QProxyStyle
{
public:
	// 重写 drawPrimitive 方法
	// 绘制原始元素，包括边框等，如果是焦点矩形框架元素，则直接返回，不进行绘制
	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption* option,
		QPainter* painter, const QWidget* widget = nullptr) const
	{
		// 如果元素是焦点矩形框架元素，则不进行绘制，直接返回
		if (element == PE_FrameFocusRect)
		{
			return;
		}
		else
		{
			// 其他情况下，调用基类的 drawPrimitive 方法进行默认绘制
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}
};


CCMainWindow::CCMainWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);

	// 设置窗口标志位为工具窗口，使其在任务栏中不显示
	setWindowFlags(windowFlags() | Qt::Tool);


	// 加载样式表，使用 "CCMainWindow" 作为样式表的标识
	loadStyleSheet("CCMainWindow");

	initControl();
	initTimer();

}

CCMainWindow::~CCMainWindow()
{
}

void CCMainWindow::initControl()
{
	// 设置树形控件的样式为自定义样式
	ui.treeWidget->setStyle(new CCMainCustomProxyStyle);

	// 设置树形控件的级别图标、头像和状态菜单图标
	setLevelPixmap(0);
	setHeadPixmap(":/Resources/MainWindow/girl.png");
	setStatusMenuIcon(":/Resources/MainWindow/StatusSucceeded.png");

	// 创建水平布局并添加一系列其他应用扩展图标到布局中
	QHBoxLayout* appupLayout = new QHBoxLayout;
	appupLayout->setContentsMargins(0, 0, 0, 0);  // 设置布局的边距
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_7.png", "app_7"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_2.png", "app_2"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_3.png", "app_3"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_4.png", "app_4"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_5.png", "app_5"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_6.png", "app_6"));
	appupLayout->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/skin.png", "app_skin"));
	appupLayout->addStretch();  // 添加伸缩量，使控件平均分布
	appupLayout->setSpacing(2);  // 设置控件之间的间距
	// 将布局应用到应用部件上
	ui.appWidget->setLayout(appupLayout);

	// 在底部布局中添加一系列其他应用扩展图标
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_10.png", "app_10"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_8.png", "app_8"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_11.png", "app_11"));
	ui.bottomLayout_up->addWidget(addOtherAppExtension(":/Resources/MainWindow/app/app_9.png", "app_9"));
	ui.bottomLayout_up->addStretch();  // 添加伸缩量，使控件平均分布

	initContactTree();

	//个性签名
	ui.lineEdit->installEventFilter(this);
	//好友搜索
	ui.searchLineEdit->installEventFilter(this);

	// 连接最小化和关闭按钮的槽函数
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
	ui.nameLabel->adjustSize(); // 调整标签以适应新数据大小

	// 通过 elidedText() 方法处理用户名以适应标签的宽度，防止过长的用户名导致显示问题
	QString name = ui.nameLabel->fontMetrics().elidedText(username, Qt::ElideRight, ui.nameLabel->width());

	ui.nameLabel->setText(name); // 设置用户名

}

void CCMainWindow::setLevelPixmap(int level)
{
	// 级别图标
	// 与按钮相同大小，方便与头像对齐
	QPixmap levelPixmap(ui.levelBtn->size());
	levelPixmap.fill(Qt::transparent);

	// 创建一个绘图对象，绘制到 levelPixmap 上
	QPainter painter(&levelPixmap);
	painter.drawPixmap(0, 4, QPixmap(":/Resources/MainWindow/lv.png"));

	int unitNum = level % 10;     // 级别 个位数，范围 1-9
	int tenNum = level / 10;       // 级别 十位数，范围 10-99

	// 十位数级别值的图像片段，从图像中取出一部分作为显示
	// 只取第一位数，不需要取全部，因为级别不会超过两位数

	//十位,截取图片中的部分进行绘制
	// drawPixmap(绘制点x，绘制点y, 图片，图片左上角x, 图片左上角y, 拷贝宽度, 拷贝高度)

	painter.drawPixmap(10, 4, QPixmap(":/Resources/MainWindow/levelvalue.png"),
		tenNum * 6, 0, 6, 7);

	// 绘制个位数级别值的图像片段
	painter.drawPixmap(16, 4, QPixmap(":/Resources/MainWindow/levelvalue.png"),
		unitNum * 6, 0, 6, 7);

	// 设置按钮图标
	ui.levelBtn->setIcon(levelPixmap);
	// 设置图标大小
	ui.levelBtn->setIconSize(ui.levelBtn->size());
}

void CCMainWindow::setHeadPixmap(const QString & headPath)
{
	QPixmap pix;
	pix.load(":/Resources/MainWindow/head_mask.png");

	//设置标签头像
	ui.headLbael->setPixmap(getRoundImage(QPixmap(headPath),
		pix, ui.headLbael->size()));
}

void CCMainWindow::setStatusMenuIcon(const QString & statusPath)
{
	// 状态图标和按钮尺寸一致
	QPixmap statusBtnPixmap(ui.stausBtn->size());
	statusBtnPixmap.fill(Qt::transparent);// 设置为透明

	QPainter painter(&statusBtnPixmap);
	painter.drawPixmap(4, 4, QPixmap(statusPath));

	// 设置图标
	ui.stausBtn->setIcon(statusBtnPixmap);
	ui.stausBtn->setIconSize(ui.stausBtn->size());
}

QWidget * CCMainWindow::addOtherAppExtension(const QString & appPath, const QString & appName)
{
	QPushButton* btn = new QPushButton(this); // 当前窗口为父对象
	btn->setFixedSize(20, 20); // 设置按钮固定大小为 20x20

	QPixmap pixmap(btn->size());
	pixmap.fill(Qt::transparent); // 填充为透明

	QPainter painter(&pixmap);
	QPixmap appPixmap(appPath); // 加载应用图标

	// 计算绘制图标的起始位置使其居中显示
	painter.drawPixmap((btn->width() - appPixmap.width()) / 2,
		(btn->height() - appPixmap.height()) / 2, appPixmap);

	btn->setIcon(pixmap); // 设置按钮图标
	btn->setIconSize(btn->size()); // 设置图标大小与按钮大小一致
	btn->setObjectName(appName); // 设置对象名
	btn->setProperty("hasborder", true); // 设置带有边框属性

	// 连接按钮点击事件到槽函数
	connect(btn, &QPushButton::clicked, this, &CCMainWindow::onAppIconClicked);

	return btn; // 返回创建的按钮对象
}

void CCMainWindow::initContactTree()
{
	// 连接各种项的事件信号到槽函数
	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onItemClicked(QTreeWidgetItem*, int)));
	connect(ui.treeWidget, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(onItemExpanded(QTreeWidgetItem*)));
	connect(ui.treeWidget, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(onItemCollapsed(QTreeWidgetItem*)));
	connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem*, int)));

	// 创建根节点
	QTreeWidgetItem* pRootGroupItem = new QTreeWidgetItem;
	pRootGroupItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
	pRootGroupItem->setData(0, Qt::UserRole, 0);

	// 创建RootContactItem实例，并设置其为顶层树节点的布局
	RootContactItem* pItemName = new RootContactItem(true, ui.treeWidget);
	QString strGroupName = QString::fromLocal8Bit("所有联系人");
	pItemName->setText(strGroupName);

	// 将根节点添加到树中，并将其布局设置为RootContactItem
	ui.treeWidget->addTopLevelItem(pRootGroupItem);
	ui.treeWidget->setItemWidget(pRootGroupItem, 0, pItemName);

	// 公司部门列表
	QStringList sComDeps;

	sComDeps << QString::fromLocal8Bit("公司群");
	sComDeps << QString::fromLocal8Bit("人事部");
	sComDeps << QString::fromLocal8Bit("市场部");
	sComDeps << QString::fromLocal8Bit("研发部");



	// 遍历公司部门列表并添加到根节点
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
	// 创建一个新的子项
	QTreeWidgetItem* pChild = new QTreeWidgetItem;

	// 加载头像的 pixmap
	QPixmap pix;
	pix.load(":/Resources/MainWindow/head_mask.png");

	// 设置子项的自定义数据，用于标识该项为子项
	pChild->setData(0, Qt::UserRole, 1);

	// 设置子项的唯一标识符ID，转换为字符串类型存储
	pChild->setData(0, Qt::UserRole + 1, QString::number(reinterpret_cast<qulonglong>(pChild)));

	// 创建联系人项，并设置头像和用户名
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);
	pContactItem->setHeadPixmap(getRoundImage(QPixmap(":/Resources/MainWindow/girl.png"), pix, pContactItem->getHeadLabelSize()));
	pContactItem->setUserName(sDeps);

	// 将子项添加到根项中
	pRootGroupItem->addChild(pChild);

	// 将联系人项设置为子项的部件
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);

	// 将子项与其对应的部门名称映射关系存储到 m_groupMap 中
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
	// 在调整窗口大小时设置用户名为默认值
	setUserName(QString::fromLocal8Bit("Vincent"));

	// 调用基类的 resizeEvent 方法以确保正常的窗口调整行为
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
	// 判断事件发生的对象是否为搜索框
	if (ui.searchLineEdit == obj)
	{
		// 判断事件类型是否为获取焦点事件
		if (event->type() == QEvent::FocusIn)
		{
			// 修改搜索框和搜索按钮的样式以响应焦点获取事件
			// 将搜索框的背景颜色设置为白色，同时设置搜索按钮的不同状态下的边框样式
			ui.searchWidget->setStyleSheet(QString("QWidget#searchWidget{background-color:rgb(255,255,255);border-bottom:1px solid rgba(%1,%2,%3,100)} \
                QPushButton#searchBtn{border-image:url(:/Resources/MainWindow/search/main_search_deldown.png)} \
                QPushButton#searchBtn:hover{border-image:url(:/Resources/MainWindow/search/main_search_delhighlight.png)} \
                QPushButton#searchBtn:pressed{border-image:url(:/Resources/MainWindow/search/main_search_delhighdown.png)}")
				.arg(m_colorBackGround.red())
				.arg(m_colorBackGround.green())
				.arg(m_colorBackGround.blue()));
		}
		// 如果事件类型为失去焦点事件
		else if (event->type() == QEvent::FocusOut)
		{
			// 调用函数恢复搜索框的原始样式
			updateSeachStyle();
		}
	}

	// 返回false表示事件会继续传递给目标对象进行处理
	return false;
}

void CCMainWindow::onItemClicked(QTreeWidgetItem* item, int column)
{
	// 判断被点击的项是否为子项，通过自定义数据来判断
	bool bIsChild = item->data(0, Qt::UserRole).toBool();

	// 如果被点击的项不是子项
	if (!bIsChild)
	{
		// 切换被点击的项的展开状态（折叠/展开）
		item->setExpanded(!item->isExpanded());
	}
}


void CCMainWindow::onItemExpanded(QTreeWidgetItem * item)
{
	// 判断是否为子项
	bool bIsChild = item->data(0, Qt::UserRole).toBool();
	if (!bIsChild)
	{
		// 尝试将QWidget指针转换为RootContactItem指针
		// 使用dynamic_cast进行安全的指针类型转换
		RootContactItem* prootItem = dynamic_cast<RootContactItem*>(ui.treeWidget->itemWidget(item, 0));

		// 如果成功转换为RootContactItem指针，则设置展开状态
		if (prootItem)
		{
			prootItem->setExpanded(true);
		}
	}
}

void CCMainWindow::onItemCollapsed(QTreeWidgetItem * item)
{
	// 检查该项是否为子项
	bool bIsChild = item->data(0, Qt::UserRole).toBool();

	// 如果不是子项，则执行后续操作
	if (!bIsChild)
	{
		// 将项关联的小部件转换为RootContactItem类型的指针
		RootContactItem* prootItem = dynamic_cast<RootContactItem*>(ui.treeWidget->itemWidget(item, 0));

		// 如果转换成功，说明该项是根节点
		if (prootItem)
		{
			// 将根节点的展开状态设置为false，即折叠该项
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
		if (strGroup == QString::fromLocal8Bit("公司群"))
		{
			WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), COMPANY);
			qDebug() << "Group is 公司群";
		}
		else if (strGroup == QString::fromLocal8Bit("人事部"))
		{
			WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), PERSONELGROUP);
		}
		else if (strGroup == QString::fromLocal8Bit("市场部"))
		{
			WindowManager::getInstance()->addNewTalkWindow(item->data(0, Qt::UserRole + 1).toString(), MARKETGROUP);
		}
		else if (strGroup == QString::fromLocal8Bit("研发部"))
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