#pragma once

#include <QWebEngineView>
#include <QDomNode>
#include <QURL>


class MsgHtmlObj : public QObject
{
	Q_OBJECT

		// ��̬���� �Լ�����, �Է�����
		// ���ﶨ���������ַ������ԣ��ֱ�����������Ϣ��� HTML ģ��
		// m_msgLHtmlTmpl �� m_msgRHtmlTmpl �ֱ��ʾ����������Ϣ��
		// signalMsgHtml �źŻ������Է����仯ʱ�����ȥ
	//��������Ϣ
	Q_PROPERTY(QString msgLHtmlTmpl MEMBER m_msgLHtmlTmpl NOTIFY signalMsgHtml)
	//�ҷ�����Ϣ
	Q_PROPERTY(QString msgRHtmlTmpl MEMBER m_msgRHtmlTmpl NOTIFY signalMsgHtml)
		
public:
	MsgHtmlObj(QObject* parent, QString msgLPicPath = ""); //����Ϣ�����˵�ͷ��·��

signals:
	void signalMsgHtml(const QString& html);

private:
	void initHtmlTmpl();            // ��ʼ�� HTML ģ��

	// ��ʼ�� HTML ҳ����Ϣ������������Ϣ���ģ�����ݣ�����ҵ��ģ����Ҫ���г�ʼ��
	// ���� code ��ʾ��Ϣģ������ͣ��������ֲ�ͬ�ĳ�ʼ��
	QString getMsgtmplHtml(const QString& code);

private:
	QString m_msgLpicPath;
	QString m_msgLHtmlTmpl;         // �����Ϣ��� HTML ģ��
	QString m_msgRHtmlTmpl;         // �Ҳ���Ϣ��� HTML ģ��
};




// ��д�� Web ҳ���࣬���ڽ������� HTML ҳ��ĵ�������ֻ���� qrc ��Դ�ĵ�������
class MsgWebPage : public QWebEnginePage
{
	Q_OBJECT

public:
	MsgWebPage(QObject* parent = nullptr) : QWebEnginePage(parent)
	{

	}

protected:
	// ��д����������ܺ�����ֻ���� qrc ��Դ�ĵ�������
	bool acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame);
};



// �Զ���� Web ��ͼ�࣬������ʾ Web ҳ��
class MsgWebView : public QWebEngineView
{
	Q_OBJECT

public:
	MsgWebView(QWidget *parent);
	~MsgWebView();

	// ׷����Ϣ�� HTML �ַ���
	void appendMsg(const QString& html, QString strObj = "0"); 

private:
	// ���� HTML �ַ���
	QList<QStringList> parseHtml(const QString& html);

	// ���� DOM �ڵ�
	// QT �ṩ�� DOM �ڵ�Ĵ��������ı��ͱ�ǩ������ͨ�� QDomNode ��ʾ�ڵ�
	QList<QStringList> parseDocNode(const QDomNode& node);


signals:
	void signalSendMsg(QString& strData, int &msgType, QString sFile = "");

private:
	// ��ҳ��ʾ��������Ҫһ�� HTML ����������
	// QT �� HTML չʾ�ǻ��� Web �ģ���Ҫ�õ� QWeb
	// ��Ϊҳ�����
	MsgHtmlObj* m_msgHtmlObj;
	QWebChannel* m_channel;
};

