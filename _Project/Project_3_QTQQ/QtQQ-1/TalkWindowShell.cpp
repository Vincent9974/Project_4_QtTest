#include "TalkWindowShell.h"
#include "CommonUtils.h"
#include "BasicWindow.h"
#include <QListWidget>
#include "TalkWindow.h"
#include "TalkWindowItem.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QFile>
#include "UserLogin.h"
#include "WindowManager.h"
#include "ReceiveFile.h"
#include "SendFile.h"

extern QString gLoginEmployeeID;

QString gfileName;
QString gfileData;

// TalkWindowShell 类的构造函数
TalkWindowShell::TalkWindowShell(QWidget *parent)
	: BasicWindow(parent) // 调用父类构造函数进行初始化
{
	ui.setupUi(this); // 设置 UI

	setAttribute(Qt::WA_DeleteOnClose); // 设置在关闭时删除对象的属性
	initControl(); // 初始化控件
	initTcpSocket();
	initUdpSocket();

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

void TalkWindowShell::initUdpSocket()
{
    m_udpRecevier = new QUdpSocket(this);
    for (quint16 port = gudpPort; port < gudpPort + 200; ++port)
    {
        // 尝试绑定端口，如果成功则退出循环
        if (m_udpRecevier->bind(port, QUdpSocket::ShareAddress))
        {
            break;
        }
    }

    // 绑定成功后，设置信号槽连接，准备接收数据
    // 当有数据可读时，触发readyRead信号，调用processPendingData函数处理数据
    connect(m_udpRecevier, &QUdpSocket::readyRead, this, &TalkWindowShell::processPendingData);
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


bool TalkWindowShell::createJSFile(QStringList& employeeList)
{
	// 读取txt文件数据
	QString strFileTxt = "Resources/MainWindow/MsgHtml/msgtmpl.txt";
	QFile fileRead(strFileTxt);

	QString strFile;			// 保存读取到的数据

	// 判断以只读模式打开，能否打开成功
	if (fileRead.open(QIODevice::ReadOnly))
	{
		// 打开成功，读取全部
		strFile = fileRead.readAll();
		fileRead.close();			// 读取完了就关闭
	}
	else
	{
		QMessageBox::information(this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("读取 msgtmpl.txt 失败"));
		return false;
	}

	// 替换（external0，appendHtml0，用作自己发信息使用）
	QFile fileWrite("Resources/MainWindow/MsgHtml/msgtmpl.js");

	// 写入模式 ，和 覆盖模式
	if (fileWrite.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		/*
			1，初始化对象为 null
			2，通道里面设置对象
			3，在接受html那里写入数据
		*/

		// 更新空值
		// 原始的，初始化的，空值的代码
		QString strSourceInitNull = "var external = null;";

		// 更新初始化
		// 原始的，初始化的，对象的代码
		QString strSourceInit = "external = channel.objects.external;";

		// 更新newWebchannel
		// 这里把 external0 去掉，等到时候再添加上
		// 原始的都用 external
		QString strSourceNew =
			"new QWebChannel(qt.webChannelTransport,\
			function(channel) {\
			external = channel.objects.external;\
		}\
		); \
		";

		// 更新追加recvHtml
		/*
			这一段里面有双引号，会引起冲突
			所以不能像上面那样直接写在双引号里，

			因此，要通过读取字符串的方法，读到 strSourceRecvHtml 里面
			把下面这段代码，单独放到一个 txt文件里，再进行读取

			function recvHtml(msg){
					$("#placeholder").append(external.msgLHtmlTmpl.format(msg));
					window.scrollTo(0,document.body.scrollHeight); ;
			};
		*/
		QString strSourceRecvHtml;
		QFile fileRecvHtml("Resources/MainWindow/MsgHtml/recvHtml.txt");
		if (fileRecvHtml.open(QIODevice::ReadOnly))
		{
			// 先读取全部，再赋值，再关闭
			strSourceRecvHtml = fileRecvHtml.readAll();
			fileRecvHtml.close();
		}
		else
		{
			QMessageBox::information(this,
				QString::fromLocal8Bit("提示"),
				QString::fromLocal8Bit("读取 recvHtml.txt 失败"));
			return false;
		}

		// 保存替换后的脚本，对应上面的4个
		QString strReplaceInitNull;
		QString strReplaceInit;
		QString strReplaceNew;
		QString strReplaceRecvHtml;

		for (int i = 0; i < employeeList.length(); i++)
		{
			// 编辑替换后的 空值
			QString strInitNull = strSourceInitNull;
			strInitNull.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceInitNull += strInitNull;
			strReplaceInitNull += "\n";

			// 编辑替换后的 初始值
			QString strInit = strSourceInit;
			strInit.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceInit += strInit;
			strReplaceInit += "\n";

			// 编辑替换后的 newWebchannel
			QString strNew = strSourceNew;
			strNew.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strReplaceNew += strNew;
			strReplaceNew += "\n";

			// replace，替换修改的，直接就是 strRecvHtml
			// 编辑替换后的 recvHtml
			QString strRecvHtml = strSourceRecvHtml;
			strRecvHtml.replace("external", QString("external_%1").arg(employeeList.at(i)));
			strRecvHtml.replace("recvHtml", QString("recvHtml_%1").arg(employeeList.at(i)));
			strReplaceRecvHtml += strRecvHtml;
			strReplaceRecvHtml += "\n";
		}

		// 上面的for循环走完，有几个员工，就会出现几组
		// 然后 再将替换后的字符串，
		// 拿来 替换到 读取数据的【原始文件】的 【原字符串】 上
		strFile.replace(strSourceInitNull, strReplaceInitNull);
		strFile.replace(strSourceInit, strReplaceInit);
		strFile.replace(strSourceNew, strReplaceNew);
		strFile.replace(strSourceRecvHtml, strReplaceRecvHtml);

		// strFile 就是最终数据了
		// 用一个文件流，写入进去
		QTextStream stream(&fileWrite);
		stream << strFile;
		fileWrite.close();

		return true;
	}
	else
	{
		QMessageBox::information(this,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("写入 msgtmpl.js 失败"));

		return false;
	}
}

void TalkWindowShell::handleReceivedMsg(int senderEmployeeID, int msgType, QString strMsg)
{
	// QMsgTextEdit，这个类的默认参数，是一个部件指针
	// 将 参数默认值 设为 nullptr ，这样构造对象时候，可以不带参数
	QMsgTextEdit msgTextEdit;	// 信息文本编辑器
	msgTextEdit.setText(strMsg);

	// 这里只处理 文本信息，表情信息。
	// 文件类型，不调用这个方法
	if (msgType == 1)	// 文本信息
	{
		// 将信息，转换为 html
		msgTextEdit.document()->toHtml();
	}
	else if (msgType == 0)	// 表情信息
	{
		// 每个表情所占宽度
		const int emotionWidth = 3;
		// 计算表情数量，数据长度 除以 每个表情宽度
		int emotionNum = strMsg.length() / emotionWidth;

		// 遍历数据中的 表情，添加html里去
		for (int i = 0; i < emotionNum; i++)
		{
			// 截取数据中的字符串，
			// 从哪里截取，从数据最开始的地方截取(在调用这个函数之前，数据已经处理完了，拿到了最后的表情数据部分)
			// 截取宽度：一次截取3个宽度(表情060，005，101)，每个表情占3位宽度
			// 再转成int类型，加载进去
			msgTextEdit.addEmotionUrl(strMsg.mid(i * 3, emotionWidth).toInt());
		}
	}

	// 判断，追加html的文本里面，有没有字体，颜色的设置
	// 如果发送的是表情，则不需要判断
	QString hemlText = msgTextEdit.document()->toHtml();

	// 文本HTML，如果没有字体，则添加字体
	// 首先要保证是 文本类型
	// 如果是表情的话，字符串中 肯定有 .png
	if (!hemlText.contains(".png") && !hemlText.contains("</span>"))
	{
		QString fontHtml;
		QFile file(":/Resources/MainWindow/MsgHtml/msgFont.txt");
		if (file.open(QIODevice::ReadOnly))
		{
			fontHtml = file.readAll();
			// 将html文件里的 %1，用字符串 text 替换
			fontHtml.replace("%1", strMsg);
			file.close();
		}
		else
		{
			// this，当前聊天部件，作为父窗体
			QMessageBox::information(this, QString::fromLocal8Bit("提示"),
				QString::fromLocal8Bit("文件 msgFont.txt 不存在！"));
			return;
		}

		// 判断转换后，有没有包含 fontHtml
		if (!hemlText.contains(fontHtml))
		{
			hemlText.replace(strMsg, fontHtml);
		}
	}

	/*
		将数据添加到"网页"中
		TalkWindowShell中，右侧部件rightStackedWidget，里面有很多页面
		每个页面，就是一个聊天窗口
		所以在将数据添加到"网页"时，要添加到当前的"页面"中
	*/

	// 先获取 窗口地址
	// 右侧部件rightStackedWidget，获取当前的 活动页面
	// 返回的是 QWidget类型指针，要转换成 TalkWindow* 类型指针
	TalkWindow* talkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget());

	// 终于最后一步，开始 追加信息
	// 1）：转换类型问题
	// appendMsg()，函数原型，第二个参数是字符串，传的是 发送者的ID
	// 在当前这个函数里，参数 发送者的ID 是int类型，两个类型不匹配，因此要转换一下
	// 2）：这个ui是 TalkWindow 的私有成员，在 TalkWindowShell 里无法访问
	// 因此 设置成友元类
	talkWindow->ui.msgWidget->appendMsg(hemlText, QString::number(senderEmployeeID));
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

/*
	数据包的格式（都是咱们自己进行的，数据约定）

	文本数据包格式：群聊标志 + 发信息员工QQ号 + 收信息员工QQ号（群QQ号）
		+ 信息类型(1) + 数据长度 + 数据

	表情数据包格式：群聊标志 + 发信息员工QQ号 + 收信息员工QQ号（群QQ号）
		+ 信息类型(0) + 表情个数 + images + 表情名称

	文件数据包格式：群聊标志 + 发信息员工QQ号 + 收信息员工QQ号（群QQ号）
		+ 信息类型(2) + 文件字节数 + bytes + 文件名 + data_begin + 文件数据

	群聊标志占1位，0单聊，1群聊
	信息类型占1位，0表情信息，1文本信息，2文件信息

	QQ号占5位，群QQ号占4位，
	数据长度占5位，
	表情名称占3位，不足3位，前面用0补全
	（这个占位，就是数据宽度的意思，下面有仔细解释）

	注意：
	当群聊标志为0时，则数据包中，就不是【收信息群QQ号】，而是【收信息员工QQ号】
	当群聊标志为1时，则数据包中，就不是【收信息员工QQ号】，而是【收信息群QQ号】

	群聊文本信息，例：
	【1100012001100005Hello】
	【1 10001 2001 1 00005 Hello】
	群聊文本信息解析：【群聊 发送消息的员工QQ号 接收消息的群QQ号 文本类型 数据宽度为5 数据内容】
	表示：QQ号10001 向群2001发送文本信息，长度是5，数据内容为 Hello

	单聊图片信息，例：
	【0100011000201images060】
	【0 10001 10002 0 1images 060】
	单聊图片信息解析：【单聊 发送消息的员工QQ号 接受消息的员工QQ号 图片类型 表情个数 表情名称】
	表示：员工QQ号10001 向员工QQ号10002发送信息 图片类型 1个表情 表情名称60(表情名称不足3位，前面用0补全)

	群聊文件信息，例：
	【1100052001210bytestest.txtdata_beginhelloworld】
	【1 10005 2001 2 10bytes test.txt data_begin helloworld】
	群聊文件信息解析：【群聊 发送消息的员工QQ号 接收消息的群QQ号 文件类型 文件内容长度 文件名 区分符号 文件内容 】
	表示：QQ号10001 向群2001 发送文件信息，文件内容长度是10，文件名test.txt，区分符号data_begin，文件内容helloworld

*/


void TalkWindowShell::processPendingData()
{
	// 端口中，有未处理的数据
	// 调用方法 hasPendingDatagrams()，返回值 就会告诉我们，是否有未处理的数据
	while (m_udpRecevier->hasPendingDatagrams())
	{
		// 定义一些变量，用于 解包时定位
		// 这些位置是固定的，不会发生改变，因此用const static
		const static int groupFlagWidth = 1;	// 群聊标志宽度，占1位
		const static int groupWidth = 4;		// 群QQ号宽度，占4位
		const static int employeeWidth = 5;		// 员工QQ号宽度
		const static int msgTypeWidth = 1;		// 信息类型宽度
		const static int msgLengthWidth = 5;	// 文本数据宽度，最多占5位
		const static int pictureWidth = 3;		// 表情图片宽度，

		QByteArray btData;
		btData.resize(m_udpRecevier->pendingDatagramSize());
		m_udpRecevier->readDatagram(btData.data(), btData.size());


		QString strData = btData.data();
		QString strWindowID;
		QString strSendEmployeeID, strRecevieEmployeeID;
		QString strMsg;		// 数据

		int msgLength;		// 数据长度
		int msgType;		// 数据类型

		// 通过 数据调用.mid()方法，获取 发送端的QQ号
		// mid(截取位置，截取多长)方法，从字符串中截取 子字符串
		strSendEmployeeID = strData.mid(groupFlagWidth, employeeWidth);


		// 自己发的信息，不做数据处理
		if (strSendEmployeeID == gLoginEmployeeID)
		{
			return;		// 直接返回
		}

		// 判断标志位，如果是1，则为群聊
		if (btData[0] == '1')
		{
			// 获取群聊ID
			strWindowID = strData.mid(groupFlagWidth + employeeWidth, groupWidth);

			QChar cMsgType = btData[groupFlagWidth + employeeWidth + groupWidth];
			// 判断 是不是文本信息
			if (cMsgType == '1')
			{
				msgType = 1;

				// 获取文本信息 长度
				msgLength = strData.mid(groupFlagWidth + employeeWidth + groupWidth + msgTypeWidth
					, msgLengthWidth).toInt();

				// 获取 数据包里的 文本数据
				strMsg = strData.mid(groupFlagWidth + employeeWidth + groupWidth + msgTypeWidth + msgLengthWidth
					, msgLength);

			}
			// 判断 是不是表情信息
			else if (cMsgType == '0')
			{
				msgType = 0;

				// 先找一下 images 字符串的位置
				// indexOf()方法，传入字符串，
				// 返回 字符串 第一次出现的位置
				int posImages = strData.indexOf("images");

				// 获取表情信息字符串
				// right()方法，参数传入 "位置"，获取到 位置右侧所有数据
				// 上面拿到了 第一次出现images的位置 的下标数值
				// 用 数据总长度 减去 第一次出现images的位置 再减去 images本身的长度
				strMsg = strData.right(strData.length() - posImages - QString("images").length());

			}
			else if (cMsgType == '2')
			{
				msgType = 2;

				// 计算 bytes 的长度
				int bytesWidth = QString("bytes").length();
				// bytes，第一次出现的位置
				int posBytes = strData.indexOf("bytes");
				// data_begin，第一次出现的位置
				int posData_begin = strData.indexOf("data_begin");


				// 获取 文件名称
				// 从 bytes第一次出现的位置 + bytes的长度 开始截取，
				// 截取长度： data_begin第一次出现的位置 减去 bytes第一次出现的位置 
				//					再减去 bytes的长度
				QString fileName = strData.mid(posBytes + bytesWidth
					, posData_begin - posBytes - bytesWidth);
				// 将解析出来的 文件名称，赋值给全局变量
				gfileName = fileName;

				// 文件内容
				int dataLengthWidth;	// 文件数据的宽度
				int posData = posData_begin + QString("data_begin").length();
				// 提取数据，文件数据
				strMsg = strData.mid(posData);

				// 将解析出来的 文件内容，赋值给全局变量
				gfileData = strMsg;

				// 根据employeeID获取发送者姓名
				QString sender;
				int empID = strSendEmployeeID.toInt();	// 转换成整形
				QSqlQuery querySenderName(QString("SELECT employee_name FROM tab_employees WHERE employeeID = %1")
					.arg(empID));
				querySenderName.exec();		// 执行以下SQL语句

				// 判断，数据库里 是否有数据
				if (querySenderName.first())
				{
					sender = querySenderName.value(0).toString();
				}

				// 接收文件的后续操作...
				ReceiveFile* recvFile = new ReceiveFile(this);

				// 用了点了取消，发送 返回信号
				connect(recvFile, &ReceiveFile::refuseFile, [this]()
					{
						return;
					});

				// 收到xxx的信息
				QString msgLabel = QString::fromLocal8Bit("收到来自") + sender
					+ QString::fromLocal8Bit("发来的文件，是否接收？");
				// 将文本字符串，设置到标签上
				recvFile->setMsg(msgLabel);
				recvFile->show();

			}

		}
		
		else // 单聊
		{
			// 获取接收者的QQ号
			strRecevieEmployeeID = strData.mid(groupFlagWidth + employeeWidth, employeeWidth);
			// 获取接收者ID昵称，字符串
			strWindowID = strSendEmployeeID;

			// 不是我的信息，不做处理
			// 接收者的ID 和 登陆者的ID ，不是一样的，则直接返回
			if (strRecevieEmployeeID != gLoginEmployeeID)
			{
				return;
			}


			// 获取信息的类型
			QChar cMsgType = btData[groupFlagWidth + employeeWidth + employeeWidth];

			// 判断信息类型
			// 文本信息
			if (cMsgType == '1')
			{
				msgType = 1;

				// 提取，文本信息的长度
				msgLength = strData.mid(groupFlagWidth + employeeWidth + employeeWidth
					+ msgTypeWidth, msgLengthWidth).toInt();

				// 文本信息
				strMsg = strData.mid(groupFlagWidth + employeeWidth + employeeWidth
					+ msgTypeWidth + msgLengthWidth, msgLength);

			}
			// 表情信息
			else if (cMsgType == '0')
			{
				msgType = 0;
				int posImages = strData.indexOf("images");
				int imagesWidth = QString("images").length();

				// mid()，第二个参数不写，不指定 截取宽度
				// 意思是 从截取位置到最后，所有的内容
				strMsg = strData.mid(posImages + imagesWidth);

			}
			
			// 文件信息
			else if (cMsgType == '2')
			{
				msgType = 2;

				int bytesWidth = QString("bytes").length();
				int posBytes = strData.indexOf("bytes");
				int data_beginWidth = QString("data_begin").length();
				int posData_begin = strData.indexOf("data_begin");

				// 文件名称
				QString fileName = strData.mid(posBytes + bytesWidth
					, posData_begin - posBytes - bytesWidth);
				gfileName = fileName;

				// 文件内容
				strMsg = strData.mid(posData_begin + data_beginWidth);
				gfileData = strMsg;

				// 根据employeeID获取发送者姓名
				QString sender;
				int empID = strSendEmployeeID.toInt();	// 转换成整形
				QSqlQuery querySenderName(QString("SELECT employee_name FROM tab_employee WHERE employeeID = %1")
					.arg(empID));
				querySenderName.exec();		// 执行以下SQL语句

				// 判断，数据库里 是否有数据
				if (querySenderName.first())
				{
					sender = querySenderName.value(0).toString();
				}

				// 接收文件的后续操作...
				ReceiveFile* recvFile = new ReceiveFile(this);

				// 用了点了取消，发送 返回信号
				connect(recvFile, &ReceiveFile::refuseFile, [this]()
					{
						return;
					});

				// 收到xxx的信息
				QString msgLabel = QString::fromLocal8Bit("收到来自") + sender
					+ QString::fromLocal8Bit("发来的文件，是否接收？");
				// 将文本字符串，设置到标签上
				recvFile->setMsg(msgLabel);
				recvFile->show();
			}
			
		}
		

		/*
			数据解析出来之后，将数据添加到 接收信息的网页里去
			发送到服务端，进行广播分发，这样信息接收者才能收到数据

			假设，
			现在打开 公司群 ，研发群 ，2个聊天窗口，
			当前活动窗口是 公司群，
			如果 这时 研发群发来消息 ，我们是看不到的，
			所以 就要把 研发群聊天窗口，设置为 活动窗口
			再在 研发群聊天窗口上面，显示接收到的信息

			如果 这时 人事群发来消息，就不做处理了
			因为，没有打开 人事群窗口

			先获取窗口QQ号，看看这个窗口有没有打开
			如果打开了，就设为活动窗口，接收消息
			如果没打开，就直接返回，不做处理了

		*/

		// 将聊天窗口，设为活动的窗口
		QWidget* widget = WindowManager::getInstance()->findWindowName(strWindowID);

		// 判断窗口是否打开
		if (widget)
		{
			// 已存在，就设为活动窗口
			this->setCurrentWidget(widget);

			// 将左侧聊天列表，同步激活
			// 通过映射，获取所有聊天窗口的值，
			// 保存到 QListWidgetItem 部件链表里
			QListWidgetItem* item = m_talkwindowItemMap.key(widget);
			item->setSelected(true);	// 设为选中，活动状态
		}

		else
		{
			return;		// 不存在，直接返回
		}

		// 对信息类型做判断，如果是文件类型，则不调用 handleReceivedMsg()
		if (msgType != 2)
		{
			int sendEmployeeID = strSendEmployeeID.toInt();
			// "网页"上追加数据
			handleReceivedMsg(sendEmployeeID, msgType, strMsg);
		}
	}
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
