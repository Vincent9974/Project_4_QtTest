#pragma once

#include <QTextEdit>

class QMsgTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	QMsgTextEdit(QWidget *parent = nullptr); // 构造函数
	~QMsgTextEdit(); // 析构函数

public:
	/*
		由于需要插入表情图片、处理表情图片的位置、以及文本的位置，
		文本编辑器需要对应的接口。
	*/

	// 添加表情图片，参数为表情图片的编号
	void addEmotionUrl(int emotionNum);

	// 删除所有表情图片
	void deleteAllEmotionImage();


private slots:
	// 当表情图片帧改变时的槽函数
	void onEmotionImageFrameChange(int frame);

private:
	// 表情图片地址列表
	QList<QString> m_listEmotionUrl;

	// 表情图片与其文件路径的映射关系
	QMap<QMovie*, QString> m_emotionMap;

};
