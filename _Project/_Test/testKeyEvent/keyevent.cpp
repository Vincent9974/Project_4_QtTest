#include "keyevent.h"
#include "ui_keyevent.h"
#include <QPainter>
#include <QPen>
#include <QKeyEvent>

KeyEvent::KeyEvent(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KeyEvent)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus); //一定要加，否则没反应
    setWindowTitle(QString("键盘Event"));
    setAutoFillBackground(true);
    setFixedSize(512, 256);
    m_width = size().width();
    m_height = size().height();

    m_pix = new QPixmap(m_width, m_height);
    m_pix->fill(Qt::white);

    m_image.load("tiger.png");

    m_startX = 100;
    m_startY = 100;
    m_step = 20;
    drawPix();
}

KeyEvent::~KeyEvent()
{
    delete ui;
}

void KeyEvent::drawPix()
{
    // 填充画布为白色
    m_pix->fill(Qt::white);

    // 创建绘图对象
    QPainter painter(this);
    QPen pen(Qt::DotLine);

    // 开始在 m_pix 上绘图
    painter.begin(m_pix);
    painter.setPen(pen);

    // 按照步长绘制纵向网格线
    for (int i = m_step; i < m_width; i += m_step) {
        painter.drawLine(QPoint(i, 0), QPoint(i, m_height));
    }

    // 按照步长绘制水平网格线
    for(int j = m_step; j < m_width; j += m_step)
    {
        painter.drawLine(QPoint(0, j),QPoint(m_width, j));
    }

    // 结束绘制
    painter.end();

    // 开始在 m_pix 上绘制图片
    painter.begin(m_pix);
    painter.drawImage(QPoint(m_startX, m_startY), m_image);
    painter.end();
}

void KeyEvent::keyPressEvent(QKeyEvent *event)
{
    // 按下Ctrl键，每次移动1个像素
    if (event->modifiers() & Qt::ControlModifier)
    {
        if (event->key() == Qt::Key_Left)
        {
            m_startX = (m_startX - 1) < 0 ? m_startX : m_startX - 1;
        }
        if (event->key() == Qt::Key_Right)
        {
            m_startX = (m_startX + 1 + m_image.width()) > m_width ? m_startX : m_startX + 1;
        }
        if (event->key() == Qt::Key_Up)
        {
            m_startY = (m_startY - 1) < 0 ? m_startY : m_startY - 1;
        }
        if (event->key() == Qt::Key_Down)
        {
            m_startY = (m_startY + 1 + m_image.height()) > m_height ? m_startY : m_startY + 1;
        }
    }
    else // 没有按下Ctrl键，每次移动一个步长
    {
        // 调整图标左上角位置到网格顶点上
        m_startX = m_startX - m_startX % m_step;
        m_startY = m_startY - m_startY % m_step;

        if (event->key() == Qt::Key_Left)
        {
            m_startX = (m_startX - m_step) < 0 ? m_startX : m_startX - m_step;
        }
        if (event->key() == Qt::Key_Right)
        {
            m_startX = (m_startX + m_step + m_image.width()) > m_width ? m_startX : m_startX + m_step;
        }
        if (event->key() == Qt::Key_Up)
        {
            m_startY = (m_startY - m_step) < 0 ? m_startY : m_startY - m_step;
        }
        if (event->key() == Qt::Key_Down)
        {
            m_startY = (m_startY + m_step + m_image.height()) > m_height ? m_startY : m_startY + m_step;
        }
    }
    drawPix();
    update();
}

void KeyEvent::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.drawPixmap(QPoint(0,0),*m_pix);
    painter.end();
}

