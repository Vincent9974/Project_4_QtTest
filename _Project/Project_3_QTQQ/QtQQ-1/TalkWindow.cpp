#include "TalkWindow.h"
#include "ContactItem.h"
#include "CommonUtils.h"
#include "WindowManager.h"
#include "RootConcatItem.h"
#include "SendFile.h"

#include <QToolTip>
#include <QFile>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>

extern QString gLoginEmployeeID;

TalkWindow::TalkWindow(QWidget* parent, const QString& uid/*, GroupType groupType*/)
	: QWidget(parent),
	m_talkId(uid)
	//m_groupType(groupType)
{
	ui.setupUi(this);

	// 将窗口名字与实例对象关联，以便在窗口关闭时删除窗口名字的映射
	WindowManager::getInstance()->addWindowName(m_talkId, this);
	setAttribute(Qt::WA_DeleteOnClose); // 在窗口关闭时自动删除对象
	initGroupTalkStatus();
	initControl();
}

TalkWindow::~TalkWindow()
{
	// 窗口关闭时删除窗口名字的映射
	WindowManager::getInstance()->deleteWindowName(m_talkId);
}

void TalkWindow::addEmotionImage(int emotionNum)
{
	ui.textEdit->setFocus();
	ui.textEdit->addEmotionUrl(emotionNum);
}

void TalkWindow::setWindowName(const QString & name)
{
	ui.nameLabel->setText(name);
}

QString TalkWindow::getTalkID()
{
	return m_talkId;
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


	connect(ui.fileopenBtn, SIGNAL(clicked(bool)), this, SLOT(onFileOpenBtnClicked(bool)));
	
	if (m_isGroupTalk)
	{
		initTalkWindow();
	}
	else
	{
		initPtoPTalk();
	}

	
	/*// 根据群组类型初始化对话窗口
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
	*/
}

void TalkWindow::initGroupTalkStatus()
{
	QSqlQueryModel sqlDepModel;
	QString strSql = QString("SELECT * FROM tab_department WHERE departmentID = %1").arg(m_talkId);
	// 执行 SQL 查询
	sqlDepModel.setQuery(strSql);

	// 获取查询结果的行数，判断是否为0，如果为0则表示不是群聊，否则表示是群聊
	int rows = sqlDepModel.rowCount();


	// 根据判断结果设置成员变量 m_isGroupTalk 的值，以标识当前窗口是否为群聊窗口
	if (rows == 0)
	{
		m_isGroupTalk = false;
	}
	else
	{
		m_isGroupTalk = true;
	}
}

int TalkWindow::getCompDepID()
{
	// 创建一个 SQL 查询对象，用于查询指定部门名称对应的部门ID
	QSqlQuery queryDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'")
		.arg(QString::fromLocal8Bit("公司群")));

	queryDepID.exec();
	queryDepID.next();

	// 返回查询结果集的第一列值，即部门ID
	return queryDepID.value(0).toInt();
}






