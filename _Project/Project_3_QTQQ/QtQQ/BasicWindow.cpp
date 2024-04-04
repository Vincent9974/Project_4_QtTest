#include "BasicWindow.h"
#include "CommonUtils.h"
#include "NotifyManager.h"
#include <QFile>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QMouseEvent>
#include <QDesktopWidget>

BasicWindow::BasicWindow(QWidget *parent)
	: QDialog(parent)
{
	m_colorBackGround = CommonUtils::getDefaultSkinColor();
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground, true);
	connect(NotifyManager::getInstance(),
		SIGNAL(signalSkinChanged(const QColor &)),
		this,
		SLOT(onSignalSkinChanged(const QColor &)));
}

BasicWindow::~BasicWindow()
{
}

void BasicWindow::onSignalSkinChanged(const QColor& color)
{
	m_colorBackGround = color;
	loadStyleSheet(m_styleName);
}

void BasicWindow::setTitleBarTitle(const QString &title, const QString &icon)
{
	_titleBar->setTitleIcon(icon);
	_titleBar->setTitleContent(title);
}


void BasicWindow::initTitleBar(ButtonType buttontype)
{
	_titleBar = new TitleBar(this);
	_titleBar->setButtonType(buttontype);
	_titleBar->move(0, 0);

	connect(_titleBar, SIGNAL(signalButtonMinCliked()), this, SLOT(onButtonMinClicked));
	connect(_titleBar, SIGNAL(signalButtonRestoreCliked()), this, SLOT(onButtonRestoreClicked));
	connect(_titleBar, SIGNAL(signalButtonMaxCliked()), this, SLOT(onButtonMaxClicked));
	connect(_titleBar, SIGNAL(signalButtonCloseCliked()), this, SLOT(onButtonCloseClicked));
}

void BasicWindow::loadStyleSheet(const QString& sheetName)
{
	m_styleName = sheetName;
	QFile file(":/Resources/QSS/" + sheetName + ".css");
	file.open(QFile::ReadOnly);

	if (file.isOpen())
	{
		setStyleSheet("");
		QString qstyleSheet = QLatin1String(file.readAll());

		//��ȡ�û���ǰƤ����ɫ
		QString r = QString::number(m_colorBackGround.red());
		QString g = QString::number(m_colorBackGround.green());
		QString b = QString::number(m_colorBackGround.blue());

		qstyleSheet += QString("QWidget[titleskin=true]\
                        {background-color:rgb(%1,%2,%3);\
                        border-top-left-radius:4px}\
                        QWidget[bottomskin=true]\
                        {border-top:1px solid rgba(%1,%2,%3,100);\
                        background-color:rgba(%1,%2,%3,50);\
                        border-bottom-left-radius:4px;\
                        border-bottom-right-radius:4px;}")
						.arg(r).arg(g).arg(b);
		setStyleSheet(qstyleSheet);
	}
	file.close();
}

//����ͼ
void BasicWindow::initBackGroundColor()
{
	QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BasicWindow::paintEvent(QPaintEvent* event)
{
	initBackGroundColor();		 // �ڻ��ƴ�������֮ǰ����ʼ��������ɫ
	QDialog::paintEvent(event); // ���û���� paintEvent ���������ƴ��ڵ����ಿ��
}

QPixmap BasicWindow::getRoundImage(const QPixmap &src, QPixmap &mask, QSize maskSize)
{
	if (maskSize == QSize(0, 0))
	{
		maskSize = mask.size();
	}
	else
	{
		// ���ָ���� maskSize���� mask ����Ϊָ����С
		mask = mask.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}

	// ����һ���հ׵� QImage ��Ϊ���ͼ��
	QImage resultImage(maskSize, QImage::Format_ARGB32_Premultiplied);

	// ����һ�� QPainter ���������� resultImage �ϻ���ͼ��
	QPainter painter(&resultImage);
	painter.setCompositionMode(QPainter::CompositionMode_Source);	// ���û���ģʽΪԴģʽ
	painter.fillRect(resultImage.rect(), Qt::transparent);			// �������ͼ�����Ϊ͸��
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);	// ���û���ģʽΪԴ����
	painter.drawPixmap(0, 0, mask);									// ���� mask ͼ��
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);	// ���û���ģʽΪԴ��
	painter.drawPixmap(0, 0, src.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // �� mask �����ڻ��� src ͼ��
	painter.end();	// �������Ʋ���

	// �����ƺõ� resultImage ת��Ϊ QPixmap��������
	return QPixmap::fromImage(resultImage);

}

void BasicWindow::onShowClose(bool)
{
	close();
}


void BasicWindow::onShowMin(bool)
{
	showMinimized();
}


void BasicWindow::onShowHide(bool)
{
	hide();
}


void BasicWindow::onShowNormal(bool)
{
	show();
	activateWindow();
}


void BasicWindow::onShowQuit(bool)
{
	QApplication::quit();
}

void BasicWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (m_mousePressed && (event->buttons() & Qt::LeftButton))
	{
		// move()���������ƶ����ڵ�λ�ã�����Ϊ�����ƶ����λ��
		move(event->globalPos() - m_mousePoint);
		event->accept(); // ���ܸ��¼�����ֹ�����ݵ�������
	}
}

void BasicWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		// pos()������������¼�����ʱ�ڴ����ڵ�λ�ã�globalPos()��������¼�����ʱ��ȫ��λ��
		// ���������ڴ��ڵ�λ�ñ�����m_mousePoint��
		m_mousePressed = true;
		m_mousePoint = event->globalPos() - pos();
		event->accept(); // ���ܸ��¼�����ֹ�����ݵ�������
	}
}

void BasicWindow::mouseReleaseEvent(QMouseEvent *event)
{
	m_mousePressed = false;
}


void BasicWindow::onButtonMinClicked()
{
	// �жϴ��ڵ������Ƿ�Ϊ���ߴ���
	// ����ǹ��ߴ��ڣ������ش���
	// ������ǹ��ߴ��ڣ�����С������

	if (Qt::Tool == (windowFlags() & Qt::Tool))
	{
		hide(); //���ش���
	}
	else
	{
		showMinimized(); //��С������
	}
	
}


void BasicWindow::onButtonRestoreClicked()
{
	QPoint windowPos; // ����λ��
	QSize windowSize; // ���ڴ�С

	//���ñ����������getInfo������ȡ���ڻ�ԭ��Ϣ
	_titleBar->getRestoreInfo(windowPos, windowSize);

	// ʹ��setGeometry�������ô��ڵ�λ�úʹ�С
	setGeometry(QRect(windowPos, windowSize));
}

void BasicWindow::onButtonCloseClicked()
{
	close();
}

void BasicWindow::onButtonMaxClicked()
{
	// ���洰�ڻ�ԭ��Ϣ�������ڵ�λ�úʹ�С
	_titleBar->saveRestoreInfo(pos(), QSize(width(), height()));

	// ��ȡ����Ŀ�������
	QRect desktopRect = QApplication::desktop()->availableGeometry();


	// ����ʵ�ʵĴ��ڴ�С�����ǵ����ڱ߿�Ĵ�С
	QRect factRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3,
		desktopRect.width() + 6, desktopRect.height() + 6);

	// ����������Ϊȫ��״̬
	setGeometry(factRect);
}

