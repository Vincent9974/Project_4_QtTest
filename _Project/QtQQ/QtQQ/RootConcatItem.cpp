#include "RootConcatItem.h"
#include <QPainter>

RootContactItem::RootContactItem(bool hasArrow, QWidget *parent)
	: QLabel(parent),
	m_rotation(0),
	m_hasArrow(hasArrow)
{
	// ���ù̶��ĸ߶�
	setFixedHeight(32);

	// ���ô�С���ԣ�ˮƽ�ʹ�ֱ���������չ�����߶ȹ̶�
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	// ��ʼ����ת����
	// �� rotation ��������ΪĿ������
	m_animation = new QPropertyAnimation(this, "rotation");

	// ���ö���ʱ��Ϊ 50 ���룬����ת��Ŀ��λ�õĳ���ʱ��
	m_animation->setDuration(50);

	// ���ö����������ߣ�����ʹ�� InQuad ���ߣ���ʾ�����˶�
	m_animation->setEasingCurve(QEasingCurve::InQuad);
}

RootContactItem::~RootContactItem()
{

}

void RootContactItem::setText(const QString& title)
{
	m_titleText = title;
	update();
}

void RootContactItem::setExpanded(bool expand)
{
	// �ж��Ƿ�չ��������Ŀ����ת�Ƕ�
	if (expand)
	{
		m_animation->setEndValue(90);
	}
	else
	{
		m_animation->setEndValue(0);
	}

	m_animation->start();
}

int RootContactItem::rotation()
{
	return m_rotation;
}

void RootContactItem::setRotation(int rotation)
{
	m_rotation = rotation;
	update();
}

void RootContactItem::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::TextAntialiasing, true);

	QFont font;
	font.setPointSize(10);
	painter.setFont(font);


	painter.drawText(24, 0, width() - 24, height(), Qt::AlignLeft | Qt::AlignVCenter, m_titleText);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
	painter.save();


	// ���Ƽ�ͷͼ��
	if (m_hasArrow)
	{
		QPixmap pixmap;
		pixmap.load(":/Resources/MainWindow/arrow.png");

		QPixmap tmpPixmap(pixmap.size());
		tmpPixmap.fill(Qt::transparent);

		QPainter p(&tmpPixmap);
		p.setRenderHint(QPainter::SmoothPixmapTransform, true);
		p.translate(pixmap.width() / 2, pixmap.height() / 2);
		p.rotate(m_rotation);
		p.drawPixmap(0 - pixmap.width() / 2, 0 - pixmap.height() / 2, pixmap);  

		painter.drawPixmap(6, (height() - pixmap.height()) / 2, tmpPixmap);

		painter.restore();
	}

	QLabel::paintEvent(event);
}