//void TalkWindow::initCompanyTalk()
//{
//	// 创建根节点
//	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
//
//	// 设置子节点指示器的显示策略，指示器表示是否有子节点
//	// 指示器的显示策略有三种，当指示器为空时，表示节点没有子节点，当指示器为箭头时，表示节点有子节点，当指示器为加号时，表示节点有子节点但未展开
//	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
//
//	// 初始化节点数据
//	pRootItem->setData(0, Qt::UserRole, 0);  // 设置节点的用户角色为0
//
//		// 创建根节点的控件
//	// 第一个参数表示是否需要表头，默认为false
//	// 第二个参数表示父部件指针
//	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);
//
//	ui.treeWidget->setFixedHeight(646);  // shell高度 - shell头高(talkwindow)
//
//	int nEmployeeNum = 50;  // 假设有50个员工
//	QString qsGroupName = QString::fromLocal8Bit("公司群 %1/%2").arg(0).arg(nEmployeeNum);  // 构造显示的群组名称
//	pItemName->setText(qsGroupName);  // 设置显示的群组名称
//
//	// 添加根节点到树形控件
//	ui.treeWidget->addTopLevelItem(pRootItem);
//	// 设置根节点的控件，第一个参数为根节点指针，第二个参数为列索引，第三个参数为控件指针
//	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);
//
//	// 展开根节点
//	pRootItem->setExpanded(true);
//
//	// 添加群组成员信息
//	for (int i = 0; i < nEmployeeNum; i++)
//	{
//		addPeopInfo(pRootItem);
//	}
//
//}
//
//void TalkWindow::initPersonelTalk()
//{
//	// 创建根节点
//	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
//
//	// 设置子节点指示器的显示策略，指示器表示是否有子节点
//	// 指示器的显示策略有三种，当指示器为空时，表示节点没有子节点，当指示器为箭头时，表示节点有子节点，当指示器为加号时，表示节点有子节点但未展开
//	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
//
//	// 初始化节点数据
//	pRootItem->setData(0, Qt::UserRole, 0);  // 设置节点的用户角色为0
//
//		// 创建根节点的控件
//	// 第一个参数表示是否需要表头，默认为false
//	// 第二个参数表示父部件指针
//	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);
//
//	ui.treeWidget->setFixedHeight(646);  // shell高度 - shell头高(talkwindow)
//
//	int nEmployeeNum = 5;  // 假设有50个员工
//	QString qsGroupName = QString::fromLocal8Bit("人事部 %1/%2").arg(0).arg(nEmployeeNum);  // 构造显示的群组名称
//	pItemName->setText(qsGroupName);  // 设置显示的群组名称
//
//	// 添加根节点到树形控件
//	ui.treeWidget->addTopLevelItem(pRootItem);
//	// 设置根节点的控件，第一个参数为根节点指针，第二个参数为列索引，第三个参数为控件指针
//	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);
//
//	// 展开根节点
//	pRootItem->setExpanded(true);
//
//	// 添加群组成员信息
//	for (int i = 0; i < nEmployeeNum; i++)
//	{
//		addPeopInfo(pRootItem);
//	}
//}
//
//void TalkWindow::initDevelopmentTalk()
//{
//	// 创建根节点
//	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
//
//	// 设置子节点指示器的显示策略，指示器表示是否有子节点
//	// 指示器的显示策略有三种，当指示器为空时，表示节点没有子节点，当指示器为箭头时，表示节点有子节点，当指示器为加号时，表示节点有子节点但未展开
//	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
//
//	// 初始化节点数据
//	pRootItem->setData(0, Qt::UserRole, 0);  // 设置节点的用户角色为0
//
//		// 创建根节点的控件
//	// 第一个参数表示是否需要表头，默认为false
//	// 第二个参数表示父部件指针
//	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);
//
//	ui.treeWidget->setFixedHeight(646);  // shell高度 - shell头高(talkwindow)
//
//	int nEmployeeNum = 32;  // 假设有50个员工
//	QString qsGroupName = QString::fromLocal8Bit("研发部 %1/%2").arg(0).arg(nEmployeeNum);  // 构造显示的群组名称
//	pItemName->setText(qsGroupName);  // 设置显示的群组名称
//
//	// 添加根节点到树形控件
//	ui.treeWidget->addTopLevelItem(pRootItem);
//	// 设置根节点的控件，第一个参数为根节点指针，第二个参数为列索引，第三个参数为控件指针
//	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);
//
//	// 展开根节点
//	pRootItem->setExpanded(true);
//
//	// 添加群组成员信息
//	for (int i = 0; i < nEmployeeNum; i++)
//	{
//		addPeopInfo(pRootItem);
//	}
//}
//
//void TalkWindow::initMarketTalk()
//{
//	// 创建根节点
//	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
//
//	// 设置子节点指示器的显示策略，指示器表示是否有子节点
//	// 指示器的显示策略有三种，当指示器为空时，表示节点没有子节点，当指示器为箭头时，表示节点有子节点，当指示器为加号时，表示节点有子节点但未展开
//	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
//
//	// 初始化节点数据
//	pRootItem->setData(0, Qt::UserRole, 0);  // 设置节点的用户角色为0
//
//		// 创建根节点的控件
//	// 第一个参数表示是否需要表头，默认为false
//	// 第二个参数表示父部件指针
//	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);
//
//	ui.treeWidget->setFixedHeight(646);  // shell高度 - shell头高(talkwindow)
//
//	int nEmployeeNum = 8;  // 假设有50个员工
//	QString qsGroupName = QString::fromLocal8Bit("市场部 %1/%2").arg(0).arg(nEmployeeNum);  // 构造显示的群组名称
//	pItemName->setText(qsGroupName);  // 设置显示的群组名称
//
//	// 添加根节点到树形控件
//	ui.treeWidget->addTopLevelItem(pRootItem);
//	// 设置根节点的控件，第一个参数为根节点指针，第二个参数为列索引，第三个参数为控件指针
//	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);
//
//	// 展开根节点
//	pRootItem->setExpanded(true);
//
//	// 添加群组成员信息
//	for (int i = 0; i < nEmployeeNum; i++)
//	{
//		addPeopInfo(pRootItem);
//	}
//}

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

