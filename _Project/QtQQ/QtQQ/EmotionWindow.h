#pragma once
#include "ui_EmotionWindow.h" // ���� UI �ļ���ͷ�ļ�

#include <QWidget> // ���� QWidget ͷ�ļ�

class EmotionWindow : public QWidget
{
	Q_OBJECT // ʹ�� QObject �ĺ궨��

public:
	EmotionWindow(QWidget *parent = Q_NULLPTR); // ���캯��
	~EmotionWindow(); // ��������

private:
	void initControl(); // ��ʼ���ؼ�

private slots:
	void addEmotion(int emotionNum); // ��ӱ��飬��Ӧ���鰴ť����¼�

signals:
	void signalEmotionWindowHide(); // ���鴰�������ź�
	void signalEmotionItemClicked(int emotionNum); // ���������ź�

private:
	void paintEvent(QPaintEvent* event) override; // ��д��ͼ�¼�

private:
	Ui::EmotionWindow ui; // UI ����
};
