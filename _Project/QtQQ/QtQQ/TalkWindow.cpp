#include "TalkWindow.h"
#include "ContactItem.h"
#include "CommonUtils.h"
#include "WindowManager.h"
#include "RootConcatItem.h"


#include <QToolTip>
#include <QFile>
#include <QMessageBox>


TalkWindow::TalkWindow(QWidget* parent, const QString& uid, GroupType groupType)
	: QWidget(parent),
	m_talkId(uid),
	m_groupType(groupType)
{
	ui.setupUi(this);

	// ������������ʵ������������Ա��ڴ��ڹر�ʱɾ���������ֵ�ӳ��
	WindowManager::getInstance()->addWindowName(m_talkId, this);
	setAttribute(Qt::WA_DeleteOnClose); // �ڴ��ڹر�ʱ�Զ�ɾ������
	initControl();
}

TalkWindow::~TalkWindow()
{
	// ���ڹر�ʱɾ���������ֵ�ӳ��
	WindowManager::getInstance()->deleteWindowName(m_talkId);
}

void TalkWindow::addEmotionImage(int emotionNum)
{

}

void TalkWindow::setWindowName(const QString & name)
{
	ui.nameLabel->setText(name);
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
	// ����Ⱥ�����ͳ�ʼ���Ի�����
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
}

void TalkWindow::initCompanyTalk()
{
	// �������ڵ�
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// �����ӽڵ�ָʾ������ʾ���ԣ�ָʾ����ʾ�Ƿ����ӽڵ�
	// ָʾ������ʾ���������֣���ָʾ��Ϊ��ʱ����ʾ�ڵ�û���ӽڵ㣬��ָʾ��Ϊ��ͷʱ����ʾ�ڵ����ӽڵ㣬��ָʾ��Ϊ�Ӻ�ʱ����ʾ�ڵ����ӽڵ㵫δչ��
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// ��ʼ���ڵ�����
	pRootItem->setData(0, Qt::UserRole, 0);  // ���ýڵ���û���ɫΪ0

		// �������ڵ�Ŀؼ�
	// ��һ��������ʾ�Ƿ���Ҫ��ͷ��Ĭ��Ϊfalse
	// �ڶ���������ʾ������ָ��
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	ui.treeWidget->setFixedHeight(646);  // shell�߶� - shellͷ��(talkwindow)

	int nEmployeeNum = 50;  // ������50��Ա��
	QString qsGroupName = QString::fromLocal8Bit("��˾Ⱥ %1/%2").arg(0).arg(nEmployeeNum);  // ������ʾ��Ⱥ������
	pItemName->setText(qsGroupName);  // ������ʾ��Ⱥ������

	// ��Ӹ��ڵ㵽���οؼ�
	ui.treeWidget->addTopLevelItem(pRootItem);
	// ���ø��ڵ�Ŀؼ�����һ������Ϊ���ڵ�ָ�룬�ڶ�������Ϊ������������������Ϊ�ؼ�ָ��
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// չ�����ڵ�
	pRootItem->setExpanded(true);

	// ���Ⱥ���Ա��Ϣ
	for (int i = 0; i < nEmployeeNum; i++)
	{
		addPeopInfo(pRootItem);
	}

}

void TalkWindow::initPersonelTalk()
{
	// �������ڵ�
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// �����ӽڵ�ָʾ������ʾ���ԣ�ָʾ����ʾ�Ƿ����ӽڵ�
	// ָʾ������ʾ���������֣���ָʾ��Ϊ��ʱ����ʾ�ڵ�û���ӽڵ㣬��ָʾ��Ϊ��ͷʱ����ʾ�ڵ����ӽڵ㣬��ָʾ��Ϊ�Ӻ�ʱ����ʾ�ڵ����ӽڵ㵫δչ��
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// ��ʼ���ڵ�����
	pRootItem->setData(0, Qt::UserRole, 0);  // ���ýڵ���û���ɫΪ0

		// �������ڵ�Ŀؼ�
	// ��һ��������ʾ�Ƿ���Ҫ��ͷ��Ĭ��Ϊfalse
	// �ڶ���������ʾ������ָ��
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	ui.treeWidget->setFixedHeight(646);  // shell�߶� - shellͷ��(talkwindow)

	int nEmployeeNum = 5;  // ������50��Ա��
	QString qsGroupName = QString::fromLocal8Bit("���²� %1/%2").arg(0).arg(nEmployeeNum);  // ������ʾ��Ⱥ������
	pItemName->setText(qsGroupName);  // ������ʾ��Ⱥ������

	// ��Ӹ��ڵ㵽���οؼ�
	ui.treeWidget->addTopLevelItem(pRootItem);
	// ���ø��ڵ�Ŀؼ�����һ������Ϊ���ڵ�ָ�룬�ڶ�������Ϊ������������������Ϊ�ؼ�ָ��
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// չ�����ڵ�
	pRootItem->setExpanded(true);

	// ���Ⱥ���Ա��Ϣ
	for (int i = 0; i < nEmployeeNum; i++)
	{
		addPeopInfo(pRootItem);
	}
}

