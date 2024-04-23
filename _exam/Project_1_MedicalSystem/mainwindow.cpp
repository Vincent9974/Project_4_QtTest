#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QStandardItemModel>
#include <QTableView>
#include <QTableWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QHBoxLayout>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建一个 QTableWidget 实例
    m_tableWidget = new QTableWidget(this);

    m_stackedWidget = new QStackedWidget(this);


    initGrid();

     np = new newProject(this);

    ui->actionExit->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    connect(np, &newProject::projectEntered,
            this, &MainWindow::handleProjectEntered);

    m_remakeDialog = new remakeDialog(this);
    connect(ui->actionRemake, &QAction::triggered,
            this, &MainWindow::hadleRemakeAction);

    connect(ui->actionPackUp, &QAction::triggered,
            this, &MainWindow::hadlePackUpAction);

    m_packUpDialog = new packUpDialog(this);

    m_pictureWidget = new picutreWidget(this);
    m_pictureWidget->resize(this->centralWidget()->width(), this->centralWidget()->height());



    connect(ui->actionLargestView, &QAction::triggered,
            this, &MainWindow::handlePictureView);


    m_stackedWidget->addWidget(m_tableWidget);
    m_stackedWidget->addWidget(m_pictureWidget);

    setCentralWidget(m_stackedWidget);

    QString exeDirPath = QCoreApplication::applicationDirPath();
    QDir imgDir(exeDirPath + "/img");
    QString imgDirPath = imgDir.absolutePath();
    qDebug() << "directory path: " << imgDirPath;

    m_imageFilePath = imgDirPath;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleProjectEntered(const QString &projectName, const QString &filePath, const QString &resolution)
{
    int row = m_tableWidget->rowCount();
    m_tableWidget->insertRow(row);
    qDebug() << row ;

    QString projectID = QString("B70356A5-4FE4-AE12-EBF54232350B");


    QDateTime currentTime = QDateTime::currentDateTime();
    QString currentString = currentTime.toString("yyyy-MM-dd HH:mm:ss");

    // 设置新行的内容
    m_tableWidget->setItem(row, 0, new QTableWidgetItem(projectID));
    m_tableWidget->setItem(row, 1, new QTableWidgetItem(projectName));
    m_tableWidget->setItem(row, 2, new QTableWidgetItem(filePath));
    m_tableWidget->setItem(row, 3, new QTableWidgetItem(resolution));
    m_tableWidget->setItem(row, 4, new QTableWidgetItem(QString("23.1.000")));
    m_tableWidget->setItem(row, 5, new QTableWidgetItem(currentString));
    m_tableWidget->setItem(row, 6, new QTableWidgetItem(QString("暂无")));


    // 将表格视图设置为主窗口的中心部件
    //setCentralWidget(m_tableWidget);
    m_stackedWidget->setCurrentIndex(0);
}

void MainWindow::initGrid()
{

    // 设置行数和列数
    m_tableWidget->setRowCount(1);
    m_tableWidget->setColumnCount(7);

    m_tableWidget->setColumnWidth(0, 300);
    m_tableWidget->setColumnWidth(1, 200);
    m_tableWidget->setColumnWidth(2, 400);
    m_tableWidget->setColumnWidth(3, 200);
    m_tableWidget->setColumnWidth(4, 200);
    m_tableWidget->setColumnWidth(5, 200);
    m_tableWidget->setColumnWidth(6, 200);
    m_tableWidget->setColumnWidth(7, 200);



    // 插入数据
    m_tableWidget->setItem(0, 0, new QTableWidgetItem("工程ID"));
    m_tableWidget->setItem(0, 1, new QTableWidgetItem("工程名称"));
    m_tableWidget->setItem(0, 2, new QTableWidgetItem("路径"));
    m_tableWidget->setItem(0, 3, new QTableWidgetItem("分辨率"));
    m_tableWidget->setItem(0, 4, new QTableWidgetItem("版本"));
    m_tableWidget->setItem(0, 5, new QTableWidgetItem("修改日期"));
    m_tableWidget->setItem(0, 6, new QTableWidgetItem("描述"));


    // 隐藏行标号
    m_tableWidget->verticalHeader()->setVisible(false);
    // 隐藏列标号
    m_tableWidget->horizontalHeader()->setVisible(false);


//    // 将表格视图设置为主窗口的中心部件
    //    setCentralWidget(m_tableWidget);
}

void MainWindow::initPictureList()
{
    loadImagesFromFloder(m_imageFilePath);
}

void MainWindow::loadImagesFromFloder(const QString &folderPath)
{
    QDir directory(folderPath);
    QStringList imageFiles = directory.entryList(QDir::Files);

//    for (auto x : imageFiles)
//    {
//        qDebug() << x;
//    }

    // 创建网格布局
    QGridLayout *layout = new QGridLayout;

    // 设置网格间隙为 0
    layout->setSpacing(0);

    int row = 0;
    int col = 0;

    // 循环遍历图片文件
    foreach (const QString &fileName, imageFiles) {
        // 创建图片标签
        QLabel *imageLabel = new QLabel;
        QPixmap pixmap(folderPath + "/" + fileName);
        imageLabel->setPixmap(pixmap);

        // 将图片标签和文字标签添加到网格布局中
        layout->addWidget(imageLabel, row, col);

        // 更新行列索引
        col++;
        if (col == 5) { // 每排显示5个部件
            col = 0;
            row  +=1;
        }
    }


    m_pictureWidget->setLayout(layout);
}

void MainWindow::hadleRemakeAction()
{
    m_remakeDialog->show();
}

void MainWindow::hadlePackUpAction()
{
    m_packUpDialog->show();
}

void MainWindow::handlePictureView()
{
    initPictureList();
    m_stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_actionNew_triggered()
{
    np->show();
}