void TalkWindow::initTalkWindow()
{
	// 创建根节点
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// 设置树形控件的指示器显示策略，指示器用于显示是否有子项
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// 初始化用户数据
	pRootItem->setData(0, Qt::UserRole, 0); // 设置用户数据为0，表示非用户节点

	// 创建根节点的子项，用于显示群名称或者部门名称
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	// 设置树形控件的固定高度，以适应界面布局
	ui.treeWidget->setFixedHeight(646);

	// 获取群名称或部门名称
	QString strGroupName;
	QSqlQuery queryGroupName(QString("SELECT department_name FROM tab_department WHERE departmentID = %1").arg(m_talkId));
	queryGroupName.exec();
	if (queryGroupName.next())
	{
		strGroupName = queryGroupName.value(0).toString();
	}

	// 根据部门ID查询员工信息，如果是公司部门则查询所有员工，否则只查询该部门员工
	QSqlQueryModel queryEmployeeModel;
	if (getCompDepID() == m_talkId.toInt())
	{
		queryEmployeeModel.setQuery("SELECT employeeID FROM tab_employees WHERE status = 1");
	}
	else
	{
		queryEmployeeModel.setQuery(QString("SELECT employeeID FROM tab_employees WHERE status = 1 AND departmentID = %1").arg(m_talkId));
	}

	// 获取员工数量
	int nEmployeeNum = queryEmployeeModel.rowCount();

	// 构建群名称的显示字符串，格式为：群名称 群成员数量/总人数
	QString qsGroupName = QString::fromLocal8Bit("%1 %2/%3").arg(strGroupName).arg(0).arg(nEmployeeNum);

	// 将群名称设置为根节点的显示文本
	pItemName->setText(qsGroupName);

	// 添加根节点到树形控件中
	ui.treeWidget->addTopLevelItem(pRootItem);
	// 将根节点的显示项设置为 pItemName，列索引为0
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// 展开根节点
	pRootItem->setExpanded(true);

	// 遍历员工信息，逐个添加到根节点下
	for (int i = 0; i < nEmployeeNum; i++)
	{
		QModelIndex modelindex = queryEmployeeModel.index(i, 0);
		int employeeID = queryEmployeeModel.data(modelindex).toInt();

		//if (employeeID == gLoginEmployeeID.toInt())
		//{
		//	continue;
		//}

		// 根据员工ID添加员工信息到根节点下
		addPeopInfo(pRootItem, employeeID);
	}
}


