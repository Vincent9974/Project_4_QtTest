#include "SkinWindow.h"
#include "QClickLabel.h"
#include "NotifyManager.h"

SkinWindow::SkinWindow(QWidget *parent)
	: BasicWindow(parent)
{
	ui.setupUi(this);
	loadStyleSheet("SkinWindow");
	setAttribute(Qt::WA_DeleteOnClose);
	initControl();
}

SkinWindow::~SkinWindow()
{
}

void SkinWindow::initControl()
{
	// 初始化颜色列表
	QList<QColor> colorList = {
		QColor(22,154,218), QColor(40,138,221), QColor(49,166,107), QColor(218,67,68),
		QColor(177,99,158), QColor(107,81,92), QColor(89,92,160), QColor(21,156,199),
		QColor(79,169,172), QColor(155,183,154), QColor(128,77,77), QColor(240,188,189),
	};

	// 生成颜色选择区域
	for (int row = 0; row < 3; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			// 创建可点击的标签
			QClickLabel* label = new QClickLabel(this);
			label->setCursor(Qt::PointingHandCursor);

			// 使用 C++11 中的 lambda 表达式连接点击事件
			connect(label, &QClickLabel::clicked, [row, column, colorList]() {
				NotifyManager::getInstance()->notifyOtherWindowChangeSkin(colorList.at(row * 4 + column));
			});


			label->setFixedSize(84, 84); // 设置标签固定大小

			// 设置背景颜色
			QPalette palette;
			palette.setColor(QPalette::Background, colorList.at(row * 4 + column));
			label->setAutoFillBackground(true);
			label->setPalette(palette);

			ui.gridLayout->addWidget(label, row, column);
		}
	}

	// 最小化和关闭按钮的连接
	connect(ui.sysmin, SIGNAL(clicked(bool)), this, SLOT(onShowMin(bool)));
	connect(ui.sysclose, SIGNAL(clicked()), this, SLOT(onShowClose()));
}

void SkinWindow::onShowClose()
{
	close();
}