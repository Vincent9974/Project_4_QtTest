#include "QMsgTextEdit.h"

#include<QMovie>
#include<QUrl>

QMsgTextEdit::QMsgTextEdit(QWidget *parent)
	: QTextEdit(parent)
{

}

QMsgTextEdit::~QMsgTextEdit()
{
	deleteAllEmotionImage();
}

void QMsgTextEdit::addEmotionUrl(int emotionNum)
{
	// 添加表情图片
	// 构造图片路径
	// 插入图片标签
	const QString& imageName = QString("qrc:/Resources/MainWindow/emotion/%1.png").arg(emotionNum);
	const QString& flagName = QString("%1").arg(imageName);
	insertHtml(QString("<img src='%1' />").arg(flagName));


	// 判断图片路径是否已存在
	// 如果已存在则直接返回，不重复添加
	// 否则将路径添加到列表中
	if (m_listEmotionUrl.contains(imageName))
	{
		return;
	}
	else
	{
		m_listEmotionUrl.append(imageName);
	}


	// 创建动画对象并添加到映射中
	QMovie* apngMovie = new QMovie(imageName, "apng", this);
	m_emotionMap.insert(apngMovie, flagName);

	// 连接动画帧改变信号和槽函数
	connect(apngMovie, SIGNAL(frameChanged(int)), this, SLOT(onEmotionImageFrameChange(int)));

	// 启动动画
	apngMovie->start();
	updateGeometry();
}

void QMsgTextEdit::deleteAllEmotionImage()
{
	for (auto itor = m_emotionMap.constBegin();
		itor != m_emotionMap.constEnd(); ++itor)
	{
		delete itor.key();
	}

	m_emotionMap.clear();
}

void QMsgTextEdit::onEmotionImageFrameChange(int frame)
{
	// 获取当前发送信号的动画对象
	QMovie* movie = qobject_cast<QMovie*>(sender());

	// 添加资源以便文本编辑器显示动画图片
	document()->addResource(QTextDocument::ImageResource,
		QUrl(m_emotionMap.value(movie)), movie->currentPixmap());
}