#include "eventfilter.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QEvent>
#include <QMouseEvent>

EventFilter::EventFilter(QWidget *parent , Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle(QString("事件过滤"));

    // 创建图片标签和状态标签
    m_label1 = new QLabel;
    m_label2 = new QLabel;
    m_label3 = new QLabel;
    m_stateLabel = new QLabel(QString("鼠标按下标志"));
    m_stateLabel->setAlignment(Qt::AlignHCenter);

    // 加载图片
    m_image1.load("fly1.png");
    m_image2.load("fly2.png");
    m_image3.load("fly3.png");

    // 设置图片标签的图片
    m_label1->setPixmap(QPixmap::fromImage(m_image1));
    m_label2->setPixmap(QPixmap::fromImage(m_image2));
    m_label3->setPixmap(QPixmap::fromImage(m_image3));

    // 创建水平布局和垂直布局
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(m_label1);
    layout->addWidget(m_label2);
    layout->addWidget(m_label3);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(layout);
    mainLayout->addWidget(m_stateLabel);

    // 调整窗口大小
    resize(m_image2.width() * 3, m_image2.height() * 2);

    // 给图片标签安装事件过滤器，并指定整个窗体为监视事件的对象
    m_label1->installEventFilter(this);
    m_label2->installEventFilter(this);
    m_label3->installEventFilter(this);
}

EventFilter::~EventFilter()
{
}

bool EventFilter::eventFilter(QObject *watched, QEvent *event)
{
    QMatrix matrix;
    QImage tmpImg;

    // 缩放图片
    matrix.scale(2, 2);
    //matrix.scale(0.5, 0.5);

    // 如果触发事件的对象是 m_label1
    if (watched == m_label1)
    {
        // 鼠标按下事件处理
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->buttons() & Qt::LeftButton)
                m_stateLabel->setText(QString("左键按下图片1"));
            if (mouseEvent->buttons() & Qt::MidButton)
                m_stateLabel->setText(QString("中键按下图片1"));
            if (mouseEvent->buttons() & Qt::RightButton)
                m_stateLabel->setText(QString("右键按下图片1"));

            tmpImg = m_image1.transformed(matrix);
            m_label1->setPixmap(QPixmap::fromImage(tmpImg));
        }
        // 鼠标释放事件，恢复图片大小
        if (event->type() == QEvent::MouseButtonRelease)
        {
            m_stateLabel->setText(QString("鼠标释放图片1"));
            m_label1->setPixmap(QPixmap::fromImage(m_image1));
        }
    }
    else if (watched == m_label2)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->buttons() & Qt::LeftButton)
                m_stateLabel->setText(QString("左键按下图片2"));
            if (mouseEvent->buttons() & Qt::MidButton)
                m_stateLabel->setText(QString("中键按下图片2"));
            if (mouseEvent->buttons() & Qt::RightButton)
                m_stateLabel->setText(QString("右键按下图片2"));

            tmpImg = m_image2.transformed(matrix);
            m_label2->setPixmap(QPixmap::fromImage(tmpImg));
        }
        // 释放鼠标事件，恢复图片大小
        if (event->type() == QEvent::MouseButtonRelease)
        {
            m_stateLabel->setText(QString("鼠标释放图片2"));
            m_label2->setPixmap(QPixmap::fromImage(m_image2));
        }
    }
    else if (watched == m_label3)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->buttons() & Qt::LeftButton)
                m_stateLabel->setText(QString("左键按下图片3"));
            if (mouseEvent->buttons() & Qt::MidButton)
                m_stateLabel->setText(QString("中键按下图片3"));
            if (mouseEvent->buttons() & Qt::RightButton)
                m_stateLabel->setText(QString("右键按下图片3"));

            tmpImg = m_image3.transformed(matrix);
            m_label3->setPixmap(QPixmap::fromImage(tmpImg));
        }
        // 释放鼠标事件，恢复图片大小
        if (event->type() == QEvent::MouseButtonRelease)
        {
            m_stateLabel->setText(QString("鼠标释放图片3"));
            m_label3->setPixmap(QPixmap::fromImage(m_image3));
        }
    }

    // 事件交给上层对话框进行处理
    return QDialog::eventFilter(watched, event);
}

