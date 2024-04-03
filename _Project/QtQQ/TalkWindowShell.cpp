#include "TalkWindowShell.h"
#include "CommonUtils.h"
#include "BasicWindow.h"
#include <QListWidget>
#include "TalkWindow.h"
#include "TalkWindowItem.h"



// TalkWindowShell 类的构造函数
TalkWindowShell::TalkWindowShell(QWidget *parent)
	: BasicWindow(parent) // 调用父类构造函数进行初始化
{
	ui.setupUi(this); // 设置 UI

	setAttribute(Qt::WA_DeleteOnClose); // 设置在关闭时删除对象的属性
	initControl(); // 初始化控件
}

// TalkWindowShell 类的析构函数
TalkWindowShell::~TalkWindowShell()
{
	delete m_emotionWindow; // 删除 m_emotionWindow 对象
	m_emotionWindow = nullptr; // 置空指针
}

// 设置当前显示的窗口
void TalkWindowShell::setCurrentWidget(QWidget* widget)
{
	ui.rightStackedWidget->setCurrentWidget(widget);
}

// 获取对话窗口项的映射关系
const QMap<QListWidgetItem*, QWidget*>& TalkWindowShell::getTalkWindowItemMap() const
{
	return m_talkwindowItemMap;
}

// 初始化控件
void TalkWindowShell::initControl()
{
	loadStyleSheet("TalkWindow"); // 加载样式表
	setWindowTitle(QString::fromLocal8Bit("聊天窗口1")); // 设置窗口标题

	m_emotionWindow = new EmotionWindow; // 创建表情窗口对象
	m_emotionWindow->hide(); // 隐藏表情窗口

	QList<int> leftWidgetSize; // 设置左侧窗口的初始大小
	leftWidgetSize << 154 << width() - 154;
	ui.splitter->setSizes(leftWidgetSize);

	ui.listWidget->setStyle(new CustomProxyStyle(this)); // 设置列表控件的自定义样式

	// 连接列表控件项点击信号与槽函数，以及表情窗口表情项点击信号与槽函数
	connect(ui.listWidget, &QListWidget::itemClicked, this, &TalkWindowShell::onTalkWindowItemClicked);
	connect(m_emotionWindow, SIGNAL(signalEmotionItemClicked(int)), this, SLOT(onEmotionItemClicked(int)));
}

// 向 TalkWindowShell 中添加对话窗口和对应的项
void TalkWindowShell::addTalkWindow(TalkWindow* talkWindow, TalkWindowItem* talkWindowItem, GroupType groupType)
{
	ui.rightStackedWidget->addWidget(talkWindow); // 将对话窗口添加到右侧堆叠窗口中

	// 连接表情窗口隐藏信号与对话窗口状态设置槽函数
	connect(m_emotionWindow, SIGNAL(signalEmotionWindowHide()), talkWindow, SLOT(onSetEmotionBtnStatus()));


	// 创建对话窗口项
	QListWidgetItem* aItem = new QListWidgetItem(ui.listWidget);
	m_talkwindowItemMap.insert(aItem, talkWindow); // 将对话窗口项与对话窗口关联


	aItem->setSelected(true); // 选中对话窗口项

	// 设置对话窗口项的头像和插入到列表控件中
	talkWindowItem->setHeadPixmap(QPixmap(":/Resources/MainWindow/girl.png"));
	ui.listWidget->addItem(aItem);
	ui.listWidget->setItemWidget(aItem, talkWindowItem);

	onTalkWindowItemClicked(aItem); // 显示对应的对话窗口

	// 连接对话窗口项关闭信号与处理槽函数
	connect(talkWindowItem, &TalkWindowItem::signalCloseClicked, [talkWindowItem, talkWindow, aItem, this]()
	{
		m_talkwindowItemMap.remove(aItem); // 从映射中移除对话窗口项
		talkWindow->close(); // 关闭对话窗口
		ui.listWidget->takeItem(ui.listWidget->row(aItem)); // 从列表控件中移除对话窗口项
		delete talkWindowItem; // 删除对话窗口项

		ui.rightStackedWidget->removeWidget(talkWindow); // 从右侧堆叠窗口中移除对话窗口

		// 如果没有对话窗口显示了，关闭 TalkWindowShell 窗口
		if (ui.rightStackedWidget->count() < 1)
		{
			close();
		}
	});
}

// 处理表情按钮点击事件
void TalkWindowShell::onEmotionBtnClicked(bool)
{
	m_emotionWindow->setVisible(!m_emotionWindow->isVisible()); // 切换表情窗口的可见性

	// 将表情窗口移动到合适的位置
	QPoint emotionPoint = this->mapToGlobal(QPoint(0, 0));
	emotionPoint.setX(emotionPoint.x() + 170);
	emotionPoint.setY(emotionPoint.y() + 220);
	m_emotionWindow->move(emotionPoint);
}

// 处理表情项点击事件
void TalkWindowShell::onEmotionItemClicked(int emotionNum)
{
	TalkWindow* curTalkWindow = dynamic_cast<TalkWindow*>(ui.rightStackedWidget->currentWidget()); // 获取当前显示的对话窗口
	if (curTalkWindow) // 判断当前对话窗口是否有效
	{
		curTalkWindow->addEmotionImage(emotionNum); // 向当前对话窗口添加表情图片
	}
}

// 处理对话窗口项点击事件
void TalkWindowShell::onTalkWindowItemClicked(QListWidgetItem* item)
{
	QWidget* talkWindowWidget = m_talkwindowItemMap.find(item).value(); // 获取对应的对话窗口
	ui.rightStackedWidget->setCurrentWidget(talkWindowWidget); // 设置当前显示的窗口为对话窗口
}