void TalkWindow::initDevelopmentTalk()
{
	// �������ڵ�
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// �����ӽڵ�ָʾ������ʾ���ԣ�ָʾ����ʾ�Ƿ����ӽڵ�
	// ָʾ������ʾ���������֣���ָʾ��Ϊ��ʱ����ʾ�ڵ�û���ӽڵ㣬��ָʾ��Ϊ��ͷʱ����ʾ�ڵ����ӽڵ㣬��ָʾ��Ϊ�Ӻ�ʱ����ʾ�ڵ����ӽڵ㵫δչ��
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// ��ʼ���ڵ�����
	pRootItem->setData(0, Qt::UserRole, 0);  // ���ýڵ���û���ɫΪ0

		// �������ڵ�Ŀؼ�
	// ��һ��������ʾ�Ƿ���Ҫ��ͷ��Ĭ��Ϊfalse
	// �ڶ���������ʾ������ָ��
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	ui.treeWidget->setFixedHeight(646);  // shell�߶� - shellͷ��(talkwindow)

	int nEmployeeNum = 32;  // ������50��Ա��
	QString qsGroupName = QString::fromLocal8Bit("�з��� %1/%2").arg(0).arg(nEmployeeNum);  // ������ʾ��Ⱥ������
	pItemName->setText(qsGroupName);  // ������ʾ��Ⱥ������

	// ��Ӹ��ڵ㵽���οؼ�
	ui.treeWidget->addTopLevelItem(pRootItem);
	// ���ø��ڵ�Ŀؼ�����һ������Ϊ���ڵ�ָ�룬�ڶ�������Ϊ������������������Ϊ�ؼ�ָ��
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// չ�����ڵ�
	pRootItem->setExpanded(true);

	// ���Ⱥ���Ա��Ϣ
	for (int i = 0; i < nEmployeeNum; i++)
	{
		addPeopInfo(pRootItem);
	}
}

void TalkWindow::initMarketTalk()
{
	// �������ڵ�
	QTreeWidgetItem* pRootItem = new QTreeWidgetItem();

	// �����ӽڵ�ָʾ������ʾ���ԣ�ָʾ����ʾ�Ƿ����ӽڵ�
	// ָʾ������ʾ���������֣���ָʾ��Ϊ��ʱ����ʾ�ڵ�û���ӽڵ㣬��ָʾ��Ϊ��ͷʱ����ʾ�ڵ����ӽڵ㣬��ָʾ��Ϊ�Ӻ�ʱ����ʾ�ڵ����ӽڵ㵫δչ��
	pRootItem->setChildIndicatorPolicy(QTreeWidgetItem::ShowIndicator);

	// ��ʼ���ڵ�����
	pRootItem->setData(0, Qt::UserRole, 0);  // ���ýڵ���û���ɫΪ0

		// �������ڵ�Ŀؼ�
	// ��һ��������ʾ�Ƿ���Ҫ��ͷ��Ĭ��Ϊfalse
	// �ڶ���������ʾ������ָ��
	RootContactItem* pItemName = new RootContactItem(false, ui.treeWidget);

	ui.treeWidget->setFixedHeight(646);  // shell�߶� - shellͷ��(talkwindow)

	int nEmployeeNum = 8;  // ������50��Ա��
	QString qsGroupName = QString::fromLocal8Bit("�г��� %1/%2").arg(0).arg(nEmployeeNum);  // ������ʾ��Ⱥ������
	pItemName->setText(qsGroupName);  // ������ʾ��Ⱥ������

	// ��Ӹ��ڵ㵽���οؼ�
	ui.treeWidget->addTopLevelItem(pRootItem);
	// ���ø��ڵ�Ŀؼ�����һ������Ϊ���ڵ�ָ�룬�ڶ�������Ϊ������������������Ϊ�ؼ�ָ��
	ui.treeWidget->setItemWidget(pRootItem, 0, pItemName);

	// չ�����ڵ�
	pRootItem->setExpanded(true);

	// ���Ⱥ���Ա��Ϣ
	for (int i = 0; i < nEmployeeNum; i++)
	{
		addPeopInfo(pRootItem);
	}
}

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

void TalkWindow::addPeopInfo(QTreeWidgetItem * pRootGroupItem)
{
	// ����һ���µ��������ڴ洢��ϵ����Ϣ
	QTreeWidgetItem* pChild = new QTreeWidgetItem();

	// ����ͷ������ͼƬ
	QPixmap pix1;
	pix1.load(":/Resources/MainWindow/head_mask.png");

	// �����û�ͷ��ͼƬ
	const QPixmap image(":/Resources/MainWindow/girl.png");

	// ������������ 
	pChild->setData(0, Qt::UserRole, 1); // ʹ�� UserRole �洢�û�����
	// ʹ�� UserRole+1 �洢�����ָ���ַ�����ں���������ʶ
	pChild->setData(0, Qt::UserRole + 1, QString::number((int)pChild));

	// ������ϵ����
	ContactItem* pContactItem = new ContactItem(ui.treeWidget);

	static int i = 0;

	// ����Բ��ͷ��
	pContactItem->setHeadPixmap(CommonUtils::getRoundImage(image, pix1, pContactItem->getHeadLabelSize()));
	// �����û���
	pContactItem->setUserName(QString::fromLocal8Bit("�û�%1").arg(i++));
	pContactItem->setSignName(QString::fromLocal8Bit("(����ǩ��)"));

	// ��������ӵ����ڵ���
	pRootGroupItem->addChild(pChild);

	// ����ϵ������ӵ�������
	ui.treeWidget->setItemWidget(pChild, 0, pContactItem);

	// ��ȡ�û�����������ָ����û�����ӵ�ӳ���У����ں�������
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
		// ��ȡ��Ա����
		QString strPeopleName = m_groupPeoMap.value(item);

		// ͨ��������ݻ�ȡ ID�����ڴ����¶Ի��򴰿�
		QString itemId = item->data(0, Qt::UserRole + 1).toString();

		// ���� WindowManager ��ľ�̬�����������µĶԻ��򴰿�
		// ��������Ӧ�Ĳ�����ID���Ի������ͣ����￴������ PTOP������Ա����
		WindowManager::getInstance()->addNewTalkWindow(itemId, PTOP, strPeopleName);
	}
}



