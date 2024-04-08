#include "MsgWebView.h" // ���� MsgWebView ���ͷ�ļ�
#include "TalkWindowShell.h"
#include "WindowManager.h"
#include <QFile> // �����ļ�������ص�ͷ�ļ�
#include <QMessageBox> // ������Ϣ����ص�ͷ�ļ�
#include <QJsonObject> // ���� JSON ������ص�ͷ�ļ�
#include <QJsonDocument> // ���� JSON �ĵ���ص�ͷ�ļ�
#include <QWebChannel> // ���� Web ͨ����ص�ͷ�ļ�
#include <QSqlQueryModel>

extern QString gstrLoginHeadPath;

// MsgHtmlObj ��Ĺ��캯��ʵ��
MsgHtmlObj::MsgHtmlObj(QObject* parent, QString msgLPicPath)
	: QObject(parent) // ʹ�ø����ĸ�������г�ʼ��
{
	m_msgLpicPath = msgLPicPath;
	initHtmlTmpl(); // ��ʼ�� HTML ģ��
}

// ��ʼ�� HTML ģ���˽�г�Ա����ʵ��
void MsgHtmlObj::initHtmlTmpl()
{
	// ��ʼ�� ���
	// ��msgleftTmpl�еġ�%1�����滻�� �Է�ͷ��·��
	m_msgLHtmlTmpl = getMsgtmplHtml("msgleftTmpl");
	m_msgLHtmlTmpl.replace("%1", m_msgLpicPath);

	// ��ʼ�� �Ҳ�
	// ��msgrightTmpl�еġ�%1�����滻�� �Է�ͷ��·��
	// gstrLoginHeadPath �� CCMainWindow ��һ��ȫ�ֱ���
	m_msgRHtmlTmpl = getMsgtmplHtml("msgrightTmpl");
	m_msgRHtmlTmpl.replace("%1", gstrLoginHeadPath);
}

