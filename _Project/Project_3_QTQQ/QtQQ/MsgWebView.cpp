#include "MsgWebView.h" // ���� MsgWebView ���ͷ�ļ�
#include "TalkWindowShell.h"
#include "WindowManager.h"
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

	TalkWindowShell* talkWindowShell = WindowManager::getInstance()->getTalkWindowShell();
	connect(this, &MsgWebView::signalSendMsg,
			talkWindowShell, &TalkWindowShell::updateSendTcpMsg);

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

void MsgWebView::appendMsg(const QString& html, QString strObj = "0")
{
	QJsonObject msgObj;
	QString qsMsg;
	const QList<QStringList> msgList = parseHtml(html); // ���� html

	// ��Ϣ���ͣ�Ĭ��Ϊ1
	// 0��ͼƬ��1���ı���2���ļ�
	int msgType = 1;
	bool isImageMsg = false; // Ĭ��ΪͼƬ��Ϣ
	int imageNum = 0;        // ͼƬ������Ĭ��Ϊ0
	QString strData;         

	for (int i = 0; i < msgList.size(); i++)
	{
		// ����msgList�ĵ�ǰѭ���еĵ�һ��Ԫ��
		// Ϊimg�ļ�
		if (msgList.at(i).at(0) == "img")
		{
			// ��ȡͼƬ·��
			// ��ʽΪ1��ͼƬ·����2��ʵ��ͼƬ��
			QString imagePath = msgList.at(i).at(1);
			QPixmap pixmap;        // ���ڼ���ͼƬ

			// ��ȡ��Դ�ļ�·��
			// ͼƬ·��
			QString strEmotionPath = "qrc:/Resources/MainWindow/emotion/";
			int pos = strEmotionPath.size();            // ·������
			isImageMsg = true;

			// ͨ��mid()������ȡ�ַ����е��Ӵ�����ȡ�ַ���
			QString strEmotionName = imagePath.mid(pos);
			// ȥ�� .png ��׺
			strEmotionName.replace(".png", "");
			// �����ļ������Ƚ��д�������3λ����
			int emotionNameLength = strEmotionName.length();

			// �жϳ���
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

			msgType = 0;        //������Ϣ
			imageNum++;

			// �ж�·����ǰ3���ַ��Ƿ�Ϊ qrc
			if (imagePath.left(3) == "qrc")        // ·��Ϊ qrc:/MainWindow/xxx
			{
				// mid() �������м�λ�ÿ�ʼ��ȡ
				// �Ӹ���λ�ÿ�ʼ��ȡ�ַ�������0��ʼ������ǰ׺ qrc
				pixmap.load(imagePath.mid(3));
			}
			else
			{    // ������� qrc����ֱ�Ӽ���
				pixmap.load(imagePath);
			}

			// ����ͼƬhtml��ʽ���ַ���������·������Ⱥ͸߶�
			QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>")
				.arg(imagePath).arg(pixmap.width()).arg(pixmap.height());

			// ��ӵ���Ϣ�ַ���
			qsMsg += imgPath;
		}
		else if (msgList.at(i).at(0) == "text")
		{
			// Ϊ�ı���Ϣ��ֱ����ӵ��ַ�����
			qsMsg += msgList.at(i).at(1);
			strData = qsMsg;                // ��ֵ
		}
	}


	msgObj.insert("MSG", qsMsg);
	const QString& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);
	
	// ������Ϣ
	if (strObj == "0")
	{
		// ���� Java �ű�����
		this->page()->runJavaScript(QString("appendHtml0(%1)").arg(Msg));

		// �����ͼƬ��Ϣ�����ͼƬ������Ϣ
		if (isImageMsg)
		{
			// ��ǰstrDataΪ�ַ������ݣ�ǰ��λΪͼƬ������ռλ3λ������ΪͼƬ����
			// ��������ͼƬ����
			strData = QString::number(imageNum) + "images" + strData;
		}

		// �����źţ�������Ϣ����Ϣ����
		emit signalSendMsg(strData, msgType);
	}
	else// ����
	{
		// ׷�����ݣ����� recvHtml ����
		this->page()->runJavaScript(QString("recvHtml_%1(%2)").arg(strObj).arg(Msg));
	}
	
}