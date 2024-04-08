#include "RootConcatItem.h"
#include <QPainter>

RootContactItem::RootContactItem(bool hasArrow, QWidget *parent)
	: QLabel(parent),
	m_rotation(0),
	m_hasArrow(hasArrow)
{
	// 设置固定的高度
	setFixedHeight(32);

	// 设置大小策略，水平和垂直方向均可扩展，但高度固定
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	// 初始化旋转动画
	// 将 rotation 属性设置为目标属性
	m_animation = new QPropertyAnimation(this, "rotation");

	// 设置动画时长为 50 毫秒，即旋转到目标位置的持续时间
	m_animation->setDuration(50);

	// 设置动画缓和曲线，这里使用 InQuad 曲线，表示加速运动
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
	// 判断是否展开，设置目标旋转角度
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


	// 绘制箭头图标
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
