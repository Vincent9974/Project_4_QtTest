#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
#include <QSpinBox>
#include <QLabel>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 菜单
    QMenu *editMenu = ui->menubar->addMenu("编辑(&E)");

    QAction *action_copy = editMenu->addAction(QIcon("copy.png"),QString("复制(&C)"));
    action_copy->setShortcut(QKeySequence("Ctrl + C"));

    ui->toolBar->addAction(action_copy);

    QActionGroup *group = new QActionGroup(this);
    QAction *action_L = group->addAction("左对齐(&L)");
    QAction *action_R = group->addAction("右对齐(&R)");
    QAction *action_C = group->addAction("居中对齐(&C)");
    QAction *action_J = group->addAction("两端对齐(&J)");

    action_L->setCheckable(true);
    action_R->setCheckable(true);
    action_C->setCheckable(true);
    action_J->setCheckable(true);

    editMenu->addSeparator(); // 菜单栏添加分隔线;
    editMenu->addAction(action_L);
    editMenu->addAction(action_R);
    editMenu->addAction(action_C);
    editMenu->addAction(action_J);

    //工具栏添加部件
    QToolButton *toolBtn = new QToolButton(this);
    toolBtn->setText("颜色");

    QMenu* colorMenu = new QMenu(this);
    colorMenu->addAction("红色");
    colorMenu->addAction("绿色");
    toolBtn->setMenu(colorMenu);

    //弹出式菜单
    toolBtn->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolBar->addWidget(toolBtn);

    QSpinBox *spinbox = new QSpinBox(this);
    ui->toolBar->addWidget(spinbox);

    //状态栏显示临时信息
    ui->statusbar->showMessage(QString("欢迎..."), 3000);

    //状态栏添加永久信息
    QLabel *tag = new QLabel("Vincent");
    ui->statusbar->addPermanentWidget(tag);
}

MainWindow::~MainWindow()
{
    delete ui;
}

