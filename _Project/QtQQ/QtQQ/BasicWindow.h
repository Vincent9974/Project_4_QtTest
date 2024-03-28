#pragma once

#include <QDialog>

#include "TitleBar.h"

class BasicWindow : public QDialog
{
	Q_OBJECT

public:
	BasicWindow(QWidget *parent=nullptr);
	virtual ~BasicWindow();

public:
	//������ʽ��
	void loadStyleSheet(const QString& sheetName);

	//��ȡԲ��ͷ��
	QPixmap getRoundImage(const QPixmap &src, QPixmap& mask, QSize masksize = QSize(0, 0));

private:
	void initBackGroundColor(); //��ʼ������


protected:
	void initTitleBar(ButtonType buttontype = MIN_BUTTON);
	void setTitleBarTitle(const QString& title, const QString& icon = "");


protected:
	void paintEvent(QPaintEvent* event);										// �����¼�
	void mousePressEvent(QMouseEvent* event);						// ����¼�
	void mouseMoveEvent(QMouseEvent* event);						// ����ƶ��¼�
	void mouseReleaseEvent(QMouseEvent* event);					// ����ɿ��¼� , ���� ����ͷ�

public slots:
	void onShowClose(bool);
	void onShowMin(bool);
	void onShowHide(bool);
	void onShowNormal(bool);
	void onShowQuit(bool);
	void onSignalSkinChanged(const QColor& color);

	void onButtonMinClicked();
	void onButtonRestoreClicked();
	void onButtonMaxClicked();
	void onButtonCloseClicked();

protected:
	QPoint m_mousePoint;
	bool m_mousePressed;
	QColor m_colorBackGround;
	QString m_styleName;
	TitleBar* _titleBar;
};
