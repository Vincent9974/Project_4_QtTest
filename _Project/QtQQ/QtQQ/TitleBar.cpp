#include "TitleBar.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QFile>

#define BUTTON_HEIGHT 27 //按钮高度
#define BUTTON_WIDTH  27 //按钮宽度
#define TITLE_HEIGHT  27 //标题栏高度


TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
	,m_isPressed(false)
	,m_buttonType(MIN_BUTTON)

{
	initControl();
	initConnections();
	loadStyleSheet("Title");

}

TitleBar::~TitleBar()
{

}

void TitleBar::initControl()
{
	m_pIcon = new QLabel(this);
	m_pTitleContent = new QLabel(this);

	m_pButtonMin = new QPushButton(this);
	m_pButtonRestore = new QPushButton(this);
	m_pButtonMax = new QPushButton(this);
	m_pButtonClose = new QPushButton(this);

	//按钮设置固定大小
	m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));
	m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));
	m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));
	m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));

	//设置对象名
	m_pTitleContent->setObjectName("TitleContent");
	m_pButtonMin->setObjectName("ButtonMin");
	m_pButtonRestore->setObjectName("ButtonRestore");
	m_pButtonMax->setObjectName("ButtonMax");
	m_pButtonClose->setObjectName("ButtonClose");

	//设置布局
	QHBoxLayout* myLayout = new QHBoxLayout(this);
	myLayout->addWidget(m_pIcon);
	myLayout->addWidget(m_pTitleContent);

	myLayout->addWidget(m_pButtonMin);
	myLayout->addWidget(m_pButtonRestore);
	myLayout->addWidget(m_pButtonMax);
	myLayout->addWidget(m_pButtonClose);

	myLayout->setContentsMargins(5,0,0,0); //设置布局的间隙
	myLayout->setSpacing(0);   //设置部件中的间隙

	m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	setFixedHeight(TITLE_HEIGHT);
	setWindowFlags(Qt::FramelessWindowHint);  //无边框
}

void TitleBar::initConnections()
{
	connect(m_pButtonMin,SIGNAL(clicked()),this,SLOT(onButtonMinClicked()));
	connect(m_pButtonRestore,SIGNAL(clicked()),this,SLOT(onButtonRestoreClicked()));
	connect(m_pButtonMax,SIGNAL(clicked()),this,SLOT(onButtonMaxClicked()));
	connect(m_pButtonClose,SIGNAL(clicked()),this,SLOT(onButtonCloseClicked()));
}


//设置标题栏图标
void TitleBar::setTitleIcon(const QString& filePath)
{
	QPixmap titleIcon(filePath);
	m_pIcon->setFixedSize(titleIcon.size());
	m_pIcon->setPixmap(titleIcon);
}

// 设置标题栏内容
void TitleBar::setTitleContent(const QString& titleContent)
{
	m_pTitleContent->setText(titleContent);
	m_titleContent = titleContent;
}

//设置标题栏的长度
void TitleBar::setTitleWidth(int width)
{
	setFixedWidth(width);
}

//设置标题栏按钮类型
void TitleBar::setButtonType(ButtonType buttontype)
{
	m_buttonType = buttontype;
	switch (buttontype)
	{
	case MIN_BUTTON:
	{
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(false);
	}
	break;
	case MIN_MAX_BUTTON:
	{
		m_pButtonRestore->setVisible(false);
	}
	break;
	case ONLY_CLOSE_BUTTON:
	{
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(false);
		m_pButtonMin->setVisible(false);
	}
	break;
	default:
		break;
	}
}

//保存窗口最大化前窗口的位置及大小
void TitleBar::saveRestoreInfo(const QPoint& point, const QSize& size)
{
	m_restorePos = point;
	m_restoreSize = size;
}

//获取窗口最大化前窗口的位置及大小
void TitleBar::getRestoreInfo(QPoint& point, QSize& size)
{
	point = m_restorePos;
	size = m_restoreSize;
}


//绘制标题栏
void TitleBar::paintEvent(QPaintEvent *event)
{
	// 设置背景色
	QPainter painter(this);
	QPainterPath pathBack;
	pathBack.setFillRule(Qt::WindingFill);// 设置填充规则为WindingFill（即“奇偶填充”）

	// 添加圆角矩形到绘图路径
	pathBack.addRoundedRect(QRect(0,0,width(),height()),3,3);// 添加一个圆角矩形到绘图路径中

	// 设置渲染提示为平滑图像变换
	painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

	// 当窗口最大化或还原后，窗口长度改变，标题栏相应做出改变
	// parentWidget()返回父部件
	if (width() != parentWidget()->width())
	{
		setFixedWidth(parentWidget()->width());
	}
}

//双击响应事件,双击标题栏实现最大化最小化操作
void TitleBar::mouseDoubleClickedEvent(QMouseEvent* event)
{
	//只有存在最大化,最小化按钮才有效
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		if (m_pButtonMax->isVisible())
		{
			onButtonMaxClicked();
		}
		else
		{
			onButtonRestoreClicked();
		}
	}
	return QWidget::mouseDoubleClickEvent(event);
}

//通过鼠标按下,移动,释放事件实现拖动标题栏达到移动窗口效果
void TitleBar::mousePressEvent(QMouseEvent* event)
{
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		//在窗口最大化时候停止移动
		if (m_pButtonMax->isVisible())
		{
			m_isPressed = true;
			m_startMovePos = event->globalPos(); //globalPos()返回事件发生时鼠标的全局位置
		}
	}
	else 
	{
		m_isPressed = true;
		m_startMovePos = event->globalPos();
	}
	return QWidget::mousePressEvent(event);
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
	if (m_isPressed)
	{
		QPoint movePoint = event->globalPos() - m_startMovePos;
		QPoint widgetPos = parentWidget()->pos();
		m_startMovePos = event->globalPos();
		parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
	}

	return QWidget::mouseMoveEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}

//加载样式表
void TitleBar::loadStyleSheet(const QString& sheetName)
{
	QFile file(":/Resources/QSS/" + sheetName + ".css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());
		setStyleSheet(styleSheet);
	}
}

void TitleBar::onButtonMinClicked()
{
	emit signalButtonCloseClicked();
}


void TitleBar::onButtonRestoreClicked()
{
	m_pButtonRestore->setVisible(false);
	m_pButtonMax->setVisible(true);
	emit signalButtonRestoreClicked();
}

void TitleBar::onButtonMaxClicked()
{
	m_pButtonMax->setVisible(false);
	m_pButtonRestore->setVisible(true);
	emit signalButtonMaxClicked();
}

void TitleBar::onButtonCloseClicked()
{
	emit signalButtonCloseClicked();
}