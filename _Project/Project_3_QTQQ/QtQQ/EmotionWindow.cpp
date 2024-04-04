#include "EmotionWindow.h" 
#include "CommonUtils.h" 
#include "EmotionLabelItem.h" 

#include <QStyleOption> 
#include <QPainter> 

const int emotionColumn = 14; // ��������
const int emotionRow = 12; // ��������


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

// ��ʼ���ؼ�
void EmotionWindow::initControl()
{
	// ������ʽ��
	CommonUtils::loadStyleSheet(this, "EmotionWindow");

	// ��������ӱ����ǩ��
	for (int row = 0; row < emotionRow; row++)
	{
		for (int column = 0; column < emotionColumn; column++)
		{
			EmotionLabelItem* label = new EmotionLabelItem(this);
			// ���ñ�����
			label->setEmotionName(row * emotionColumn + column);
			// ���ӱ������źŵ��ۺ��� addEmotion
			connect(label, &EmotionLabelItem::emotionClicked, this, &EmotionWindow::addEmotion);
			// ����ǩ����ӵ����񲼾���
			ui.gridLayout->addWidget(label, row, column);
		}
	}
}


// ��ӱ��飬���ش��ڲ������ź�
void EmotionWindow::addEmotion(int emotionNum)
{
	hide(); // ���ش���
	emit signalEmotionWindowHide(); // ���ͱ��鴰�������ź�
	emit signalEmotionItemClicked(emotionNum); // ���ͱ��������ź�
}



// �ػ��¼�
void EmotionWindow::paintEvent(QPaintEvent* event)
{
	QStyleOption opt; // ��ʽѡ��
	opt.init(this); // ��ʼ����ʽѡ��
	QPainter painter(this); // ��ͼ����

	// ʹ�õ�ǰ�����ƴ���
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

	__super::paintEvent(event); // ���ø���Ļ�ͼ�¼�������

}