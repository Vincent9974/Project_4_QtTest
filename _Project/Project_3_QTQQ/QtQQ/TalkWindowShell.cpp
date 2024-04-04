#include "TalkWindowShell.h"
#include "CommonUtils.h"
#include "BasicWindow.h"
#include <QListWidget>
#include "TalkWindow.h"
#include "TalkWindowItem.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFile>
#include "UserLogin.h"

extern QString gLoginEmployeeID;

// TalkWindowShell 类的构造函数
TalkWindowShell::TalkWindowShell(QWidget *parent)
	: BasicWindow(parent) // 调用父类构造函数进行初始化
{
	ui.setupUi(this); // 设置 UI

	setAttribute(Qt::WA_DeleteOnClose); // 设置在关闭时删除对象的属性
	initControl(); // 初始化控件

	// 检查是否存在消息模板的 JavaScript 文件
	QFile file("Resources/MainWindow/MsgHtml/msgtmpl.js");

	// 如果 JavaScript 文件不存在或为空，则创建新的 JavaScript 文件
	if (!file.size())
	{
		// 获取员工ID列表
		QStringList employeeIDList;
		getEmployeeID(employeeIDList);

		// 创建新的 JavaScript 文件
		if (!createJSFile(employeeIDList))
		{
			// 如果创建失败，则弹出提示框提示用户
			QMessageBox::information(this,
				QString::fromLocal8Bit("提示"),
				QString::fromLocal8Bit("JS文件创建失败"));
		}
	}
}


// TalkWindowShell 类的析构函数
TalkWindowShell::~TalkWindowShell()
{
	delete m_emotionWindow; // 删除 m_emotionWindow 对象
	m_emotionWindow = nullptr; // 置空指针
}

// 设置当前显示的窗口
void TalkWindowShell::setCurrentWidget(QWidget* widget)
{
	ui.rightStackedWidget->setCurrentWidget(widget);
}

// 获取对话窗口项的映射关系
const QMap<QListWidgetItem*, QWidget*>& TalkWindowShell::getTalkWindowItemMap() const
{
	return m_talkwindowItemMap;
}

// 初始化控件
void TalkWindowShell::initControl()
{
	loadStyleSheet("TalkWindow"); // 加载样式表
	setWindowTitle(QString::fromLocal8Bit("聊天窗口1")); // 设置窗口标题

	m_emotionWindow = new EmotionWindow; // 创建表情窗口对象
	m_emotionWindow->hide(); // 隐藏表情窗口

	QList<int> leftWidgetSize; // 设置左侧窗口的初始大小
	leftWidgetSize << 154 << width() - 154;
	ui.splitter->setSizes(leftWidgetSize);

	ui.listWidget->setStyle(new CustomProxyStyle(this)); // 设置列表控件的自定义样式

	// 连接列表控件项点击信号与槽函数，以及表情窗口表情项点击信号与槽函数
	connect(ui.listWidget, &QListWidget::itemClicked, this, &TalkWindowShell::onTalkWindowItemClicked);
	connect(m_emotionWindow, SIGNAL(signalEmotionItemClicked(int)), this, SLOT(onEmotionItemClicked(int)));
}

void TalkWindowShell::initTcpSocket()
{
	m_tcpClientSocket = new QTcpSocket(this);
	m_tcpClientSocket->connectToHost("127.0.0.1", gtcpPort);
}

void TalkWindowShell::getEmployeeID(QStringList& employeesList)
{
	// 创建一个 SQL 查询模型
	QSqlQueryModel queryModel;
	// 设置 SQL 查询语句，从名为 tab_employee 的表中选择员工ID，其中状态为1
	queryModel.setQuery("SELECT employeeID FROM tab_employees WHERE status = 1");

	// 获取查询结果中的行数，即员工数量
	int employeeNum = queryModel.rowCount();

	// 用于存储查询结果的索引对象
	QModelIndex index;
	// 遍历查询结果的每一行
	for (int i = 0; i < employeeNum; i++)
	{
		// 获取当前行的第一列数据的索引
		index = queryModel.index(i, 0);
		// 将当前行的第一列数据转换为字符串，并添加到员工列表中
		employeesList << queryModel.data(index).toString();
	}
}