void TalkWindow::addPeopInfo(QTreeWidgetItem * pRootGroupItem, int employeeID)
{
	// 创建一个子节点用于存储个人信息
	QTreeWidgetItem* pChild = new QTreeWidgetItem();

	// 设置子节点的数据，UserRole 设置为 1，用于标识这是一个个人节点
	pChild->setData(0, Qt::UserRole, 1);
	// 用于标识子节点的地址，设置为 UserRole + 1
	pChild->setData(0, Qt::UserRole + 1, employeeID);

	// 加载默认头像图片
	QPixmap pix1;
	pix1.load(":/Resources/MainWindow/head_mask.png");

	// 获取员工姓名、签名和头像路径
	QString strName, strSign, strPicturePath;
	QSqlQueryModel queryInfoModel;
	queryInfoModel.setQuery(QString("SELECT employee_name, employee_sign, picture FROM tab_employees WHERE employeeID = %1")
		.arg(employeeID));

	QModelIndex nameIndex, signIndex, picIndex;
	nameIndex = queryInfoModel.index(0, 0);
	signIndex = queryInfoModel.index(0, 1);
	picIndex = queryInfoModel.index(0, 2);

	strName = queryInfoModel.data(nameIndex).toString();
	strSign = queryInfoModel.data(signIndex).toString();
	strPicturePath = queryInfoModel.data(picIndex).toString();

	QImage imageHead;
	imageHead.load(strPicturePath);

	// 创建联系人项
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);

	// 设置圆形头像
	pContactItem->setHeadPixmap(CommonUtils::getRoundImage(QPixmap::fromImage(imageHead), pix1, pContactItem->getHeadLabelSize()));
	// 设置姓名和签名
	pContactItem->setUserName(strName);
	pContactItem->setSignName(strSign);

	// 将子节点添加到父节点下
	pRootGroupItem->addChild(pChild);

	// 设置联系人项到子节点
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);

	// 将联系人姓名与子节点地址建立映射关系
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
		// 通过项的数据获取 ID，用于创建新对话框窗口
		QString itemId = item->data(0, Qt::UserRole + 1).toString();

		if (itemId == gLoginEmployeeID) //不能和自己聊天
		{
			return;
		}

		// 获取人员名称
		QString strPeopleName = m_groupPeoMap.value(item);
		// 调用 WindowManager 类的静态函数，创建新的对话框窗口
		// 并传递相应的参数：ID、对话框类型（这里看起来是 PTOP）、人员名称
		WindowManager::getInstance()->addNewTalkWindow(itemId/*, PTOP, strPeopleName*/);
	}
}

void TalkWindow::onSendBtnClicked(bool)
{
	// 检查消息是否为空，为空则提示用户并返回
	if (ui.textEdit->toPlainText().isEmpty())
	{
		// 显示提示信息，位置在 (630, 660) 处，持续时间为 2000 毫秒
		QToolTip::showText(this->mapToGlobal(QPoint(630, 660)),
			QString::fromLocal8Bit("发送消息内容不能为空"),
			this, QRect(0, 0, 120, 100), 2000);
		return;
	}

	// 将纯文本转换为 HTML 格式
	QString& html = ui.textEdit->document()->toHtml();

	// 如果 HTML 中不包含图片和<span>标签，则添加字体样式
	if (!html.contains(".png") && !html.contains("</span>"))
	{
		QString fontHtml;
		QString text = ui.textEdit->toPlainText();
		QFile file(":/Resources/MainWindow/MsgHtml/msgFont.txt");

		if (file.open(QIODevice::ReadOnly))
		{
			fontHtml = file.readAll();
			// 将 HTML 文件中的 %1 占位符替换为消息文本
			fontHtml.replace("%1", text);
			file.close();
		}
		else
		{
			// 如果文件打开失败，则弹出消息框提示用户
			QMessageBox::information(this, QString::fromLocal8Bit("提示"),
				QString::fromLocal8Bit("文件 msgFont.txt 不存在"));
			return;
		}

		// 如果 HTML 中不包含字体样式代码，则替换文本为带有字体样式的 HTML
		if (!html.contains(fontHtml))
		{
			html.replace(text, fontHtml);
		}
	}

	// 清空文本编辑框并删除所有表情图片
	ui.textEdit->clear();
	ui.textEdit->deleteAllEmotionImage();

	ui.msgWidget->appendMsg(html); //收信息窗口添加信息
}

void TalkWindow::onFileOpenBtnClicked(bool)
{
	
	SendFile* sendFile = new SendFile(this);
	sendFile->show();
}





