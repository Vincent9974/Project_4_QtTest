#include "TalkWindow.h"
#include "ContactItem.h"
#include "CommonUtils.h"
#include "WindowManager.h"
#include "RootConcatItem.h"


#include <QToolTip>
#include <QFile>
#include <QMessageBox>


TalkWindow::TalkWindow(QWidget* parent, const QString& uid, GroupType groupType)
	: QWidget(parent),
	m_talkId(uid),
	m_groupType(groupType)
{
	ui.setupUi(this);

	// 将窗口名字与实例对象关联，以便在窗口关闭时删除窗口名字的映射
	WindowManager::getInstance()->addWindowName(m_talkId, this);
	setAttribute(Qt::WA_DeleteOnClose); // 在窗口关闭时自动删除对象
	initControl();
}

TalkWindow::~TalkWindow()
{
	// 窗口关闭时删除窗口名字的映射
	WindowManager::getInstance()->deleteWindowName(m_talkId);
}

void TalkWindow::addEmotionImage(int emotionNum)
{

}

void TalkWindow::setWindowName(const QString & name)
{
	ui.nameLabel->setText(name);
}

void TalkWindow::initControl()
{
	// 设置右侧窗口大小
	QList<int> rightWidgetSize;
	rightWidgetSize << 600 << 138;
	ui.bodySplitter->setSizes(rightWidgetSize);

	ui.textEdit->setFontPointSize(10);
	ui.textEdit->setFocus(); // 获取焦点，打开窗口时直接输入，不需要再点击输入框获取焦点


	// 最小化、关闭按钮连接到父窗口的槽函数
	connect(ui.sysmin, SIGNAL(clicked(bool)), parent(), SLOT(onShowMin(bool)));
	connect(ui.sysclose, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));
	connect(ui.closeBtn, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));

	// 表情按钮连接到父窗口的槽函数
	connect(ui.faceBtn, SIGNAL(clicked(bool)), parent(), SLOT(onEmotionBtnClicked(bool)));

	// 发送按钮连接到当前窗口的槽函数
	connect(ui.sendBtn, SIGNAL(clicked(bool)), this, SLOT(onSendBtnClicked(bool)));

	// 双击树形控件项连接到当前窗口的槽函数
	connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem*, int)));
	// 根据群组类型初始化对话窗口
	switch (m_groupType)
	{
	case COMPANY:
		initCompanyTalk(); // 初始化公司群对话
		break;
	case PERSONELGROUP:
		initPersonelTalk(); // 初始化人事部对话
		break;
	case DEVELOPMENTGROUP:
		initDevelopmentTalk(); // 初始化研发部对话
		break;
	case MARKETGROUP:
		initMarketTalk(); // 初始化市场部对话
		break;
	default:
		initPtoPTalk(); // 默认为个人对话
		break;
	}
}

void TalkWindow::initCompanyTalk()
{
	// 创建根节点
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// 设置子节点指示器的显示策略，指示器表示是否有子节点
	// 指示器的显示策略有三种，当指示器为空时，表示节点没有子节点，当指示器为箭头时，表示节点有子节点，当指示器为加号时，表示节点有子节点但未展开
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// 初始化节点数据
	pRootItem->setData(0, Qt::UserRole, 0);  // 设置节点的用户角色为0

		// 创建根节点的控件
	// 第一个参数表示是否需要表头，默认为false
	// 第二个参数表示父部件指针
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	ui.treeWidget->setFixedHeight(646);  // shell高度 - shell头高(talkwindow)

	int nEmployeeNum = 50;  // 假设有50个员工
	QString qsGroupName = QString::fromLocal8Bit("公司群 %1/%2").arg(0).arg(nEmployeeNum);  // 构造显示的群组名称
	pItemName->setText(qsGroupName);  // 设置显示的群组名称

	// 添加根节点到树形控件
	ui.treeWidget->addTopLevelItem(pRootItem);
	// 设置根节点的控件，第一个参数为根节点指针，第二个参数为列索引，第三个参数为控件指针
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// 展开根节点
	pRootItem->setExpanded(true);

	// 添加群组成员信息
	for (int i = 0; i < nEmployeeNum; i++)
	{
		addPeopInfo(pRootItem);
	}

}

void TalkWindow::initPersonelTalk()
{
	// 创建根节点
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// 设置子节点指示器的显示策略，指示器表示是否有子节点
	// 指示器的显示策略有三种，当指示器为空时，表示节点没有子节点，当指示器为箭头时，表示节点有子节点，当指示器为加号时，表示节点有子节点但未展开
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// 初始化节点数据
	pRootItem->setData(0, Qt::UserRole, 0);  // 设置节点的用户角色为0

		// 创建根节点的控件
	// 第一个参数表示是否需要表头，默认为false
	// 第二个参数表示父部件指针
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	ui.treeWidget->setFixedHeight(646);  // shell高度 - shell头高(talkwindow)

	int nEmployeeNum = 5;  // 假设有50个员工
	QString qsGroupName = QString::fromLocal8Bit("人事部 %1/%2").arg(0).arg(nEmployeeNum);  // 构造显示的群组名称
	pItemName->setText(qsGroupName);  // 设置显示的群组名称

	// 添加根节点到树形控件
	ui.treeWidget->addTopLevelItem(pRootItem);
	// 设置根节点的控件，第一个参数为根节点指针，第二个参数为列索引，第三个参数为控件指针
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// 展开根节点
	pRootItem->setExpanded(true);

	// 添加群组成员信息
	for (int i = 0; i < nEmployeeNum; i++)
	{
		addPeopInfo(pRootItem);
	}
}

