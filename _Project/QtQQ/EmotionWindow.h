#pragma once
#include "ui_EmotionWindow.h" // 包含 UI 文件的头文件

#include <QWidget> // 包含 QWidget 头文件

class EmotionWindow : public QWidget
{
	Q_OBJECT // 使用 QObject 的宏定义

public:
	EmotionWindow(QWidget *parent = Q_NULLPTR); // 构造函数
	~EmotionWindow(); // 析构函数

private:
	void initControl(); // 初始化控件

private slots:
	void addEmotion(int emotionNum); // 添加表情，响应表情按钮点击事件

signals:
	void signalEmotionWindowHide(); // 表情窗口隐藏信号
	void signalEmotionItemClicked(int emotionNum); // 表情项点击信号

private:
	void paintEvent(QPaintEvent* event) override; // 重写绘图事件

private:
	Ui::EmotionWindow ui; // UI 对象
};
