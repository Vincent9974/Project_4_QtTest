#include "EmotionLabelItem.h"
#include <QMovie>

// EmotionLabelItem 构造函数
EmotionLabelItem::EmotionLabelItem(QWidget *parent)
	: QClickLabel(parent) // 调用父类的构造函数
{
	initControl(); // 初始化控件

	// 连接点击信号与槽函数，发送 emotionClicked 信号
	connect(this, &QClickLabel::clicked, [this]
	{
		emit emotionClicked(m_emotionName);
	});
}

EmotionLabelItem::~EmotionLabelItem()
{
}

// 设置表情编号的函数实现
void EmotionLabelItem::setEmotionName(int emotionName)
{
	m_emotionName = emotionName; // 设置表情编号

// 拼接图片路径
	QString imageName = QString(":/Resources/MainWindow/emotion/%1.png").arg(emotionName);

	// 创建 QMovie 对象，用于处理 APNG 格式的动画
	m_apngMovie = new QMovie(imageName, "apng", this);

	m_apngMovie->start(); // 开始播放动画
	m_apngMovie->stop(); // 停止动画
	setMovie(m_apngMovie); // 将动画设置为标签的图像
}



// 初始化控件的函数实现
void EmotionLabelItem::initControl()
{
	setAlignment(Qt::AlignCenter); // 设置标签文本的对齐方式为居中
	setObjectName("emotionLabelItem"); // 设置对象名称
	setFixedSize(32, 32); // 设置标签的固定尺寸为 32x32 像素
}