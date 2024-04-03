#pragma once

#include "QClickLabel.h" 

class EmotionLabelItem : public QClickLabel
{
	Q_OBJECT

public:
	EmotionLabelItem(QWidget *parent);
	~EmotionLabelItem();

	// ���ñ�����
	void setEmotionName(int emotionName);

private:
	void initControl();

signals:
	// �������źţ����ͱ�����
	void emotionClicked(int emotionNum);

private:
	int m_emotionName;   // ������
	QMovie* m_apngMovie; // APNG ��������ָ��
};
