#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>

enum ButtonType
{
	MIN_BUTTON = 0, //��С�����رհ�ť
	MIN_MAX_BUTTON, //��С��,��󻯼��رհ�ť
	ONLY_CLOSE_BUTTON //ֻ�йرհ�ť
};

//�Զ��������
class TitleBar : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget *parent);
	~TitleBar();

	void setTitleIcon(const QString &filePath);		    //���ñ�����ͼ��
	void setTitleContent(const QString &titleContent);   //���ñ���������
	void setTitleWidth(int width);				  //���ñ���������
	void setButtonType(ButtonType buttonType);   //���ñ�������ť����

	//����,��ȡ�������ǰ���ڵ�λ�õĴ�С
	void saveRestoreInfo(const QPoint& point, const QSize& size);
	void getRestoreInfo( QPoint& point,  QSize& size);

private:
	void paintEvent(QPaintEvent *event);				//��ͼ�¼�
	void mouseDoubleClickedEvent(QMouseEvent* event);	//���˫���¼�
	void mousePressEvent(QMouseEvent* event);			//��갴���¼�
	void mouseMoveEvent(QMouseEvent* event);			//����ƶ��¼�
	void mouseReleaseEvent(QMouseEvent* event);			//����ɿ��¼�

	void initControl();			//��ʼ���ؼ�
	void initConnections();		//��ʼ���ź���۵�����
	void loadStyleSheet(const QString& sheetName); //������ʽ��

signals:
	//��������ť���ʱ�������ź�
	void signalButtonMinClicked();      //��С����ť
	void signalButtonRestoreClicked();  //��󻯻�ԭ��ť
	void signalButtonMaxClicked();      //��󻯰�ť
	void signalButtonCloseClicked();    //�رհ�ť

private:
	//��ť��Ӧ�Ĳ�
	void onButtonMinClicked();
	void onButtonRestoreClicked();
	void onButtonMaxClicked();
	void onButtonCloseClicked();

private:
	QLabel *m_pIcon;				//������ͼ��
	QLabel *m_pTitleContent;		//����������
	QPushButton *m_pButtonMin;		//��С����ť
	QPushButton *m_pButtonRestore;	//��󻯻�ԭ��ť
	QPushButton *m_pButtonMax;
	QPushButton *m_pButtonClose;	//�رհ�ť

	//��󻯻�ԭ��ť�ı���(λ��,��С)
	QPoint m_restorePos;
	QSize  m_restoreSize;

	//�ƶ����ڵı���
	bool m_isPressed;
	QPoint m_startMovePos;

	QString m_titleContent;
	ButtonType m_buttonType;
};