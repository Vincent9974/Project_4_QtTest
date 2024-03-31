#include "TalkWindowShell.h"
#include "CommonUtils.h"
#include "BasicWindow.h"
#include <QListWidget>
#include "TalkWindow.h"
#include "TalkWindowItem.h"



// TalkWindowShell ��Ĺ��캯��
TalkWindowShell::TalkWindowShell(QWidget *parent)
	: BasicWindow(parent) // ���ø��๹�캯�����г�ʼ��
{
	ui.setupUi(this); // ���� UI

	setAttribute(Qt::WA_DeleteOnClose); // �����ڹر�ʱɾ�����������
	initControl(); // ��ʼ���ؼ�
}

// TalkWindowShell �����������
TalkWindowShell::~TalkWindowShell()
{
	delete m_emotionWindow; // ɾ�� m_emotionWindow ����
	m_emotionWindow = nullptr; // �ÿ�ָ��
}

// ���õ�ǰ��ʾ�Ĵ���
void TalkWindowShell::setCurrentWidget(QWidget* widget)
{
	ui.rightStackedWidget->setCurrentWidget(widget);
}

// ��ȡ�Ի��������ӳ���ϵ
const QMap<QListWidgetItem*, QWidget*>& TalkWindowShell::getTalkWindowItemMap() const
{
	return m_talkwindowItemMap;
}

// ��ʼ���ؼ�
void TalkWindowShell::initControl()
{
	loadStyleSheet("TalkWindow"); // ������ʽ��
	setWindowTitle(QString::fromLocal8Bit("���촰��1")); // ���ô��ڱ���

	m_emotionWindow = new EmotionWindow; // �������鴰�ڶ���
	m_emotionWindow->hide(); // ���ر��鴰��

	QList<int> leftWidgetSize; // ������ര�ڵĳ�ʼ��С
	leftWidgetSize << 154 << width() - 154;
	ui.splitter->setSizes(leftWidgetSize);

	ui.listWidget->setStyle(new CustomProxyStyle(this)); // �����б�ؼ����Զ�����ʽ

	// �����б�ؼ������ź���ۺ������Լ����鴰�ڱ��������ź���ۺ���
	connect(ui.listWidget, &QListWidget::itemClicked, this, &TalkWindowShell::onTalkWindowItemClicked);
	connect(m_emotionWindow, SIGNAL(signalEmotionItemClicked(int)), this, SLOT(onEmotionItemClicked(int)));
}

// �� TalkWindowShell ����ӶԻ����ںͶ�Ӧ����
void TalkWindowShell::addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, GroupType groupType)
{
	ui.rightStackedWidget->addWidget(talkWindow); // ���Ի�������ӵ��Ҳ�ѵ�������

	// ���ӱ��鴰�������ź���Ի�����״̬���òۺ���
	connect(m_emotionWindow, SIGNAL(signalEmotionWindowHide()), talkWindow, SLOT(onSetEmotionBtnStatus()));


	// �����Ի�������
	QListWidgetItem* aItem = new QListWidgetItem(ui.listWidget);
	m_talkwindowItemMap.insert(aItem, talkWindow); // ���Ի���������Ի����ڹ���


	aItem->setSelected(true); // ѡ�жԻ�������

	// ���öԻ��������ͷ��Ͳ��뵽�б�ؼ���
	talkWindowItem->setHeadPixmap(QPixmap(":/Resources/MainWindow/girl.png"));
	ui.listWidget->addItem(aItem);
	ui.listWidget->setItemWidget(aItem, talkWindowItem);

	onTalkWindowItemClicked(aItem); // ��ʾ��Ӧ�ĶԻ�����

	// ���ӶԻ�������ر��ź��봦��ۺ���
	connect(talkWindowItem, &TalkWindowItem::signalCloseClicked, [talkWindowItem, talkWindow, aItem, this]()
	{
		m_talkwindowItemMap.remove(aItem); // ��ӳ�����Ƴ��Ի�������
		talkWindow->close(); // �رնԻ�����
		ui.listWidget->takeItem(ui.listWidget->row(aItem)); // ���б�ؼ����Ƴ��Ի�������
		delete talkWindowItem; // ɾ���Ի�������

		ui.rightStackedWidget->removeWidget(talkWindow); // ���Ҳ�ѵ��������Ƴ��Ի�����

		// ���û�жԻ�������ʾ�ˣ��ر� TalkWindowShell ����
		if (ui.rightStackedWidget->count() < 1)
		{
			close();
		}
	});
}

// ������鰴ť����¼�
void TalkWindowShell::onEmotionBtnClicked(bool)
{
	m_emotionWindow->setVisible(!m_emotionWindow->isVisible()); // �л����鴰�ڵĿɼ���

	// �����鴰���ƶ������ʵ�λ��
	QPoint emotionPoint = this->mapToGlobal(QPoint(0, 0));
	emotionPoint.setX(emotionPoint.x() + 170);
	emotionPoint.setY(emotionPoint.y() + 220);
	m_emotionWindow->move(emotionPoint);
}

// ������������¼�
void TalkWindowShell::onEmotionItemClicked(int emotionNum)
{
	TalkWindow* curTalkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget()); // ��ȡ��ǰ��ʾ�ĶԻ�����
	if (curTalkWindow) // �жϵ�ǰ�Ի������Ƿ���Ч
	{
		curTalkWindow->addEmotionImage(emotionNum); // ��ǰ�Ի�������ӱ���ͼƬ
	}
}

// ����Ի����������¼�
void TalkWindowShell::onTalkWindowItemClicked(QListWidgetItem* item)
{
	QWidget* talkWindowWidget = m_talkwindowItemMap.find(item).value(); // ��ȡ��Ӧ�ĶԻ�����
	ui.rightStackedWidget->setCurrentWidget(talkWindowWidget); // ���õ�ǰ��ʾ�Ĵ���Ϊ�Ի�����
}