bool TalkWindowShell::createJSFile(QStringList & employeeList)
{
	// 获取txt文件路径
	QString strFileTxt = "Resources/MainWindow/MsgHtml/msgtmpl.txt";
	QFile fileRead(strFileTxt);
	QString strFile; // 用于存储读取的文件内容

	// 如果以只读模式成功打开文件，则读取全部内容
	if (fileRead.open(QIODevice::ReadOnly))
	{
		strFile = fileRead.readAll();
		fileRead.close(); // 关闭文件读取器
	}
	else
	{
		// 如果无法打开文件，显示错误提示信息并返回false
		QMessageBox::information(this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("读取 msgtmpl.txt 失败"));
		return false;
	}

	// 替换模板中的external0和appendHtml0为实际的消息信息
	QFile fileWrite("Resources/MainWindow/MsgHtml/msgtmpl.js");


	// 以写入模式打开文件，如果成功则进行写入操作
	if (fileWrite.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		// 定义需要替换的源代码段和实际消息的初始化值
		QString strSourceInitNull = "var external = null;";
		QString strSourceInit = "external = channel.objects.external;";
		QString strSourceNew =
			"new QWebChannel(qt.webChannelTransport,\
			function(channel) {\
			external = channel.objects.external;\
		}\
		); \
		";

		//更新追加recvHtml,脚本中有双引号无法直接进行赋值
		QString strSourceRecvHtml;
		QFile fileRecvHtml("Resources/MainWindow/MsgHtml/recvHtml.txt");

		// 如果成功打开接收消息的文件，则读取全部内容
		if (fileRecvHtml.open(QIODevice::ReadOnly))
		{
			strSourceRecvHtml = fileRecvHtml.readAll();
			fileRecvHtml.close();
		}
		else
		{
			// 如果无法打开文件，显示错误提示信息并返回false
			QMessageBox::information(this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("读取 recvHtml.txt 失败"));
			return false;
		}

		// 定义需要替换的字符串
		QString strReplaceInitNull;
		QString strReplaceInit;
		QString strReplaceNew;
		QString strReplaceRecvHtml;

		// 遍历员工列表，替换相应的字符串
		for (int i = 0; i < employeeList.length(); i++)
		{
			// 编辑替换后的初始化值字符串
			QString strInitNull = strSourceInitNull;
			strInitNull.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceInitNull += strInitNull;
			strReplaceInitNull += "\n";

			// 编辑替换后的初始化字符串
			QString strInit = strSourceInit;
			strInit.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceInit += strInit;
			strReplaceInit += "\n";

			// 编辑替换后的newWebchannel字符串
			QString strNew = strSourceNew;
			strNew.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceNew += strNew;
			strReplaceNew += "\n";

			// 编辑替换后的recvHtml字符串
			QString strRecvHtml = strSourceRecvHtml;
			strRecvHtml.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strRecvHtml.replace("recvHtml", QString("recvHtml_%1").arg(employeeList.at(i)));
			strReplaceRecvHtml += strRecvHtml;
			strReplaceRecvHtml += "\n";
		}

		// 使用替换后的字符串替换源文件中的对应部分
		strFile.replace(strSourceInitNull, strReplaceInitNull);
		strFile.replace(strSourceInit, strReplaceInit);
		strFile.replace(strSourceNew, strReplaceNew);
		strFile.replace(strSourceRecvHtml, strReplaceRecvHtml);

		// 将替换后的内容写入文件
		QTextStream stream(&fileWrite);
		stream << strFile;
		fileWrite.close(); // 关闭文件写入器

		return true; // 返回true表示操作成功
	}
	else
	{
		qDebug() << "File open failed. Error: " << fileWrite.errorString();
		// 如果无法打开文件，显示错误提示信息并返回false
		QMessageBox::information(this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("写入 msgtmpl.js 失败"));
		return false;
	}
}

// 文本数据包的格式：群聊标志 + 发信息员工QQ号 + 收信息QQ号 + 信息类型 + 数据长度 + 数据
// 表情数据包格式： 群聊标志 + 发信息员工QQ号（群QQ号） + 收信息员工QQ号 + 信息类型 + 表情个数 + images + 数据
void TalkWindowShell::updateSendTcpMsg(QString & strData, int & msgType, QString fileName)
{
	// 获取当前对话框
	TalkWindow* curTalkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget());
	// 获取对话ID
	QString talkID = curTalkWindow->getTalkID();

	// 群聊标志
	QString strGroupFlag;
	QString strSend;


	if (talkID.length() == 4) // 群聊ID长度为4
	{
		// 群聊标志为1
		strGroupFlag = "1";
	}
	else
	{
		strGroupFlag = "0";
	}

	// 获取数据长度
	int nstrDataLength = strData.length();
	int dataLength = QString::number(nstrDataLength).length();

	QString strdataLength;


	if (msgType == 1) // 文本消息
	{
		if (dataLength < 5)
		{
			strdataLength = QString(5 - dataLength, '0') + QString::number(nstrDataLength);
		}
		else if (dataLength == 5)
		{
			strdataLength = QString::number(nstrDataLength);
		}
		else
		{
			QMessageBox::information(this,
				QString::fromLocal8Bit("提示"),
				QString::fromLocal8Bit("数据长度超出限制"));
		}

		// 文本数据包的格式：群聊标志 + 发信息员工QQ号 + 收信息QQ号 + 信息类型 + 数据长度 + 数据
		strSend = strGroupFlag + gLoginEmployeeID + talkID + "1" + strdataLength + strData;
	}
	else if (msgType == 0) // 图片消息
	{
		// 表情数据包格式： 群聊标志 + 发信息员工QQ号（群QQ号） + 收信息员工QQ号 + 信息类型 + 表情个数 + images + 数据
		strSend = strGroupFlag + gLoginEmployeeID + talkID + "0" + strData;
	}
	else if (msgType == 2) // 文件消息
	{
		// 文件数据包格式： 群聊标志 + 发信息员工QQ号（群QQ号） 
		// + 收信息员工QQ号  + 信息类型(2) + 文件长度 + "bytes" 
		// + 文件名称 + “data_begin”+ 文件内容

		QByteArray bt = strData.toUtf8();
		QString strLength = QString::number(bt.length());

		strSend = strGroupFlag + gLoginEmployeeID + talkID + "2" + strLength
			+ "bytes" + fileName + "data_begin" + strData;
	}

	QByteArray dataBt;
	dataBt.resize(strSend.length());
	dataBt = strSend.toUtf8();

	m_tcpClientSocket->write(dataBt);
}

