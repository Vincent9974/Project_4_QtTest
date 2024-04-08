#pragma once

#include <QTextEdit>

class QMsgTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	QMsgTextEdit(QWidget *parent = nullptr); // ���캯��
	~QMsgTextEdit(); // ��������

public:
	/*
		������Ҫ�������ͼƬ���������ͼƬ��λ�á��Լ��ı���λ�ã�
		�ı��༭����Ҫ��Ӧ�Ľӿڡ�
	*/

	// ��ӱ���ͼƬ������Ϊ����ͼƬ�ı��
	void addEmotionUrl(int emotionNum);

	// ɾ�����б���ͼƬ
	void deleteAllEmotionImage();


private slots:
	// ������ͼƬ֡�ı�ʱ�Ĳۺ���
	void onEmotionImageFrameChange(int frame);

private:
	// ����ͼƬ��ַ�б�
	QList<QString> m_listEmotionUrl;

	// ����ͼƬ�����ļ�·����ӳ���ϵ
	QMap<QMovie*, QString> m_emotionMap;

};
