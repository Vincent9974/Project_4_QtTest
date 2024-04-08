#include "MsgWebView.h" // 包含 MsgWebView 类的头文件
#include "TalkWindowShell.h"
#include "WindowManager.h"
#include <QFile> // 包含文件操作相关的头文件
#include <QMessageBox> // 包含消息框相关的头文件
#include <QJsonObject> // 包含 JSON 对象相关的头文件
#include <QJsonDocument> // 包含 JSON 文档相关的头文件
#include <QWebChannel> // 包含 Web 通道相关的头文件
#include <QSqlQueryModel>

extern QString gstrLoginHeadPath;

// MsgHtmlObj 类的构造函数实现
MsgHtmlObj::MsgHtmlObj(QObject* parent, QString msgLPicPath)
	: QObject(parent) // 使用给定的父对象进行初始化
{
	m_msgLpicPath = msgLPicPath;
	initHtmlTmpl(); // 初始化 HTML 模板
}

// 初始化 HTML 模板的私有成员函数实现
void MsgHtmlObj::initHtmlTmpl()
{
	// 初始化 左侧
	// 将msgleftTmpl中的【%1】，替换成 对方头像路径
	m_msgLHtmlTmpl = getMsgtmplHtml("msgleftTmpl");
	m_msgLHtmlTmpl.replace("%1", m_msgLpicPath);

	// 初始化 右侧
	// 将msgrightTmpl中的【%1】，替换成 对方头像路径
	// gstrLoginHeadPath 是 CCMainWindow 中一个全局变量
	m_msgRHtmlTmpl = getMsgtmplHtml("msgrightTmpl");
	m_msgRHtmlTmpl.replace("%1", gstrLoginHeadPath);
}

// QWebEngineView 视图，用于 显示网页内容
MsgWebView::MsgWebView(QWidget *parent)
	: QWebEngineView(parent)
	, m_channel(new QWebChannel(this))
{
	// 构造一个网页，并 设置为 当前的网页
	MsgWebPage* page = new MsgWebPage(this);
	setPage(page);

	// 通道
	// QWebChannel* channel = new QWebChannel(this);		// 不需要了 注释掉
	m_msgHtmlObj = new MsgHtmlObj(this);

	// 注册
	// "external0" 用于自己发送信息，这个网页对象
	m_channel->registerObject("external0", m_msgHtmlObj);

	TalkWindowShell* talkWindowShell = WindowManager::getInstance()->getTalkWindowShell();
	connect(this, &MsgWebView::signalSendMsg, talkWindowShell, &TalkWindowShell::updateSendTcpMsg);

	/*
		根据当前打开的聊天窗口，
		在构造聊天窗口的时候，才会构造 MsgWebView 网页视图这个类
		所以要看当前构造的是哪个聊天窗口，
		如果当前是研发部，左侧发信息的对象，只能是研发部的群员

		如果是公司群，那就要将公司群的数据拿过来，根据QQ号 注册对象
	*/
	// 先获取左侧聊天窗口的ID
	// 网页视图 在构造的时候，也就是 聊天窗口 正在构造 时候
	// 当前正构建的聊天窗口的ID（QQ号）
	QString strTalkID = WindowManager::getInstance()->getCreatingTalkID();

	// 创建左侧网页对象，主要根据 ID来创建
	// 2种情况：群聊，单聊。公司群QQ号 2000，属于特殊情况
	// 获取 公司群QQ号，然后做对比
	QSqlQueryModel queryEmployeeModel;
	QString strEmployeeID, strPicturePath;
	QString strExternal;
	bool isGroupTalk = false;		// 群聊标志，初始为 false

	queryEmployeeModel.setQuery(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'")
		.arg(QStringLiteral("公司群")));
	// 获取索引
	QModelIndex companyIndex = queryEmployeeModel.index(0, 0);
	// 通过索引获取 公司群的ID
	QString strCompanyID = queryEmployeeModel.data(companyIndex).toString();
	// 判断，当前窗口ID，是不是公司群
	if (strTalkID == strCompanyID)
	{
		isGroupTalk = true;
		// 如果是公司群窗口，就进数据库遍历
		// 把所有状态为1，没有注销的【员工ID和头像】，全提取出来
		queryEmployeeModel.setQuery("SELECT employeeID,picture FROM tab_employees WHERE status = 1");
	}
	else
	{
		// 不是公司群聊窗口
		// 判断QQ号宽度，群里是2001这种占4位宽度，单聊是10001这种占5位
		if (strTalkID.length() == 4)	// 其他群里
		{
			isGroupTalk = true;
			// 获取 某个群，里面的 群员QQ号
			queryEmployeeModel.setQuery(QString("SELECT employeeID,picture FROM tab_employees WHERE status = 1 AND departmentID = %1")
				.arg(strTalkID));

		}
		else  // 单聊
		{
			// 获取 对方QQ号
			queryEmployeeModel.setQuery(QString("SELECT picture FROM tab_employees WHERE status = 1 AND employeeID = %1")
				.arg(strTalkID));
			// 通过索引，找出图片路径，并转成 字符串
			QModelIndex index = queryEmployeeModel.index(0, 0);
			strPicturePath = queryEmployeeModel.data(index).toString();

			strExternal = "external_" + strTalkID;

			// 构建网页对象
			MsgHtmlObj* msgHtmlObj = new MsgHtmlObj(this, strPicturePath);
			m_channel->registerObject(strExternal, msgHtmlObj);		// 注册
		}
	}

	// 进行群聊处理
	if (isGroupTalk)
	{
		QModelIndex employeeModelIndex, pictureModelIndex;
		// 模型总行数
		int rows = queryEmployeeModel.rowCount();
		// 遍历群聊
		for (int i = 0; i < rows; i++)
		{
			// 获取索引
			employeeModelIndex = queryEmployeeModel.index(i, 0);	// 群成员QQ号/ID，索引
			pictureModelIndex = queryEmployeeModel.index(i, 1);		// 群成员头像路径，索引

			// 获取群成员QQ号，ID
			strEmployeeID = queryEmployeeModel.data(employeeModelIndex).toString();
			// 获取群成员 头像路径
			strPicturePath = queryEmployeeModel.data(pictureModelIndex).toString();

			strExternal = "external_" + strEmployeeID;

			MsgHtmlObj* msgHtmlObj = new MsgHtmlObj(this, strPicturePath);
			m_channel->registerObject(strExternal, msgHtmlObj);
		}

	}


	// 设置当前网页，网络通道
	this->page()->setWebChannel(m_channel);

	// 加载网页，进行初始化
	this->load(QUrl("qrc:/Resources/MainWindow/MsgHtml/msgTmpl.html"));
}

