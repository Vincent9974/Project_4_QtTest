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

		//获取用户当前皮肤颜色
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

//背景图
void BasicWindow::initBackGroundColor()
{
	QStyleOption opt;
	opt.init(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BasicWindow::paintEvent(QPaintEvent* event)
{
	initBackGroundColor();		 // 在绘制窗口内容之前，初始化背景颜色
	QDialog::paintEvent(event); // 调用基类的 paintEvent 函数，绘制窗口的其余部分
}

QPixmap BasicWindow::getRoundImage(const QPixmap &src, QPixmap &mask, QSize maskSize)
{
	if (maskSize == QSize(0, 0))
	{
		maskSize = mask.size();
	}
	else
	{
		// 如果指定了 maskSize，则将 mask 调整为指定大小
		mask = mask.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}

	// 创建一个空白的 QImage 作为结果图像
	QImage resultImage(maskSize, QImage::Format_ARGB32_Premultiplied);

	// 创建一个 QPainter 对象，用于在 resultImage 上绘制图像
	QPainter painter(&resultImage);
	painter.setCompositionMode(QPainter::CompositionMode_Source);	// 设置绘制模式为源模式
	painter.fillRect(resultImage.rect(), Qt::transparent);			// 填充整个图像矩形为透明
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);	// 设置绘制模式为源覆盖
	painter.drawPixmap(0, 0, mask);									// 绘制 mask 图像
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);	// 设置绘制模式为源中
	painter.drawPixmap(0, 0, src.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation)); // 在 mask 区域内绘制 src 图像
	painter.end();	// 结束绘制操作

	// 将绘制好的 resultImage 转换为 QPixmap，并返回
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
		// move()函数用于移动窗口的位置，参数为窗口移动后的位置
		move(event->globalPos() - m_mousePoint);
		event->accept(); // 接受该事件，防止它传递到父窗口
	}
}

void BasicWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		// pos()函数返回鼠标事件发生时在窗口内的位置，globalPos()返回鼠标事件发生时的全局位置
		// 将鼠标相对于窗口的位置保存在m_mousePoint中
		m_mousePressed = true;
		m_mousePoint = event->globalPos() - pos();
		event->accept(); // 接受该事件，防止它传递到父窗口
	}
}

void BasicWindow::mouseReleaseEvent(QMouseEvent *event)
{
	m_mousePressed = false;
}


void BasicWindow::onButtonMinClicked()
{
	// 判断窗口的类型是否为工具窗口
	// 如果是工具窗口，则隐藏窗口
	// 如果不是工具窗口，则最小化窗口

	if (Qt::Tool == (windowFlags() & Qt::Tool))
	{
		hide(); //隐藏窗口
	}
	else
	{
		showMinimized(); //最小化窗口
	}
	
}


void BasicWindow::onButtonRestoreClicked()
{
	QPoint windowPos; // 窗口位置
	QSize windowSize; // 窗口大小

	//调用标题栏对象的getInfo函数获取窗口还原信息
	_titleBar->getRestoreInfo(windowPos, windowSize);

	// 使用setGeometry函数设置窗口的位置和大小
	setGeometry(QRect(windowPos, windowSize));
}

void BasicWindow::onButtonCloseClicked()
{
	close();
}

void BasicWindow::onButtonMaxClicked()
{
	// 保存窗口还原信息，即窗口的位置和大小
	_titleBar->saveRestoreInfo(pos(), QSize(width(), height()));

	// 获取桌面的可用区域
	QRect desktopRect = QApplication::desktop()->availableGeometry();


	// 计算实际的窗口大小，考虑到窗口边框的大小
	QRect factRect = QRect(desktopRect.x() - 3, desktopRect.y() - 3,
		desktopRect.width() + 6, desktopRect.height() + 6);

	// 将窗口设置为全屏状态
	setGeometry(factRect);
}

