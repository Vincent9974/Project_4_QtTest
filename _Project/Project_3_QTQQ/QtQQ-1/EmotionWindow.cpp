#include "EmotionWindow.h" 
#include "CommonUtils.h" 
#include "EmotionLabelItem.h" 

#include <QStyleOption> 
#include <QPainter> 

const int emotionColumn = 14; // 表情列数
const int emotionRow = 12; // 表情行数


EmotionWindow::EmotionWindow(QWidget *parent)
	: QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);
	setAttribute(Qt::WA_TranslucentBackground);
	setAttribute(Qt::WA_DeleteOnClose);

	ui.setupUi(this);
	initControl();
}

EmotionWindow::~EmotionWindow()
{
}

// 初始化控件
void EmotionWindow::initControl()
{
	// 加载样式表
	CommonUtils::loadStyleSheet(this, "EmotionWindow");

	// 创建并添加表情标签项
	for (int row = 0; row < emotionRow; row++)
	{
		for (int column = 0; column < emotionColumn; column++)
		{
			EmotionLabelItem* label = new EmotionLabelItem(this);
			// 设置表情编号
			label->setEmotionName(row * emotionColumn + column);
			// 连接表情点击信号到槽函数 addEmotion
			connect(label, &EmotionLabelItem::emotionClicked, this, &EmotionWindow::addEmotion);
			// 将标签项添加到网格布局中
			ui.gridLayout->addWidget(label, row, column);
		}
	}
}


// 添加表情，隐藏窗口并发送信号
void EmotionWindow::addEmotion(int emotionNum)
{
	hide(); // 隐藏窗口
	emit signalEmotionWindowHide(); // 发送表情窗口隐藏信号
	emit signalEmotionItemClicked(emotionNum); // 发送表情项点击信号
}



// 重绘事件
void EmotionWindow::paintEvent(QPaintEvent* event)
{
	QStyleOption opt; // 样式选项
	opt.init(this); // 初始化样式选项
	QPainter painter(this); // 绘图对象

	// 使用当前风格绘制窗口
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

	__super::paintEvent(event); // 调用父类的绘图事件处理函数

}