// MsgWebView 类的析构函数实现
MsgWebView::~MsgWebView()
{
}

// 获取消息模板 HTML 内容的私有成员函数实现
QString MsgHtmlObj::getMsgtmplHtml(const QString& code)
{
	// 构造文件路径
	QFile file(":/Resources/MainWindow/MsgHtml/" + code + ".html");

	// 打开文件
	file.open(QFile::ReadOnly);
	QString strData;

	if (file.isOpen()) // 如果文件成功打开
	{
		strData = QLatin1String(file.readAll()); // 读取文件内容并转换为字符串
	}
	else // 如果文件打开失败
	{
		// 显示消息框提示失败信息
		QMessageBox::information(nullptr, "Tips", "Failed to init html!");
		return QString(""); // 返回空字符串
	}

	file.close(); // 关闭文件

	return strData; // 返回文件内容字符串
}

// 接受导航请求的函数实现
bool MsgWebPage::acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame)
{
	// 判断 URL 是否为 qrc 格式
	if (url.scheme() == QString("qrc"))
	{
		return true; // 如果是 qrc 格式，则允许导航
	}
	else
	{
		return false; // 否则不允许导航
	}
}

// 解析 HTML 字符串的私有成员函数实现
QList<QStringList> MsgWebView::parseHtml(const QString& html)
{
	QDomDocument doc;
	doc.setContent(html); // 解析 HTML 字符串为 QDomDocument 对象


	// 获取 body 标签下的所有子节点
	const QDomElement& root = doc.documentElement();
	const QDomNode& node = root.firstChildElement("body");

	// 解析节点并返回解析结果
	return parseDocNode(node);
}

// 解析节点的私有成员函数实现
QList<QStringList> MsgWebView::parseDocNode(const QDomNode& node)
{
	QList<QStringList> attribute;
	const QDomNodeList& list = node.childNodes(); // 获取子节点列表


	// 遍历子节点列表
	for (int i = 0; i < list.count(); i++)
	{
		const QDomNode& node = list.at(i);

		if (node.isElement()) // 如果是元素节点
		{
			const QDomElement& element = node.toElement(); // 转换为元素节点

			if (element.tagName() == "img") // 如果是 img 标签
			{
				QStringList attributeList;
				attributeList << "img" << element.attribute("src"); // 获取图片路径并添加到属性列表中
				attribute << attributeList; // 添加属性列表到结果列表中
			}


			if (element.tagName() == "span") // 如果是 span 标签
			{
				QStringList attributeList;
				attributeList << "text" << element.text(); // 获取文本内容并添加到属性列表中
				attribute << attributeList; // 添加属性列表到结果列表中
			}

			if (node.hasChildNodes()) // 如果节点还有子节点
			{
				attribute << parseDocNode(node); // 递归解析子节点并添加到结果列表中
			}
		}
	}

	return attribute; // 返回解析结果列表
}

