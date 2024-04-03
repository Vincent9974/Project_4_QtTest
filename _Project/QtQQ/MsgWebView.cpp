#include "MsgWebView.h" // ���� MsgWebView ���ͷ�ļ�
#include <QFile> // �����ļ�������ص�ͷ�ļ�
#include <QMessageBox> // ������Ϣ����ص�ͷ�ļ�
#include <QJsonObject> // ���� JSON ������ص�ͷ�ļ�
#include <QJsonDocument> // ���� JSON �ĵ���ص�ͷ�ļ�
#include <QWebChannel> // ���� Web ͨ����ص�ͷ�ļ�

// MsgHtmlObj ��Ĺ��캯��ʵ��
MsgHtmlObj::MsgHtmlObj(QObject* parent)
	: QObject(parent) // ʹ�ø����ĸ�������г�ʼ��
{
	initHtmlTmpl(); // ��ʼ�� HTML ģ��
}

// ��ʼ�� HTML ģ���˽�г�Ա����ʵ��
void MsgHtmlObj::initHtmlTmpl()
{
	// ��ʼ�������Ҳ���Ϣģ��
	m_msgLHtmlTmpl = getMsgtmplHtml("msgleftTmpl");
	m_msgRHtmlTmpl = getMsgtmplHtml("msgrightTmpl");
}

// MsgWebView ��Ĺ��캯��ʵ��
MsgWebView::MsgWebView(QWidget *parent)
	: QWebEngineView(parent) // ʹ�ø����ĸ�������г�ʼ��
{
	// ����һ���µ� Web ҳ�棬������Ϊ��ǰҳ��
	MsgWebPage* page = new MsgWebPage(this);
	setPage(page);

	// ���� Web ͨ����ע�� MsgHtmlObj ����
	QWebChannel* channel = new QWebChannel(this);
	m_msgHtmlObj = new MsgHtmlObj(this);
	channel->registerObject("external", m_msgHtmlObj);

	// �� Web ͨ������Ϊ��ǰҳ���ͨ��ͨ��
	this->page()->setWebChannel(channel);

	// ������Ϣģ�� HTML ҳ��
	this->load(QUrl("qrc:/Resources/MainWindow/MsgHtml/msgTmpl.html"));
}

// MsgWebView �����������ʵ��
MsgWebView::~MsgWebView()
{
}

// ��ȡ��Ϣģ�� HTML ���ݵ�˽�г�Ա����ʵ��
QString MsgHtmlObj::getMsgtmplHtml(const QString& code)
{
	// �����ļ�·��
	QFile file(":/Resources/MainWindow/MsgHtml/" + code + ".html");

	// ���ļ�
	file.open(QFile::ReadOnly);
	QString strData;

	if (file.isOpen()) // ����ļ��ɹ���
	{
		strData = QLatin1String(file.readAll()); // ��ȡ�ļ����ݲ�ת��Ϊ�ַ���
	}
	else // ����ļ���ʧ��
	{
		// ��ʾ��Ϣ����ʾʧ����Ϣ
		QMessageBox::information(nullptr, "Tips", "Failed to init html!");
		return QString(""); // ���ؿ��ַ���
	}

	file.close(); // �ر��ļ�

	return strData; // �����ļ������ַ���
}

// ���ܵ�������ĺ���ʵ��
bool MsgWebPage::acceptNavigationRequest(const QUrl& url, NavigationType type, bool isMainFrame)
{
	// �ж� URL �Ƿ�Ϊ qrc ��ʽ
	if (url.scheme() == QString("qrc"))
	{
		return true; // ����� qrc ��ʽ����������
	}
	else
	{
		return false; // ����������
	}
}

// ���� HTML �ַ�����˽�г�Ա����ʵ��
QList<QStringList> MsgWebView::parseHtml(const QString& html)
{
	QDomDocument doc;
	doc.setContent(html); // ���� HTML �ַ���Ϊ QDomDocument ����


	// ��ȡ body ��ǩ�µ������ӽڵ�
	const QDomElement& root = doc.documentElement();
	const QDomNode& node = root.firstChildElement("body");

	// �����ڵ㲢���ؽ������
	return parseDocNode(node);
}

// �����ڵ��˽�г�Ա����ʵ��
QList<QStringList> MsgWebView::parseDocNode(const QDomNode& node)
{
	QList<QStringList> attribute;
	const QDomNodeList& list = node.childNodes(); // ��ȡ�ӽڵ��б�


	// �����ӽڵ��б�
	for (int i = 0; i < list.count(); i++)
	{
		const QDomNode& node = list.at(i);

		if (node.isElement()) // �����Ԫ�ؽڵ�
		{
			const QDomElement& element = node.toElement(); // ת��ΪԪ�ؽڵ�

			if (element.tagName() == "img") // ����� img ��ǩ
			{
				QStringList attributeList;
				attributeList << "img" << element.attribute("src"); // ��ȡͼƬ·������ӵ������б���
				attribute << attributeList; // ��������б�����б���
			}


			if (element.tagName() == "span") // ����� span ��ǩ
			{
				QStringList attributeList;
				attributeList << "text" << element.text(); // ��ȡ�ı����ݲ���ӵ������б���
				attribute << attributeList; // ��������б�����б���
			}

			if (node.hasChildNodes()) // ����ڵ㻹���ӽڵ�
			{
				attribute << parseDocNode(node); // �ݹ�����ӽڵ㲢��ӵ�����б���
			}
		}
	}

	return attribute; // ���ؽ�������б�
}

// �����Ϣ�� WebView �ĳ�Ա����ʵ��
void MsgWebView::appendMsg(const QString& html)
{
	QJsonObject msgObj;
	QString qsMsg;
	const QList<QStringList> msgList = parseHtml(html); // ���� HTML �ַ���


	// ������Ϣ�б�
	for (int i = 0; i < msgList.size(); i++)
	{
		// �ж���Ϣ����
		if (msgList.at(i).at(0) == "img") // �����ͼƬ��Ϣ
		{
			// ��ȡͼƬ·��
			QString imagePath = msgList.at(i).at(1);
			QPixmap pixmap; // ���� QPixmap ����

			// �ж�ͼƬ·���Ƿ�Ϊ qrc ��ʽ
			if (imagePath.left(3) == "qrc")
			{
				pixmap.load(imagePath.mid(3)); // ����� qrc ��ʽ�������ͼƬ
			}
			else
			{
				pixmap.load(imagePath); // ����ֱ�Ӽ���ͼƬ
			}

			// ����ͼƬ HTML ��ǩ����ӵ���Ϣ�ַ�����
			QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>")
				.arg(imagePath).arg(pixmap.width()).arg(pixmap.height());
			qsMsg += imgPath;
		}
		else if (msgList.at(i).at(0) == "text") // ������ı���Ϣ
		{
			qsMsg += msgList.at(i).at(1); // ֱ������ı�����Ϣ�ַ�����
		}
	}

	// ���� JSON ���󣬲�������Ϣ����
	msgObj.insert("MSG", qsMsg);

	// �� JSON ����ת��Ϊ�ַ���
	const QString& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);

	// �ڵ�ǰҳ����ִ�� JavaScript������Ϣ����׷�ӵ�ҳ����
	this->page()->runJavaScript(QString("appendHtml(%1)").arg(Msg));
}