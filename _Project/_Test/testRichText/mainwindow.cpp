#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextFrame>
#include <QDebug>
#include <QFileDialog>
#include <QUrl>
#include <QImageReader>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 获取文档对象
    QTextDocument *document = ui->textEdit->document();

    //获取根框架
    QTextFrame *rootFrame = document->rootFrame();

    //文档框架格式
    QTextFrameFormat format;
    format.setBorderBrush(Qt::red); //边框颜色
    format.setBorder(3);

    //文档框架设置格式
    rootFrame->setFrameFormat(format);

    //设置文本格式
    QTextFrameFormat frameFormat;
    frameFormat.setBackground(Qt::lightGray);
    frameFormat.setMargin(10);
    frameFormat.setPadding(15);
    frameFormat.setBorder(2);
    frameFormat.setBorderStyle(QTextFrameFormat::BorderStyle_DotDash);

    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertFrame(frameFormat);

    QAction *action_textframe = new QAction("框架",this);
    connect(action_textframe, &QAction::triggered,
            this, &MainWindow::showTextFrame);
    ui->toolBar->addAction(action_textframe);

    QAction *action_textblock = new QAction("文本块", this);
    connect(action_textblock, &QAction::triggered,
            this, &MainWindow::showTextBlock);
    ui->toolBar->addAction(action_textblock);

    QAction *action_textFont = new QAction("字体",this);
    action_textFont->setCheckable(true);
    connect(action_textFont,&QAction::triggered,
            this, &MainWindow::showTextFont);
    ui->toolBar->addAction(action_textFont);

    QAction* action_textTable = new QAction("表格",this);
    QAction* action_textList = new QAction("列表",this);
    QAction* action_textImage = new QAction("图片",this);


    connect(action_textTable, &QAction::triggered,
            this, &MainWindow::insertTable);

    connect(action_textList, &QAction::triggered,
            this, &MainWindow::insertList);

    connect(action_textImage, &QAction::triggered,
            this, &MainWindow::insertImage);


    ui->toolBar->addAction(action_textTable);
    ui->toolBar->addAction(action_textList);
    ui->toolBar->addAction(action_textImage);

    m_sLighter = new MySyntaxHighlighter(ui->textEdit->document());

    QAction *action_textfind = new QAction("查找", this);
    connect(action_textfind, &QAction::triggered,
            this, &MainWindow::textFind);
    ui->toolBar->addAction(action_textfind);

    m_findDialog = new QDialog(this); //查找对话框
    m_lineEdit = new QLineEdit(m_findDialog); //查找输入框
    QPushButton *btn = new QPushButton(m_findDialog);
    btn->setText("查找下一个");
    connect(btn,&QPushButton::clicked,
            this,&MainWindow::textNext);
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_lineEdit);
    layout->addWidget(btn);
    m_findDialog->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTextFrame()
{


    // 获取文档对象
    QTextDocument *document = ui->textEdit->document();

    // 获取根框架
    QTextFrame *frame = document->rootFrame();


    QTextFrame::iterator it;
    for(it = frame->begin(); !(it.atEnd()); ++it)
    {
        // 获取当前框架指针
        QTextFrame *childFrame = it.currentFrame();

        //获取当前文本快
        QTextBlock childBlock = it.currentBlock();
        if(childFrame)
            qDebug() << "frame";
        else if (childBlock.isValid())
            qDebug() << "block:" << childBlock.text();

    }
}

void MainWindow::showTextBlock()
{
    QTextDocument *document = ui->textEdit->document();
    QTextBlock block = document->firstBlock();

    for(int i= 0; i < document->blockCount(); ++i)
    {
        //输出文本块的信息
        qDebug() << QString("Block%1,firstBlock:%2,length%3,content%4")
                    .arg(i)
                    .arg(block.firstLineNumber())
                    .arg(block.length())
                    .arg(block.text());
        block = block.next();
    }
}

void MainWindow::showTextFont(bool checked)
{
    if(checked)
    {
        QTextCursor cursor = ui->textEdit->textCursor();

        //文本块格式
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignHCenter);
        cursor.insertBlock(blockFormat);

        QTextCharFormat charFormat;
        charFormat.setBackground(Qt::lightGray);
        charFormat.setForeground(Qt::blue);
        charFormat.setFont(QFont(QString("宋体"),12,QFont::Bold,true));
        charFormat.setFontUnderline(true);

        cursor.setCharFormat(charFormat);
        cursor.insertText("lol");
    }
}

void MainWindow::insertTable()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTableFormat format;
    format.setCellSpacing(2);
    format.setCellPadding(10);
    cursor.insertTable(3,3,format);
}

void MainWindow::insertList()
{
    QTextListFormat format;
    format.setStyle(QTextListFormat::ListDecimal); //数字编号
    ui->textEdit->textCursor().insertList(format);
}

void MainWindow::insertImage()
{
    QString filepath = QFileDialog::getOpenFileName(this,
                                 "选择图片",
                                 ".",
                                 "JPEG(*.jpg *.jepg);;"
                                 "GIF(*.gif);;"
                                 "PNG(*.png)");
    QUrl url(QString("file://%1").arg(filepath));
    QImage image = QImageReader(filepath).read();

    QTextDocument* document = ui->textEdit->document();
    document->addResource(QTextDocument::ImageResource,
                          url,QVariant(image));

    QTextCursor cursor = ui->textEdit->textCursor();
    QTextImageFormat imgFormat;
    imgFormat.setWidth(image.width());
    imgFormat.setHeight(image.height());
    imgFormat.setName(url.toString());
    cursor.insertImage(imgFormat);
}

void MainWindow::textFind()
{
    m_findDialog->show();
}

void MainWindow::textNext()
{
    QString strFind = m_lineEdit->text();
    bool isFind = ui->textEdit->find(strFind,QTextDocument::FindBackward);
    if(isFind)
    {
        qDebug() << QString("row:%1   ncloumn:%2")
                    .arg(ui->textEdit->textCursor().blockNumber())
                    .arg(ui->textEdit->textCursor().columnNumber());
    }
}

