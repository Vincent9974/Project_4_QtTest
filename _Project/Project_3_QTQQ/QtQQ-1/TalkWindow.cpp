#include "TalkWindow.h"
#include "ContactItem.h"
#include "CommonUtils.h"
#include "WindowManager.h"
#include "RootConcatItem.h"
#include "SendFile.h"

#include <QToolTip>
#include <QFile>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>

extern QString gLoginEmployeeID;

TalkWindow::TalkWindow(QWidget* parent, const QString& uid/*, GroupType groupType*/)
	: QWidget(parent),
	m_talkId(uid)
	//m_groupType(groupType)
{
	ui.setupUi(this);

	// ������������ʵ������������Ա��ڴ��ڹر�ʱɾ���������ֵ�ӳ��
	WindowManager::getInstance()->addWindowName(m_talkId, this);
	setAttribute(Qt::WA_DeleteOnClose); // �ڴ��ڹر�ʱ�Զ�ɾ������
	initGroupTalkStatus();
	initControl();
}

TalkWindow::~TalkWindow()
{
	// ���ڹر�ʱɾ���������ֵ�ӳ��
	WindowManager::getInstance()->deleteWindowName(m_talkId);
}

void TalkWindow::addEmotionImage(int emotionNum)
{
	ui.textEdit->setFocus();
	ui.textEdit->addEmotionUrl(emotionNum);
}

void TalkWindow::setWindowName(const QString & name)
{
	ui.nameLabel->setText(name);
}

QString TalkWindow::getTalkID()
{
	return m_talkId;
}

void TalkWindow::initControl()
{
	// �����Ҳര�ڴ�С
	QList<int> rightWidgetSize;
	rightWidgetSize << 600 << 138;
	ui.bodySplitter->setSizes(rightWidgetSize);

	ui.textEdit->setFontPointSize(10);
	ui.textEdit->setFocus(); // ��ȡ���㣬�򿪴���ʱֱ�����룬����Ҫ�ٵ��������ȡ����


	// ��С�����رհ�ť���ӵ������ڵĲۺ���
	connect(ui.sysmin, SIGNAL(clicked(bool)), parent(), SLOT(onShowMin(bool)));
	connect(ui.sysclose, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));
	connect(ui.closeBtn, SIGNAL(clicked(bool)), parent(), SLOT(onShowClose(bool)));

	// ���鰴ť���ӵ������ڵĲۺ���
	connect(ui.faceBtn, SIGNAL(clicked(bool)), parent(), SLOT(onEmotionBtnClicked(bool)));

	// ���Ͱ�ť���ӵ���ǰ���ڵĲۺ���
	connect(ui.sendBtn, SIGNAL(clicked(bool)), this, SLOT(onSendBtnClicked(bool)));

	// ˫�����οؼ������ӵ���ǰ���ڵĲۺ���
	connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem*, int)));


	connect(ui.fileopenBtn, SIGNAL(clicked(bool)), this, SLOT(onFileOpenBtnClicked(bool)));
	
	if (m_isGroupTalk)
	{
		initTalkWindow();
	}
	else
	{
		initPtoPTalk();
	}

	
	/*// ����Ⱥ�����ͳ�ʼ���Ի�����
	switch (m_groupType)
	{
	case COMPANY:
		initCompanyTalk(); // ��ʼ����˾Ⱥ�Ի�
		break;
	case PERSONELGROUP:
		initPersonelTalk(); // ��ʼ�����²��Ի�
		break;
	case DEVELOPMENTGROUP:
		initDevelopmentTalk(); // ��ʼ���з����Ի�
		break;
	case MARKETGROUP:
		initMarketTalk(); // ��ʼ���г����Ի�
		break;
	default:
		initPtoPTalk(); // Ĭ��Ϊ���˶Ի�
		break;
	}
	*/
}

void TalkWindow::initGroupTalkStatus()
{
	QSqlQueryModel sqlDepModel;
	QString strSql = QString("SELECT * FROM tab_department WHERE departmentID = %1").arg(m_talkId);
	// ִ�� SQL ��ѯ
	sqlDepModel.setQuery(strSql);

	// ��ȡ��ѯ������������ж��Ƿ�Ϊ0�����Ϊ0���ʾ����Ⱥ�ģ������ʾ��Ⱥ��
	int rows = sqlDepModel.rowCount();


	// �����жϽ�����ó�Ա���� m_isGroupTalk ��ֵ���Ա�ʶ��ǰ�����Ƿ�ΪȺ�Ĵ���
	if (rows == 0)
	{
		m_isGroupTalk = false;
	}
	else
	{
		m_isGroupTalk = true;
	}
}

