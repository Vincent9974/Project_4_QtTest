#pragma once

#include <QWebEngineView>
#include <QDomNode>
#include <QURL>


class MsgHtmlObj : public QObject
{
	Q_OBJECT

		// 动态属性 自己发的, 对方发的
		// 这里定义了两个字符串属性，分别用于左右消息框的 HTML 模板
		// m_msgLHtmlTmpl 和 m_msgRHtmlTmpl 分别表示左右两个消息框
		// signalMsgHtml 信号会在属性发生变化时发射出去
	//发来的信息
	Q_PROPERTY(QString msgLHtmlTmpl MEMBER m_msgLHtmlTmpl NOTIFY signalMsgHtml)
	//我发的信息
	Q_PROPERTY(QString msgRHtmlTmpl MEMBER m_msgRHtmlTmpl NOTIFY signalMsgHtml)
		
public:
	MsgHtmlObj(QObject* parent, QString msgLPicPath = ""); //发信息来的人的头像路径

signals:
	void signalMsgHtml(const QString& html);

private:
	void initHtmlTmpl();            // 初始化 HTML 模板

	// 初始化 HTML 页面信息，包括左右消息框的模板内容，根据业务模型需要进行初始化
	// 参数 code 表示消息模板的类型，用于区分不同的初始化
	QString getMsgtmplHtml(const QString& code);

private:
	QString m_msgLpicPath;
	QString m_msgLHtmlTmpl;         // 左侧消息框的 HTML 模板
	QString m_msgRHtmlTmpl;         // 右侧消息框的 HTML 模板
};




// 重写的 Web 页面类，用于接收来自 HTML 页面的导航请求，只接受 qrc 资源的导航请求
class MsgWebPage : public QWebEnginePage
{
	Q_OBJECT

public:
	MsgWebPage(QObject* parent = nullptr) : QWebEnginePage(parent)
	{

	}

protected:
	// 重写导航请求接受函数，只接受 qrc 资源的导航请求
	bool acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame);
};



// 自定义的 Web 视图类，用于显示 Web 页面
class MsgWebView : public QWebEngineView
{
	Q_OBJECT

public:
	MsgWebView(QWidget *parent);
	~MsgWebView();

	// 追加消息到 HTML 字符串
	void appendMsg(const QString& html, QString strObj = "0"); 

private:
	// 解析 HTML 字符串
	QList<QStringList> parseHtml(const QString& html);

	// 解析 DOM 节点
	// QT 提供了 DOM 节点的处理，包括文本和标签，这里通过 QDomNode 表示节点
	QList<QStringList> parseDocNode(const QDomNode& node);


signals:
	void signalSendMsg(QString& strData, int &msgType, QString sFile = "");

private:
	// 网页显示的内容需要一个 HTML 对象来管理
	// QT 的 HTML 展示是基于 Web 的，需要用到 QWeb
	// 作为页面对象
	MsgHtmlObj* m_msgHtmlObj;
	QWebChannel* m_channel;
};