void MsgWebView::appendMsg(const QString& html, QString strObj)
{
	QJsonObject msgObj;
	QString qsMsg;
	const QList<QStringList> msgList = parseHtml(html);		// 解析 html

	// 信息类型，默认给1
	// 0是表情，1是文本，2是文件
	int msgType = 1;
	bool isImageMsg = false;	// 默认的图片信息
	int imageNum = 0;			// 表情数量，默认给0
	QString strData;			// 055，008，表情名称，宽度不够用0补全


	for (int i = 0; i < msgList.size(); i++)
	{
		// 如果 msgList当前循环的，链表的 第一个元素
		// 是 img 文件
		if (msgList.at(i).at(0) == "img")
		{
			// 获得 图片路径
			// 这里写1，0是img，1是图片的真实内容
			QString imagePath = msgList.at(i).at(1);
			QPixmap pixmap;		// 用于加载图片

			// 获取表情名称的位置
			// 表情路径
			QString strEmotionPath = "qrc:/Resources/MainWindow/emotion/";
			int pos = strEmotionPath.size();			// 表情路径长度
			isImageMsg = true;

			// 获取表情名称
			// 通过mid()方法，截取整个字符串中的，部分字符串
			QString strEmotionName = imagePath.mid(pos);
			// 把【.png】用 【空】替换，直接改变的就是 strEmotionName 本身
			strEmotionName.replace(".png", "");

			// 根据表情名称的长度，进行设置表情数据
			// 不足3位，则不足3位，如23.png，则不足为 023.png
			int emotionNameLength = strEmotionName.length();

			// 判断长度
			if (emotionNameLength == 1)
			{
				strData = strData + "00" + strEmotionName;
			}
			else if (emotionNameLength == 2)
			{
				strData = strData + "0" + strEmotionName;
			}
			else if (emotionNameLength == 3)
			{
				strData = strData + strEmotionName;
			}

			msgType = 0;		// 表情信息
			imageNum++;

			// 判断最左边的 3个字符，是否为 qrc
			if (imagePath.left(3) == "qrc")		// 假设路径为 qrc:/MainWindow/xxx
			{
				// mid() 方法，从中间位置开始截取
				// 从第三个字符开始截取，就是 " : " 冒号开始
				// 去掉表情路径中 qrc
				pixmap.load(imagePath.mid(3));
			}
			else
			{	// 不是 qrc的，就直接加载
				pixmap.load(imagePath);
			}

			// 表情图片html格式，文本组合（路径，宽度，高度）
			QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>")
				.arg(imagePath).arg(pixmap.width()).arg(pixmap.height());

			// 存到 字符串中
			qsMsg += imgPath;
		}
		else if (msgList.at(i).at(0) == "text")
		{
			// 这里写1，0是text，1是文本的真实内容
			qsMsg += msgList.at(i).at(1);
			strData = qsMsg;				// 赋值
		}
	}

	// 插入到 Json 对象中，是键值对，
	// "MSG"是键，qsMsg是值
	// 体现在，资源文件中，以 msgleftTmpl.html 为例
	// 里面的内容中的 【MSG】 <div class="msg">{{MSG}}<span class="trigon">
	msgObj.insert("MSG", qsMsg);

	// 一切的目的，都是为了 转成QString 字符串类型
	// 再转换成 Json 文档，并且 要转成 UTF-8 的文档
	// QJsonDocument::Compact，紧凑的意思
	const QString& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);

	// 发信息
	if (strObj == "0")
	{
		// 属于 Java脚本语言
		this->page()->runJavaScript(QString("appendHtml0(%1)").arg(Msg));

		// 如果发送的是表情，那就对 发送的数据，进行处理
		if (isImageMsg)
		{
			// 当前strData保存的只是表情的名称，占位是3个宽度
			// 这里加上表情的数量
			strData = QString::number(imageNum) + "images" + strData;
		}

		// 发送信号，发送信息
		emit signalSendMsg(strData, msgType);
	}
	else// 来信
	{
		// 追加数据，这里就是 recvHtml
		this->page()->runJavaScript(QString("recvHtml_%1(%2)").arg(strObj).arg(Msg));
	}
}