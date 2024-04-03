#pragma once

#include <QLabel>
#include <QPropertyAnimation>

class RootContactItem : public QLabel
{
	Q_OBJECT

	// 使用属性动画实现旋转
	Q_PROPERTY(int rotation READ rotation WRITE setRotation)

public:
	RootContactItem(bool hasArrow = true, QWidget *parent = nullptr);
	~RootContactItem();

public:
	void setText(const QString& title);
	void setExpanded(bool expand);

private:
	int rotation();
	void setRotation(int rotation);

protected:
	void paintEvent(QPaintEvent* event); // 重写绘图事件

private:
	QPropertyAnimation* m_animation; // 旋转动画
	QString m_titleText; // 显示的文本
	int m_rotation; // 头部的旋转角度
	bool m_hasArrow; // 是否有箭头
};