int TalkWindow::getCompDepID()
{
	// ����һ�� SQL ��ѯ�������ڲ�ѯָ���������ƶ�Ӧ�Ĳ���ID
	QSqlQuery queryDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'")
		.arg(QString::fromLocal8Bit("��˾Ⱥ")));

	queryDepID.exec();
	queryDepID.next();

	// ���ز�ѯ������ĵ�һ��ֵ��������ID
	return queryDepID.value(0).toInt();
}






//void TalkWindow::initCompanyTalk()
//{
//	// �������ڵ�
//	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
//
//	// �����ӽڵ�ָʾ������ʾ���ԣ�ָʾ����ʾ�Ƿ����ӽڵ�
//	// ָʾ������ʾ���������֣���ָʾ��Ϊ��ʱ����ʾ�ڵ�û���ӽڵ㣬��ָʾ��Ϊ��ͷʱ����ʾ�ڵ����ӽڵ㣬��ָʾ��Ϊ�Ӻ�ʱ����ʾ�ڵ����ӽڵ㵫δչ��
//	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
//
//	// ��ʼ���ڵ�����
//	pRootItem->setData(0, Qt::UserRole, 0);  // ���ýڵ���û���ɫΪ0
//
//		// �������ڵ�Ŀؼ�
//	// ��һ��������ʾ�Ƿ���Ҫ��ͷ��Ĭ��Ϊfalse
//	// �ڶ���������ʾ������ָ��
//	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);
//
//	ui.treeWidget->setFixedHeight(646);  // shell�߶� - shellͷ��(talkwindow)
//
//	int nEmployeeNum = 50;  // ������50��Ա��
//	QString qsGroupName = QString::fromLocal8Bit("��˾Ⱥ %1/%2").arg(0).arg(nEmployeeNum);  // ������ʾ��Ⱥ������
//	pItemName->setText(qsGroupName);  // ������ʾ��Ⱥ������
//
//	// ��Ӹ��ڵ㵽���οؼ�
//	ui.treeWidget->addTopLevelItem(pRootItem);
//	// ���ø��ڵ�Ŀؼ�����һ������Ϊ���ڵ�ָ�룬�ڶ�������Ϊ������������������Ϊ�ؼ�ָ��
//	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);
//
//	// չ�����ڵ�
//	pRootItem->setExpanded(true);
//
//	// ���Ⱥ���Ա��Ϣ
//	for (int i = 0; i < nEmployeeNum; i++)
//	{
//		addPeopInfo(pRootItem);
//	}
//
//}
//
//void TalkWindow::initPersonelTalk()
//{
//	// �������ڵ�
//	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
//
//	// �����ӽڵ�ָʾ������ʾ���ԣ�ָʾ����ʾ�Ƿ����ӽڵ�
//	// ָʾ������ʾ���������֣���ָʾ��Ϊ��ʱ����ʾ�ڵ�û���ӽڵ㣬��ָʾ��Ϊ��ͷʱ����ʾ�ڵ����ӽڵ㣬��ָʾ��Ϊ�Ӻ�ʱ����ʾ�ڵ����ӽڵ㵫δչ��
//	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
//
//	// ��ʼ���ڵ�����
//	pRootItem->setData(0, Qt::UserRole, 0);  // ���ýڵ���û���ɫΪ0
//
//		// �������ڵ�Ŀؼ�
//	// ��һ��������ʾ�Ƿ���Ҫ��ͷ��Ĭ��Ϊfalse
//	// �ڶ���������ʾ������ָ��
//	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);
//
//	ui.treeWidget->setFixedHeight(646);  // shell�߶� - shellͷ��(talkwindow)
//
//	int nEmployeeNum = 5;  // ������50��Ա��
//	QString qsGroupName = QString::fromLocal8Bit("���²� %1/%2").arg(0).arg(nEmployeeNum);  // ������ʾ��Ⱥ������
//	pItemName->setText(qsGroupName);  // ������ʾ��Ⱥ������
//
//	// ��Ӹ��ڵ㵽���οؼ�
//	ui.treeWidget->addTopLevelItem(pRootItem);
//	// ���ø��ڵ�Ŀؼ�����һ������Ϊ���ڵ�ָ�룬�ڶ�������Ϊ������������������Ϊ�ؼ�ָ��
//	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);
//
//	// չ�����ڵ�
//	pRootItem->setExpanded(true);
//
//	// ���Ⱥ���Ա��Ϣ
//	for (int i = 0; i < nEmployeeNum; i++)
//	{
//		addPeopInfo(pRootItem);
//	}
//}
//
//void TalkWindow::initDevelopmentTalk()
//{
//	// �������ڵ�
//	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
//
//	// �����ӽڵ�ָʾ������ʾ���ԣ�ָʾ����ʾ�Ƿ����ӽڵ�
//	// ָʾ������ʾ���������֣���ָʾ��Ϊ��ʱ����ʾ�ڵ�û���ӽڵ㣬��ָʾ��Ϊ��ͷʱ����ʾ�ڵ����ӽڵ㣬��ָʾ��Ϊ�Ӻ�ʱ����ʾ�ڵ����ӽڵ㵫δչ��
//	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
//
//	// ��ʼ���ڵ�����
//	pRootItem->setData(0, Qt::UserRole, 0);  // ���ýڵ���û���ɫΪ0
//
//		// �������ڵ�Ŀؼ�
//	// ��һ��������ʾ�Ƿ���Ҫ��ͷ��Ĭ��Ϊfalse
//	// �ڶ���������ʾ������ָ��
//	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);
//
//	ui.treeWidget->setFixedHeight(646);  // shell�߶� - shellͷ��(talkwindow)
//
//	int nEmployeeNum = 32;  // ������50��Ա��
//	QString qsGroupName = QString::fromLocal8Bit("�з��� %1/%2").arg(0).arg(nEmployeeNum);  // ������ʾ��Ⱥ������
//	pItemName->setText(qsGroupName);  // ������ʾ��Ⱥ������
//
//	// ��Ӹ��ڵ㵽���οؼ�
//	ui.treeWidget->addTopLevelItem(pRootItem);
//	// ���ø��ڵ�Ŀؼ�����һ������Ϊ���ڵ�ָ�룬�ڶ�������Ϊ������������������Ϊ�ؼ�ָ��
//	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);
//
//	// չ�����ڵ�
//	pRootItem->setExpanded(true);
//
//	// ���Ⱥ���Ա��Ϣ
//	for (int i = 0; i < nEmployeeNum; i++)
//	{
//		addPeopInfo(pRootItem);
//	}
//}
//
//void TalkWindow::initMarketTalk()
//{
//	// �������ڵ�
//	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();
//
//	// �����ӽڵ�ָʾ������ʾ���ԣ�ָʾ����ʾ�Ƿ����ӽڵ�
//	// ָʾ������ʾ���������֣���ָʾ��Ϊ��ʱ����ʾ�ڵ�û���ӽڵ㣬��ָʾ��Ϊ��ͷʱ����ʾ�ڵ����ӽڵ㣬��ָʾ��Ϊ�Ӻ�ʱ����ʾ�ڵ����ӽڵ㵫δչ��
//	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);
//
//	// ��ʼ���ڵ�����
//	pRootItem->setData(0, Qt::UserRole, 0);  // ���ýڵ���û���ɫΪ0
//
//		// �������ڵ�Ŀؼ�
//	// ��һ��������ʾ�Ƿ���Ҫ��ͷ��Ĭ��Ϊfalse
//	// �ڶ���������ʾ������ָ��
//	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);
//
//	ui.treeWidget->setFixedHeight(646);  // shell�߶� - shellͷ��(talkwindow)
//
//	int nEmployeeNum = 8;  // ������50��Ա��
//	QString qsGroupName = QString::fromLocal8Bit("�г��� %1/%2").arg(0).arg(nEmployeeNum);  // ������ʾ��Ⱥ������
//	pItemName->setText(qsGroupName);  // ������ʾ��Ⱥ������
//
//	// ��Ӹ��ڵ㵽���οؼ�
//	ui.treeWidget->addTopLevelItem(pRootItem);
//	// ���ø��ڵ�Ŀؼ�����һ������Ϊ���ڵ�ָ�룬�ڶ�������Ϊ������������������Ϊ�ؼ�ָ��
//	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);
//
//	// չ�����ڵ�
//	pRootItem->setExpanded(true);
//
//	// ���Ⱥ���Ա��Ϣ
//	for (int i = 0; i < nEmployeeNum; i++)
//	{
//		addPeopInfo(pRootItem);
//	}
//}

