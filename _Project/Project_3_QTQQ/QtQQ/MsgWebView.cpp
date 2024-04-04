#include "MsgWebView.h" // 包含 MsgWebView 类的头文件
#include "TalkWindowShell.h"
#include "WindowManager.h"
#include <QFile> // 包含文件操作相关的头文件
#include <QMessageBox> // 包含消息框相关的头文件
#include <QJsonObject> // 包含 JSON 对象相关的头文件
#include <QJsonDocument> // 包含 JSON 文档相关的头文件
#include <QWebChannel> // 包含 Web 通道相关的头文件

// MsgHtmlObj 类的构造函数实现
MsgHtmlObj::MsgHtmlObj(QObject* parent)
	: QObject(parent) // 使用给定的父对象进行初始化
{
	initHtmlTmpl(); // 初始化 HTML 模板
}

// 初始化 HTML 模板的私有成员函数实现
void MsgHtmlObj::initHtmlTmpl()
{
	// 初始化左侧和右侧消息模板
	m_msgLHtmlTmpl = getMsgtmplHtml("msgleftTmpl");
	m_msgRHtmlTmpl = getMsgtmplHtml("msgrightTmpl");
}

// MsgWebView 类的构造函数实现
MsgWebView::MsgWebView(QWidget *parent)
	: QWebEngineView(parent) // 使用给定的父对象进行初始化
{
	// 创建一个新的 Web 页面，并设置为当前页面
	MsgWebPage* page = new MsgWebPage(this);
	setPage(page);

	// 创建 Web 通道并注册 MsgHtmlObj 对象
	QWebChannel* channel = new QWebChannel(this);
	m_msgHtmlObj = new MsgHtmlObj(this);
	channel->registerObject("external", m_msgHtmlObj);

	// 将 Web 通道设置为当前页面的通信通道
	this->page()->setWebChannel(channel);

	TalkWindowShell* talkWindowShell = WindowManager::getInstance()->getTalkWindowShell();
	connect(this, &MsgWebView::signalSendMsg,
			talkWindowShell, &TalkWindowShell::updateSendTcpMsg);

	// 加载消息模板 HTML 页面
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

void MsgWebView::appendMsg(const QString& html, QString strObj = "0")
{
	QJsonObject msgObj;
	QString qsMsg;
	const QList<QStringList> msgList = parseHtml(html); // 解析 html

	// 消息类型，默认为1
	// 0是图片，1是文本，2是文件
	int msgType = 1;
	bool isImageMsg = false; // 默认为图片消息
	int imageNum = 0;        // 图片数量，默认为0
	QString strData;         

	for (int i = 0; i < msgList.size(); i++)
	{
		// 遍历msgList的当前循环中的第一个元素
		// 为img文件
		if (msgList.at(i).at(0) == "img")
		{
			// 获取图片路径
			// 格式为1是图片路径，2是实际图片名
			QString imagePath = msgList.at(i).at(1);
			QPixmap pixmap;        // 用于加载图片

			// 获取资源文件路径
			// 图片路径
			QString strEmotionPath = "qrc:/Resources/MainWindow/emotion/";
			int pos = strEmotionPath.size();            // 路径长度
			isImageMsg = true;

			// 通过mid()方法获取字符串中的子串，截取字符串
			QString strEmotionName = imagePath.mid(pos);
			// 去除 .png 后缀
			strEmotionName.replace(".png", "");
			// 根据文件名长度进行处理，不足3位则补足
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

			msgType = 0;        //表情信息
			imageNum++;

			// 判断路径的前3个字符是否为 qrc
			if (imagePath.left(3) == "qrc")        // 路径为 qrc:/MainWindow/xxx
			{
				// mid() 方法从中间位置开始获取
				// 从给定位置开始获取字符串，从0开始，忽略前缀 qrc
				pixmap.load(imagePath.mid(3));
			}
			else
			{    // 如果不是 qrc，则直接加载
				pixmap.load(imagePath);
			}

			// 构造图片html格式的字符串，包含路径，宽度和高度
			QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>")
				.arg(imagePath).arg(pixmap.width()).arg(pixmap.height());

			// 添加到消息字符串
			qsMsg += imgPath;
		}
		else if (msgList.at(i).at(0) == "text")
		{
			// 为文本消息，直接添加到字符串中
			qsMsg += msgList.at(i).at(1);
			strData = qsMsg;                // 赋值
		}
	}


	msgObj.insert("MSG", qsMsg);
	const QString& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);
	
	// 发送消息
	if (strObj == "0")
	{
		// 调用 Java 脚本方法
		this->page()->runJavaScript(QString("appendHtml0(%1)").arg(Msg));

		// 如果是图片消息，添加图片数量信息
		if (isImageMsg)
		{
			// 当前strData为字符串数据，前三位为图片数量，占位3位，后续为图片名称
			// 在左侧添加图片数量
			strData = QString::number(imageNum) + "images" + strData;
		}

		// 发送信号，发送消息和消息类型
		emit signalSendMsg(strData, msgType);
	}
	else// 接收
	{
		// 追加数据，调用 recvHtml 方法
		this->page()->runJavaScript(QString("recvHtml_%1(%2)").arg(strObj).arg(Msg));
	}
	
}