#pragma once

#include "QClickLabel.h" 

class EmotionLabelItem : public QClickLabel
{
	Q_OBJECT

public:
	EmotionLabelItem(QWidget *parent);
	~EmotionLabelItem();

	// 设置表情编号
	void setEmotionName(int emotionName);

private:
	void initControl();

signals:
	// 表情点击信号，发送表情编号
	void emotionClicked(int emotionNum);

private:
	int m_emotionName;   // 表情编号
	QMovie* m_apngMovie; // APNG 动画对象指针
};