void TalkWindow::initPtoPTalk()
{
	// ��Ϊ��Ե�����ʱ�����ܻ���һ�ű���ͼƬ
	QPixmap pixSkin;
	pixSkin.load(":/Resources/MainWindow/skin.png");

	ui.widget->setFixedSize(pixSkin.size());  // ���ÿؼ��Ĺ̶���С

	// ���ÿؼ��ı���ͼƬ
	QLabel* skinLabel = new QLabel(ui.widget);
	skinLabel->setPixmap(pixSkin);

	// ���ñ�ǩ��ؼ���ͬ��С
	skinLabel->setFixedSize(ui.widget->size());
}

void TalkWindow::initTalkWindow()
{
	// �������ڵ�
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// �������οؼ���ָʾ����ʾ���ԣ�ָʾ��������ʾ�Ƿ�������
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// ��ʼ���û�����
	pRootItem->setData(0, Qt::UserRole, 0); // �����û�����Ϊ0����ʾ���û��ڵ�

	// �������ڵ�����������ʾȺ���ƻ��߲�������
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	// �������οؼ��Ĺ̶��߶ȣ�����Ӧ���沼��
	ui.treeWidget->setFixedHeight(646);

	// ��ȡȺ���ƻ�������
	QString strGroupName;
	QSqlQuery queryGroupName(QString("SELECT department_name FROM tab_department WHERE departmentID = %1").arg(m_talkId));
	queryGroupName.exec();
	if (queryGroupName.next())
	{
		strGroupName = queryGroupName.value(0).toString();
	}

	// ���ݲ���ID��ѯԱ����Ϣ������ǹ�˾�������ѯ����Ա��������ֻ��ѯ�ò���Ա��
	QSqlQueryModel queryEmployeeModel;
	if (getCompDepID() == m_talkId.toInt())
	{
		queryEmployeeModel.setQuery("SELECT employeeID FROM tab_employees WHERE status = 1");
	}
	else
	{
		queryEmployeeModel.setQuery(QString("SELECT employeeID FROM tab_employees WHERE status = 1 AND departmentID = %1").arg(m_talkId));
	}

	// ��ȡԱ������
	int nEmployeeNum = queryEmployeeModel.rowCount();

	// ����Ⱥ���Ƶ���ʾ�ַ�������ʽΪ��Ⱥ���� Ⱥ��Ա����/������
	QString qsGroupName = QString::fromLocal8Bit("%1 %2/%3").arg(strGroupName).arg(0).arg(nEmployeeNum);

	// ��Ⱥ��������Ϊ���ڵ����ʾ�ı�
	pItemName->setText(qsGroupName);

	// ��Ӹ��ڵ㵽���οؼ���
	ui.treeWidget->addTopLevelItem(pRootItem);
	// �����ڵ����ʾ������Ϊ pItemName��������Ϊ0
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// չ�����ڵ�
	pRootItem->setExpanded(true);

	// ����Ա����Ϣ�������ӵ����ڵ���
	for (int i = 0; i < nEmployeeNum; i++)
	{
		QModelIndex modelindex = queryEmployeeModel.index(i, 0);
		int employeeID = queryEmployeeModel.data(modelindex).toInt();

		//if (employeeID == gLoginEmployeeID.toInt())
		//{
		//	continue;
		//}

		// ����Ա��ID���Ա����Ϣ�����ڵ���
		addPeopInfo(pRootItem, employeeID);
	}
}