void TalkWindow::initDevelopmentTalk()
{
	// 创建根节点
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// 设置子节点指示器的显示策略，指示器表示是否有子节点
	// 指示器的显示策略有三种，当指示器为空时，表示节点没有子节点，当指示器为箭头时，表示节点有子节点，当指示器为加号时，表示节点有子节点但未展开
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// 初始化节点数据
	pRootItem->setData(0, Qt::UserRole, 0);  // 设置节点的用户角色为0

		// 创建根节点的控件
	// 第一个参数表示是否需要表头，默认为false
	// 第二个参数表示父部件指针
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	ui.treeWidget->setFixedHeight(646);  // shell高度 - shell头高(talkwindow)

	int nEmployeeNum = 32;  // 假设有50个员工
	QString qsGroupName = QString::fromLocal8Bit("研发部 %1/%2").arg(0).arg(nEmployeeNum);  // 构造显示的群组名称
	pItemName->setText(qsGroupName);  // 设置显示的群组名称

	// 添加根节点到树形控件
	ui.treeWidget->addTopLevelItem(pRootItem);
	// 设置根节点的控件，第一个参数为根节点指针，第二个参数为列索引，第三个参数为控件指针
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// 展开根节点
	pRootItem->setExpanded(true);

	// 添加群组成员信息
	for (int i = 0; i < nEmployeeNum; i++)
	{
		addPeopInfo(pRootItem);
	}
}

void TalkWindow::initMarketTalk()
{
	// 创建根节点
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// 设置子节点指示器的显示策略，指示器表示是否有子节点
	// 指示器的显示策略有三种，当指示器为空时，表示节点没有子节点，当指示器为箭头时，表示节点有子节点，当指示器为加号时，表示节点有子节点但未展开
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// 初始化节点数据
	pRootItem->setData(0, Qt::UserRole, 0);  // 设置节点的用户角色为0

		// 创建根节点的控件
	// 第一个参数表示是否需要表头，默认为false
	// 第二个参数表示父部件指针
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	ui.treeWidget->setFixedHeight(646);  // shell高度 - shell头高(talkwindow)

	int nEmployeeNum = 8;  // 假设有50个员工
	QString qsGroupName = QString::fromLocal8Bit("市场部 %1/%2").arg(0).arg(nEmployeeNum);  // 构造显示的群组名称
	pItemName->setText(qsGroupName);  // 设置显示的群组名称

	// 添加根节点到树形控件
	ui.treeWidget->addTopLevelItem(pRootItem);
	// 设置根节点的控件，第一个参数为根节点指针，第二个参数为列索引，第三个参数为控件指针
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// 展开根节点
	pRootItem->setExpanded(true);

	// 添加群组成员信息
	for (int i = 0; i < nEmployeeNum; i++)
	{
		addPeopInfo(pRootItem);
	}
}

void TalkWindow::initPtoPTalk()
{
	// 当为点对点聊天时，可能还有一张背景图片
	QPixmap pixSkin;
	pixSkin.load(":/Resources/MainWindow/skin.png");

	ui.widget->setFixedSize(pixSkin.size());  // 设置控件的固定大小

	// 设置控件的背景图片
	QLabel* skinLabel = new QLabel(ui.widget);
	skinLabel->setPixmap(pixSkin);

	// 设置标签与控件相同大小
	skinLabel->setFixedSize(ui.widget->size());
}

void TalkWindow::addPeopInfo(QTreeWidgetItem * pRootGroupItem)
{
	// 创建一个新的子项用于存储联系人信息
	QTreeWidgetItem* pChild = new QTreeWidgetItem();

	// 加载头像遮罩图片
	QPixmap pix1;
	pix1.load(":/Resources/MainWindow/head_mask.png");

	// 加载用户头像图片
	const QPixmap image(":/Resources/MainWindow/girl.png");

	// 设置子项数据 
	pChild->setData(0, Qt::UserRole, 1); // 使用 UserRole 存储用户数据
	// 使用 UserRole+1 存储子项的指针地址，用于后续操作标识
	pChild->setData(0, Qt::UserRole + 1, QString::number((int)pChild));

	// 创建联系人项
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);

	static int i = 0;

	// 设置圆形头像
	pContactItem->setHeadPixmap(CommonUtils::getRoundImage(image, pix1, pContactItem->getHeadLabelSize()));
	// 设置用户名
	pContactItem->setUserName(QString::fromLocal8Bit("用户%1").arg(i++));
	pContactItem->setSignName(QString::fromLocal8Bit("(个性签名)"));

	// 将子项添加到根节点下
	pRootGroupItem->addChild(pChild);

	// 将联系人项添加到子项上
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);

	// 获取用户名并将子项指针和用户名添加到映射中，用于后续管理
	QString str = pContactItem->getUserNmae();
	m_groupPeoMap.insert(pChild, str);
}

void TalkWindow::onItemDoubleClicked(QTreeWidgetItem* item, int column)
{
	// 获取项的数据，判断是否为叶子节点
	bool bIsChild = item->data(0, Qt::UserRole).toBool();

	// 如果是叶子节点
	if (bIsChild)
	{
		// 获取人员名称
		QString strPeopleName = m_groupPeoMap.value(item);

		// 通过项的数据获取 ID，用于创建新对话框窗口
		QString itemId = item->data(0, Qt::UserRole + 1).toString();

		// 调用 WindowManager 类的静态函数，创建新的对话框窗口
		// 并传递相应的参数：ID、对话框类型（这里看起来是 PTOP）、人员名称
		WindowManager::getInstance()->addNewTalkWindow(itemId, PTOP, strPeopleName);
	}
}



