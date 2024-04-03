#include "EmotionLabelItem.h"
#include <QMovie>

// EmotionLabelItem ���캯��
EmotionLabelItem::EmotionLabelItem(QWidget *parent)
	: QClickLabel(parent) // ���ø���Ĺ��캯��
{
	initControl(); // ��ʼ���ؼ�

	// ���ӵ���ź���ۺ��������� emotionClicked �ź�
	connect(this, &QClickLabel::clicked, [this]
	{
		emit emotionClicked(m_emotionName);
	});
}

EmotionLabelItem::~EmotionLabelItem()
{
}

// ���ñ����ŵĺ���ʵ��
void EmotionLabelItem::setEmotionName(int emotionName)
{
	m_emotionName = emotionName; // ���ñ�����

// ƴ��ͼƬ·��
	QString imageName = QString(":/Resources/MainWindow/emotion/%1.png").arg(emotionName);

	// ���� QMovie �������ڴ��� APNG ��ʽ�Ķ���
	m_apngMovie = new QMovie(imageName, "apng", this);

	m_apngMovie->start(); // ��ʼ���Ŷ���
	m_apngMovie->stop(); // ֹͣ����
	setMovie(m_apngMovie); // ����������Ϊ��ǩ��ͼ��
}



// ��ʼ���ؼ��ĺ���ʵ��
void EmotionLabelItem::initControl()
{
	setAlignment(Qt::AlignCenter); // ���ñ�ǩ�ı��Ķ��뷽ʽΪ����
	setObjectName("emotionLabelItem"); // ���ö�������
	setFixedSize(32, 32); // ���ñ�ǩ�Ĺ̶��ߴ�Ϊ 32x32 ����
}