void TalkWindow::addPeopInfo(QTreeWidgetItem * pRootGroupItem, int employeeID)
{
	// ����һ���ӽڵ����ڴ洢������Ϣ
	QTreeWidgetItem* pChild = new QTreeWidgetItem();

	// �����ӽڵ�����ݣ�UserRole ����Ϊ 1�����ڱ�ʶ����һ�����˽ڵ�
	pChild->setData(0, Qt::UserRole, 1);
	// ���ڱ�ʶ�ӽڵ�ĵ�ַ������Ϊ UserRole + 1
	pChild->setData(0, Qt::UserRole + 1, employeeID);

	// ����Ĭ��ͷ��ͼƬ
	QPixmap pix1;
	pix1.load(":/Resources/MainWindow/head_mask.png");

	// ��ȡԱ��������ǩ����ͷ��·��
	QString strName, strSign, strPicturePath;
	QSqlQueryModel queryInfoModel;
	queryInfoModel.setQuery(QString("SELECT employee_name, employee_sign, picture FROM tab_employees WHERE employeeID = %1")
		.arg(employeeID));

	QModelIndex nameIndex, signIndex, picIndex;
	nameIndex = queryInfoModel.index(0, 0);
	signIndex = queryInfoModel.index(0, 1);
	picIndex = queryInfoModel.index(0, 2);

	strName = queryInfoModel.data(nameIndex).toString();
	strSign = queryInfoModel.data(signIndex).toString();
	strPicturePath = queryInfoModel.data(picIndex).toString();

	QImage imageHead;
	imageHead.load(strPicturePath);

	// ������ϵ����
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);

	// ����Բ��ͷ��
	pContactItem->setHeadPixmap(CommonUtils::getRoundImage(QPixmap::fromImage(imageHead), pix1, pContactItem->getHeadLabelSize()));
	// ����������ǩ��
	pContactItem->setUserName(strName);
	pContactItem->setSignName(strSign);

	// ���ӽڵ���ӵ����ڵ���
	pRootGroupItem->addChild(pChild);

	// ������ϵ����ӽڵ�
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);

	// ����ϵ���������ӽڵ��ַ����ӳ���ϵ
	QString str = pContactItem->getUserNmae();
	m_groupPeoMap.insert(pChild, str);
}

