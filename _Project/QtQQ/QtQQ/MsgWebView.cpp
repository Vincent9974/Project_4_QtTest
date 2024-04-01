#include "MsgWebView.h" // 包含 MsgWebView 类的头文件
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

// 添加消息到 WebView 的成员函数实现
void MsgWebView::appendMsg(const QString& html)
{
	QJsonObject msgObj;
	QString qsMsg;
	const QList<QStringList> msgList = parseHtml(html); // 解析 HTML 字符串


	// 遍历消息列表
	for (int i = 0; i < msgList.size(); i++)
	{
		// 判断消息类型
		if (msgList.at(i).at(0) == "img") // 如果是图片消息
		{
			// 获取图片路径
			QString imagePath = msgList.at(i).at(1);
			QPixmap pixmap; // 创建 QPixmap 对象

			// 判断图片路径是否为 qrc 格式
			if (imagePath.left(3) == "qrc")
			{
				pixmap.load(imagePath.mid(3)); // 如果是 qrc 格式，则加载图片
			}
			else
			{
				pixmap.load(imagePath); // 否则直接加载图片
			}

			// 构造图片 HTML 标签并添加到消息字符串中
			QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>")
				.arg(imagePath).arg(pixmap.width()).arg(pixmap.height());
			qsMsg += imgPath;
		}
		else if (msgList.at(i).at(0) == "text") // 如果是文本消息
		{
			qsMsg += msgList.at(i).at(1); // 直接添加文本到消息字符串中
		}
	}

	// 构造 JSON 对象，并插入消息内容
	msgObj.insert("MSG", qsMsg);

	// 将 JSON 对象转换为字符串
	const QString& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);

	// 在当前页面中执行 JavaScript，将消息内容追加到页面中
	this->page()->runJavaScript(QString("appendHtml(%1)").arg(Msg));
}