// QWebEngineView ��ͼ������ ��ʾ��ҳ����
MsgWebView::MsgWebView(QWidget *parent)
	: QWebEngineView(parent)
	, m_channel(new QWebChannel(this))
{
	// ����һ����ҳ���� ����Ϊ ��ǰ����ҳ
	MsgWebPage* page = new MsgWebPage(this);
	setPage(page);

	// ͨ��
	// QWebChannel* channel = new QWebChannel(this);		// ����Ҫ�� ע�͵�
	m_msgHtmlObj = new MsgHtmlObj(this);

	// ע��
	// "external0" �����Լ�������Ϣ�������ҳ����
	m_channel->registerObject("external0", m_msgHtmlObj);

	TalkWindowShell* talkWindowShell = WindowManager::getInstance()->getTalkWindowShell();
	connect(this, &MsgWebView::signalSendMsg, talkWindowShell, &TalkWindowShell::updateSendTcpMsg);

	/*
		���ݵ�ǰ�򿪵����촰�ڣ�
		�ڹ������촰�ڵ�ʱ�򣬲Żṹ�� MsgWebView ��ҳ��ͼ�����
		����Ҫ����ǰ��������ĸ����촰�ڣ�
		�����ǰ���з�������෢��Ϣ�Ķ���ֻ�����з�����ȺԱ

		����ǹ�˾Ⱥ���Ǿ�Ҫ����˾Ⱥ�������ù���������QQ�� ע�����
	*/
	// �Ȼ�ȡ������촰�ڵ�ID
	// ��ҳ��ͼ �ڹ����ʱ��Ҳ���� ���촰�� ���ڹ��� ʱ��
	// ��ǰ�����������촰�ڵ�ID��QQ�ţ�
	QString strTalkID = WindowManager::getInstance()->getCreatingTalkID();

	// ���������ҳ������Ҫ���� ID������
	// 2�������Ⱥ�ģ����ġ���˾ȺQQ�� 2000�������������
	// ��ȡ ��˾ȺQQ�ţ�Ȼ�����Ա�
	QSqlQueryModel queryEmployeeModel;
	QString strEmployeeID, strPicturePath;
	QString strExternal;
	bool isGroupTalk = false;		// Ⱥ�ı�־����ʼΪ false

	queryEmployeeModel.setQuery(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'")
		.arg(QStringLiteral("��˾Ⱥ")));
	// ��ȡ����
	QModelIndex companyIndex = queryEmployeeModel.index(0, 0);
	// ͨ��������ȡ ��˾Ⱥ��ID
	QString strCompanyID = queryEmployeeModel.data(companyIndex).toString();
	// �жϣ���ǰ����ID���ǲ��ǹ�˾Ⱥ
	if (strTalkID == strCompanyID)
	{
		isGroupTalk = true;
		// ����ǹ�˾Ⱥ���ڣ��ͽ����ݿ����
		// ������״̬Ϊ1��û��ע���ġ�Ա��ID��ͷ�񡿣�ȫ��ȡ����
		queryEmployeeModel.setQuery("SELECT employeeID,picture FROM tab_employees WHERE status = 1");
	}
	else
	{
		// ���ǹ�˾Ⱥ�Ĵ���
		// �ж�QQ�ſ�ȣ�Ⱥ����2001����ռ4λ��ȣ�������10001����ռ5λ
		if (strTalkID.length() == 4)	// ����Ⱥ��
		{
			isGroupTalk = true;
			// ��ȡ ĳ��Ⱥ������� ȺԱQQ��
			queryEmployeeModel.setQuery(QString("SELECT employeeID,picture FROM tab_employees WHERE status = 1 AND departmentID = %1")
				.arg(strTalkID));

		}
		else  // ����
		{
			// ��ȡ �Է�QQ��
			queryEmployeeModel.setQuery(QString("SELECT picture FROM tab_employees WHERE status = 1 AND employeeID = %1")
				.arg(strTalkID));
			// ͨ���������ҳ�ͼƬ·������ת�� �ַ���
			QModelIndex index = queryEmployeeModel.index(0, 0);
			strPicturePath = queryEmployeeModel.data(index).toString();

			strExternal = "external_" + strTalkID;

			// ������ҳ����
			MsgHtmlObj* msgHtmlObj = new MsgHtmlObj(this, strPicturePath);
			m_channel->registerObject(strExternal, msgHtmlObj);		// ע��
		}
	}

	// ����Ⱥ�Ĵ���
	if (isGroupTalk)
	{
		QModelIndex employeeModelIndex, pictureModelIndex;
		// ģ��������
		int rows = queryEmployeeModel.rowCount();
		// ����Ⱥ��
		for (int i = 0; i < rows; i++)
		{
			// ��ȡ����
			employeeModelIndex = queryEmployeeModel.index(i, 0);	// Ⱥ��ԱQQ��/ID������
			pictureModelIndex = queryEmployeeModel.index(i, 1);		// Ⱥ��Աͷ��·��������

			// ��ȡȺ��ԱQQ�ţ�ID
			strEmployeeID = queryEmployeeModel.data(employeeModelIndex).toString();
			// ��ȡȺ��Ա ͷ��·��
			strPicturePath = queryEmployeeModel.data(pictureModelIndex).toString();

			strExternal = "external_" + strEmployeeID;

			MsgHtmlObj* msgHtmlObj = new MsgHtmlObj(this, strPicturePath);
			m_channel->registerObject(strExternal, msgHtmlObj);
		}

	}


	// ���õ�ǰ��ҳ������ͨ��
	this->page()->setWebChannel(m_channel);

	// ������ҳ�����г�ʼ��
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

void MsgWebView::appendMsg(const QString& html, QString strObj)
{
	QJsonObject msgObj;
	QString qsMsg;
	const QList<QStringList> msgList = parseHtml(html);		// ���� html

	// ��Ϣ���ͣ�Ĭ�ϸ�1
	// 0�Ǳ��飬1���ı���2���ļ�
	int msgType = 1;
	bool isImageMsg = false;	// Ĭ�ϵ�ͼƬ��Ϣ
	int imageNum = 0;			// ����������Ĭ�ϸ�0
	QString strData;			// 055��008���������ƣ���Ȳ�����0��ȫ


	for (int i = 0; i < msgList.size(); i++)
	{
		// ��� msgList��ǰѭ���ģ������ ��һ��Ԫ��
		// �� img �ļ�
		if (msgList.at(i).at(0) == "img")
		{
			// ��� ͼƬ·��
			// ����д1��0��img��1��ͼƬ����ʵ����
			QString imagePath = msgList.at(i).at(1);
			QPixmap pixmap;		// ���ڼ���ͼƬ

			// ��ȡ�������Ƶ�λ��
			// ����·��
			QString strEmotionPath = "qrc:/Resources/MainWindow/emotion/";
			int pos = strEmotionPath.size();			// ����·������
			isImageMsg = true;

			// ��ȡ��������
			// ͨ��mid()��������ȡ�����ַ����еģ������ַ���
			QString strEmotionName = imagePath.mid(pos);
			// �ѡ�.png���� ���ա��滻��ֱ�Ӹı�ľ��� strEmotionName ����
			strEmotionName.replace(".png", "");

			// ���ݱ������Ƶĳ��ȣ��������ñ�������
			// ����3λ������3λ����23.png������Ϊ 023.png
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

			msgType = 0;		// ������Ϣ
			imageNum++;

			// �ж�����ߵ� 3���ַ����Ƿ�Ϊ qrc
			if (imagePath.left(3) == "qrc")		// ����·��Ϊ qrc:/MainWindow/xxx
			{
				// mid() ���������м�λ�ÿ�ʼ��ȡ
				// �ӵ������ַ���ʼ��ȡ������ " : " ð�ſ�ʼ
				// ȥ������·���� qrc
				pixmap.load(imagePath.mid(3));
			}
			else
			{	// ���� qrc�ģ���ֱ�Ӽ���
				pixmap.load(imagePath);
			}

			// ����ͼƬhtml��ʽ���ı���ϣ�·������ȣ��߶ȣ�
			QString imgPath = QString("<img src=\"%1\" width=\"%2\" height=\"%3\"/>")
				.arg(imagePath).arg(pixmap.width()).arg(pixmap.height());

			// �浽 �ַ�����
			qsMsg += imgPath;
		}
		else if (msgList.at(i).at(0) == "text")
		{
			// ����д1��0��text��1���ı�����ʵ����
			qsMsg += msgList.at(i).at(1);
			strData = qsMsg;				// ��ֵ
		}
	}

	// ���뵽 Json �����У��Ǽ�ֵ�ԣ�
	// "MSG"�Ǽ���qsMsg��ֵ
	// �����ڣ���Դ�ļ��У��� msgleftTmpl.html Ϊ��
	// ����������е� ��MSG�� <div class="msg">{{MSG}}<span class="trigon">
	msgObj.insert("MSG", qsMsg);

	// һ�е�Ŀ�ģ�����Ϊ�� ת��QString �ַ�������
	// ��ת���� Json �ĵ������� Ҫת�� UTF-8 ���ĵ�
	// QJsonDocument::Compact�����յ���˼
	const QString& Msg = QJsonDocument(msgObj).toJson(QJsonDocument::Compact);

	// ����Ϣ
	if (strObj == "0")
	{
		// ���� Java�ű�����
		this->page()->runJavaScript(QString("appendHtml0(%1)").arg(Msg));

		// ������͵��Ǳ��飬�ǾͶ� ���͵����ݣ����д���
		if (isImageMsg)
		{
			// ��ǰstrData�����ֻ�Ǳ�������ƣ�ռλ��3�����
			// ������ϱ��������
			strData = QString::number(imageNum) + "images" + strData;
		}

		// �����źţ�������Ϣ
		emit signalSendMsg(strData, msgType);
	}
	else// ����
	{
		// ׷�����ݣ�������� recvHtml
		this->page()->runJavaScript(QString("recvHtml_%1(%2)").arg(strObj).arg(Msg));
	}
}