void TalkWindow::onItemDoubleClicked(QTreeWidgetItem* item, int column)
{
	// ��ȡ������ݣ��ж��Ƿ�ΪҶ�ӽڵ�
	bool bIsChild = item->data(0, Qt::UserRole).toBool();

	// �����Ҷ�ӽڵ�
	if (bIsChild)
	{
		// ͨ��������ݻ�ȡ ID�����ڴ����¶Ի��򴰿�
		QString itemId = item->data(0, Qt::UserRole + 1).toString();

		if (itemId == gLoginEmployeeID) //���ܺ��Լ�����
		{
			return;
		}

		// ��ȡ��Ա����
		QString strPeopleName = m_groupPeoMap.value(item);
		// ���� WindowManager ��ľ�̬�����������µĶԻ��򴰿�
		// ��������Ӧ�Ĳ�����ID���Ի������ͣ����￴������ PTOP������Ա����
		WindowManager::getInstance()->addNewTalkWindow(itemId/*, PTOP, strPeopleName*/);
	}
}

void TalkWindow::onSendBtnClicked(bool)
{
	// �����Ϣ�Ƿ�Ϊ�գ�Ϊ������ʾ�û�������
	if (ui.textEdit->toPlainText().isEmpty())
	{
		// ��ʾ��ʾ��Ϣ��λ���� (630, 660) ��������ʱ��Ϊ 2000 ����
		QToolTip::showText(this->mapToGlobal(QPoint(630, 660)),
			QString::fromLocal8Bit("������Ϣ���ݲ���Ϊ��"),
			this, QRect(0, 0, 120, 100), 2000);
		return;
	}

	// �����ı�ת��Ϊ HTML ��ʽ
	QString& html = ui.textEdit->document()->toHtml();

	// ��� HTML �в�����ͼƬ��<span>��ǩ�������������ʽ
	if (!html.contains(".png") && !html.contains("</span>"))
	{
		QString fontHtml;
		QString text = ui.textEdit->toPlainText();
		QFile file(":/Resources/MainWindow/MsgHtml/msgFont.txt");

		if (file.open(QIODevice::ReadOnly))
		{
			fontHtml = file.readAll();
			// �� HTML �ļ��е� %1 ռλ���滻Ϊ��Ϣ�ı�
			fontHtml.replace("%1", text);
			file.close();
		}
		else
		{
			// ����ļ���ʧ�ܣ��򵯳���Ϣ����ʾ�û�
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"),
				QString::fromLocal8Bit("�ļ� msgFont.txt ������"));
			return;
		}

		// ��� HTML �в�����������ʽ���룬���滻�ı�Ϊ����������ʽ�� HTML
		if (!html.contains(fontHtml))
		{
			html.replace(text, fontHtml);
		}
	}

	// ����ı��༭��ɾ�����б���ͼƬ
	ui.textEdit->clear();
	ui.textEdit->deleteAllEmotionImage();

	ui.msgWidget->appendMsg(html); //����Ϣ���������Ϣ
}

void TalkWindow::onFileOpenBtnClicked(bool)
{
	
	SendFile* sendFile = new SendFile(this);
	sendFile->show();
}