// 向 TalkWindowShell 中添加对话窗口和对应的项
void TalkWindowShell::addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, const QString& uid/*, GroupType groupType*/)
{
	ui.rightStackedWidget->addWidget(talkWindow);

	// 添加表情窗口的信号连接，当表情窗口隐藏时，设置聊天窗口的表情按钮状态
	connect(m_emotionWindow, SIGNAL(signalEmotionWindowHide()),
		talkWindow, SLOT(onSetEmotionBtnStatus()));

	// 创建一个列表项，用于显示在左侧列表中
	QListWidgetItem* aItem = new QListWidgetItem(ui.listWidget);

	// 将列表项与聊天窗口进行映射
	m_talkwindowItemMap.insert(aItem, talkWindow);

	aItem->setSelected(true);   // 默认选中

	//判断群聊单聊
	QSqlQueryModel sqlDepModel;
	QString strQuery = QString("SELECT picture FROM tab_department WHERE departmentID = %1").arg(uid);
	sqlDepModel.setQuery(strQuery);
	int rows = sqlDepModel.rowCount();          // 获取行数

	// 判断是群组还是个人，如果行数为0，则说明是个人
	if (rows == 0)
	{
		strQuery = QString("SELECT picture FROM tab_employees WHERE employeeID = %1").arg(uid);
		sqlDepModel.setQuery(strQuery);
	}

	QModelIndex index;
	index = sqlDepModel.index(0, 0);        // 获取第一行第一列

	QImage img;
	// 加载头像图片
	img.load(sqlDepModel.data(index).toString());

	// 设置头像
	talkWindowItem->setHeadPixmap(QPixmap::fromImage(img));
	// 添加列表项
	ui.listWidget->addItem(aItem);
	// 设置列表项的窗口部件
	ui.listWidget->setItemWidget(aItem, talkWindowItem);

	// 触发列表项点击事件
	onTalkWindowItemClicked(aItem);

	// 添加关闭按钮的信号连接，实现关闭窗口的功能
	connect(talkWindowItem, &TalkWindowItem::signalCloseClicked, [talkWindowItem, talkWindow, aItem, this]()
	{
		// 从映射中移除列表项
		m_talkwindowItemMap.remove(aItem);     // 删除映射
		talkWindow->close();                                    // 关闭聊天窗口
		// 从列表中移除列表项
		ui.listWidget->takeItem(ui.listWidget->row(aItem));
		delete talkWindowItem;

		// 从右侧布局中移除聊天窗口
		ui.rightStackedWidget->removeWidget(talkWindow);

		// 如果没有聊天窗口了，则关闭主窗口
		if (ui.rightStackedWidget->count() < 1)
		{
			close();
		}
	});

}

// 处理表情按钮点击事件
void TalkWindowShell::onEmotionBtnClicked(bool)
{
	m_emotionWindow->setVisible(!m_emotionWindow->isVisible()); // 切换表情窗口的可见性

	// 将表情窗口移动到合适的位置
	QPoint emotionPoint = this->mapToGlobal(QPoint(0, 0));
	emotionPoint.setX(emotionPoint.x() + 170);
	emotionPoint.setY(emotionPoint.y() + 220);
	m_emotionWindow->move(emotionPoint);
}

// 处理表情项点击事件
void TalkWindowShell::onEmotionItemClicked(int emotionNum)
{
	TalkWindow* curTalkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget()); // 获取当前显示的对话窗口
	if (curTalkWindow) // 判断当前对话窗口是否有效
	{
		curTalkWindow->addEmotionImage(emotionNum); // 向当前对话窗口添加表情图片
	}
}

// 处理对话窗口项点击事件
void TalkWindowShell::onTalkWindowItemClicked(QListWidgetItem* item)
{
	QWidget* talkWindowWidget = m_talkwindowItemMap.find(item).value(); // 获取对应的对话窗口
	ui.rightStackedWidget->setCurrentWidget(talkWindowWidget); // 设置当前显示的窗口为对话窗口
}
