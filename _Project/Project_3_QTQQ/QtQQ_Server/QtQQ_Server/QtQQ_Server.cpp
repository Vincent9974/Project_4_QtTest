#include "QtQQ_Server.h"

#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QFileDialog>

const int gtcpPort = 8888;
const int gudpPort = 6666;

QtQQ_Server::QtQQ_Server(QWidget *parent)
    : QDialog(parent)
	,m_pixPath("")
{
    ui.setupUi(this);


	// 连接到 MySQL 数据库
	if (!connectMySql())
	{
		QMessageBox::warning(NULL,
			QString::fromLocal8Bit("提示"),
			QString::fromLocal8Bit("连接数据库失败!"));
		close();
		return;
	}

	setDepNameMap();
	setStatusMap();
	setOnlineMap();

	initComboBoxData();

	// 查询员工信息
	m_queryInfoModel.setQuery("SELECT * FROM tab_employees");
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置表格为只读模式

	//初始化查询公司群所有员工信息
	m_employeeID = 0;
	m_depID = getCompDepID();
	m_compDepID = m_depID;

	updateTableData();


	//定时刷新数据
	m_timer = new QTimer(this);
	m_timer->setInterval(200);
	m_timer->start();
	connect(m_timer, &QTimer::timeout, this, &QtQQ_Server::onRefresh);

	initTcpSocket();
	initUdpSocket();
}

void QtQQ_Server::initTcpSocket()
{
	m_tcpServer = new TcpServer(gtcpPort);
	m_tcpServer->run();

	//收到tcp客户端发来的信息后进行udp广播
	connect(m_tcpServer,&TcpServer::signalTcpMsgComes,
		this, &QtQQ_Server::onUDPbroadMsg);
}

void QtQQ_Server::initUdpSocket()
{
	m_udpSender = new QUdpSocket(this);
}

void QtQQ_Server::onUDPbroadMsg(QByteArray& btData)
{
	for (quint16 port = gudpPort; port < gudpPort + 200; ++port)
	{
		m_udpSender->writeDatagram(btData, btData.size(), QHostAddress::Broadcast, port);

	}
}


// 连接到 MySQL 数据库
bool QtQQ_Server::connectMySql()
{
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setDatabaseName("qtqq"); // 数据库名称
	db.setHostName("localhost"); // 主机名
	db.setUserName("root"); // 用户名
	db.setPassword("123456"); // 密码
	db.setPort(3306); // 端口号

	if (db.open())
	{
		return true;
	}
	else
	{
		return false;
	}
}

int QtQQ_Server::getCompDepID()
{
	QSqlQuery queryCompDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'")
		.arg(QString::fromLocal8Bit("公司群")));

	// 执行 SQL 查询
	queryCompDepID.exec();

	// 移动查询结果的指针到第一条记录
	queryCompDepID.next();

	// 获取查询结果中第一列的值（即公司部门的 departmentID）并转换为整数类型
	int compDepID = queryCompDepID.value(0).toInt();

	// 返回公司部门的 departmentID
	return compDepID;
}


// 更新表格数据
void QtQQ_Server::updateTableData(int depID, int employeeID)
{
	ui.tableWidget->clear();

	// 根据查询条件获取员工信息
	QString queryStr;
	if (depID && depID != m_compDepID) // 查询部门
	{
		queryStr = QString("SELECT * FROM tab_employees WHERE departmentID = %1").arg(depID);
	}
	else if (employeeID) // 精确查找
	{
		queryStr = QString("SELECT * FROM tab_employees WHERE employeeID = %1").arg(employeeID);
	}
	else // 查询所有
	{
		queryStr = QString("SELECT * FROM tab_employees");
	}


	// 设置查询模型
	m_queryInfoModel.setQuery(queryStr);

	// 获取查询结果的行数和列数
	int rows = m_queryInfoModel.rowCount();
	int columns = m_queryInfoModel.columnCount();

	QModelIndex index; // 模型索引

	// 设置表格行数和列数
	ui.tableWidget->setRowCount(rows);
	ui.tableWidget->setColumnCount(columns);

	// 设置表格列标题
	QStringList headers;
	headers << QStringLiteral("部门")
		<< QStringLiteral("工号")
		<< QStringLiteral("员工姓名")
		<< QStringLiteral("员工签名")
		<< QStringLiteral("员工状态")
		<< QStringLiteral("员工头像")
		<< QStringLiteral("在线状态");
	ui.tableWidget->setHorizontalHeaderLabels(headers);

	// 设置表格列宽自适应
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	// 遍历查询结果，填充表格数据
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			index = m_queryInfoModel.index(i, j); // 获取模型索引
			QString strData = m_queryInfoModel.data(index).toString(); // 获取数据

			// 根据字段名称设置特殊列数据
			QSqlRecord record = m_queryInfoModel.record(i); // 当前记录
			QString strRecordName = record.fieldName(j); // 字段名称


			if (strRecordName == QLatin1String("departmentID"))
			{
				ui.tableWidget->setItem(i, j, new QTableWidgetItem(m_depNameMap.value(strData)));
				continue;
			}
			else if (strRecordName == QLatin1String("status"))
			{
				ui.tableWidget->setItem(i, j, new QTableWidgetItem(m_statusMap.value(strData)));
				continue;
			}
			else if (strRecordName == QLatin1String("online"))
			{
				ui.tableWidget->setItem(i, j, new QTableWidgetItem(m_onlineMap.value(strData)));
				continue;
			}

			ui.tableWidget->setItem(i, j, new QTableWidgetItem(strData));
		}
	}
}

// 设置部门名称映射
void QtQQ_Server::setDepNameMap()
{
	m_depNameMap.insert(QStringLiteral("2001"), QStringLiteral("人事部"));
	m_depNameMap.insert(QStringLiteral("2002"), QStringLiteral("市场部"));
	m_depNameMap.insert(QStringLiteral("2003"), QStringLiteral("研发部"));
}

// 设置状态映射
void QtQQ_Server::setStatusMap()
{
	m_statusMap.insert(QStringLiteral("1"), QStringLiteral("有效"));
	m_statusMap.insert(QStringLiteral("0"), QStringLiteral("无效"));
}

// 设置在线状态映射
void QtQQ_Server::setOnlineMap()
{
	m_onlineMap.insert(QStringLiteral("1"), QStringLiteral("离线"));
	m_onlineMap.insert(QStringLiteral("2"), QStringLiteral("在线"));
	m_onlineMap.insert(QStringLiteral("3"), QStringLiteral("忙碌"));
}

// 初始化下拉框数据
void QtQQ_Server::initComboBoxData()
{
	QString itemText; // 下拉框项文本

	// 获取部门名称列表并设置对应的部门 ID
	QSqlQueryModel queryDepModel;
	queryDepModel.setQuery("SELECT * FROM tab_department");
	int depCounts = queryDepModel.rowCount() - 1; // 部门数量(减去总群)


	for (int i = 0; i < depCounts; i++)
	{
		itemText = ui.employeeDepBox->itemText(i);
		QSqlQuery queryDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'").arg(itemText));
		queryDepID.exec();
		queryDepID.first();

		ui.employeeDepBox->setItemData(i, queryDepID.value(0).toInt());
	}

	// 多一个"公司群" 部门
	for (int i = 0; i < depCounts + 1; i++)
	{
		itemText = ui.departmentBox->itemText(i);
		QSqlQuery queryDepID(QString("SELECT departmentID FROM tab_department WHERE department_name = '%1'").arg(itemText));
		queryDepID.exec();
		queryDepID.first();

		ui.departmentBox->setItemData(i, queryDepID.value(0).toInt());
	}
}


// 定时刷新表格数据
void QtQQ_Server::onRefresh()
{
	updateTableData(m_depID, m_employeeID);
}

// 部门查询按钮点击事件
void QtQQ_Server::on_queryDepartmentBtn_clicked()
{
	ui.queryIDLineEdit->clear();
	m_employeeID = 0;
	m_depID = ui.departmentBox->currentData().toInt();
	updateTableData(m_depID);
}

// 员工查询按钮点击事件
void QtQQ_Server::on_queryIDBtn_clicked()
{
	ui.departmentBox->setCurrentIndex(0);
	m_depID = m_compDepID;

	// 检查员工QQ输入框是否为空
	if (!ui.queryIDLineEdit->text().length())
	{
		QMessageBox::information(this,
			QStringLiteral("提示"),
			QStringLiteral("请输入员工QQ号"));
		ui.queryIDLineEdit->setFocus();
		return;
	}

	// 获取用户输入的员工QQ号
	int employeeID = ui.queryIDLineEdit->text().toInt();

	// 查询员工信息
	QSqlQuery queryInfo(QString("SELECT * FROM tab_employees WHERE employeeID = %1").arg(employeeID));
	queryInfo.exec();
	if (!queryInfo.next())
	{
		QMessageBox::information(this,
			QStringLiteral("提示"),
			QStringLiteral("输入的员工QQ号不存在"));
		ui.queryIDLineEdit->setFocus();
		return;
	}
	else
	{
		m_employeeID = employeeID;
	}

}

void QtQQ_Server::on_logoutBtn_clicked()
{
	ui.queryIDLineEdit->clear(); // 清空员工ID查询框内容
	ui.departmentBox->setCurrentIndex(0); // 将部门下拉框选中项重置为第一项

	// 如果注销员工ID查询框为空，则提示输入员工ID
	if (!ui.logoutIDLineEdit->text().length())
	{
		QMessageBox::information(this,
			QStringLiteral("提示"),
			QStringLiteral("请输入员工ID"));
		ui.logoutIDLineEdit->setFocus();
		return;
	}

	// 获取输入的员工ID
	int employeeID = ui.logoutIDLineEdit->text().toInt();

	// 查询员工信息是否存在，如果不存在则提示输入正确的员工ID
	QSqlQuery queryInfo(QString("SELECT employee_name FROM tab_employees WHERE employeeID = %1").arg(employeeID));
	queryInfo.exec();
	if (!queryInfo.next())
	{
		QMessageBox::information(this,
			QStringLiteral("提示"),
			QStringLiteral("请输入正确的员工ID"));
		ui.logoutIDLineEdit->setFocus();
		return;
	}
	else
	{
		// 注销操作,更新数据库中员工状态为离职状态（status=0）
		QSqlQuery sqlUpdate(QString("UPDATE tab_employees SET status = 0 WHERE employeeID = %1").arg(employeeID));
		sqlUpdate.exec();

		// 获取员工姓名
		QString strName = queryInfo.value(0).toString();

		// 弹出提示消息，显示成功注销的员工姓名和QQ号
		QMessageBox::information(this,
			QStringLiteral("提示"),
			QStringLiteral("员工 %1 的业务QQ:%2 已成功注销")
			.arg(strName)
			.arg(employeeID));

		ui.logoutIDLineEdit->clear(); // 清空注销员工ID查询框内容
	}
}

void QtQQ_Server::on_selectPictureBtn_clicked()
{
	// 获取选择的头像路径 
	m_pixPath = QFileDialog::getOpenFileName(
		this,
		QStringLiteral("选择头像"),
		".",
		"*.png;;*.jpg"
	);


	// 如果未选择头像，则返回 
	if (!m_pixPath.size())
	{
		return;
	}

	// 显示头像并调整大小 
	QPixmap pixmap;
	pixmap.load(m_pixPath);

	// 计算宽度和高度的比例 
	qreal widthRatio = (qreal)ui.headLabel->width() / (qreal)pixmap.width();
	qreal heightRatio = (qreal)ui.headLabel->height() / (qreal)pixmap.height();

	// 根据比例调整大小 
	QSize size(pixmap.width() * widthRatio, pixmap.height() * heightRatio);
	ui.headLabel->setPixmap(pixmap.scaled(size));
}


void QtQQ_Server::on_addBtn_clicked()
{
	// 检查是否输入了员工姓名
	QString strName = ui.nameLineEdit->text();
	if (!strName.size())
	{
		QMessageBox::information(this,
			QStringLiteral("提示"),
			QStringLiteral("请输入员工姓名"));
		ui.nameLineEdit->setFocus();
		return;
	}

	// 检查是否选择了员工头像
	if (!m_pixPath.size())
	{
		QMessageBox::information(this,
			QStringLiteral("提示"),
			QStringLiteral("请选择员工头像路径"));
		return;
	}

	// 向数据库中添加新员工信息
	// 获取员工最大的QQ号
	QSqlQuery maxEmployeeID("SELECT MAX(employeeID) FROM tab_employees");
	maxEmployeeID.exec();
	maxEmployeeID.next();

	int employeeID = maxEmployeeID.value(0).toInt() + 1;

	// 获取员工所属部门ID
	int depID = ui.employeeDepBox->currentData().toInt();

	// 将图片路径中的正斜杠替换为反斜杠形成合法路径
	m_pixPath.replace("/", "\\\\");

	// 执行插入语句
	QSqlQuery insertSql(QString("INSERT INTO tab_employees(departmentID,employeeID,employee_name,picture) \
        VALUES(%1,%2,'%3','%4')")
		.arg(depID)
		.arg(employeeID)
		.arg(strName)
		.arg(m_pixPath));

	insertSql.exec();
	QMessageBox::information(this,
		QStringLiteral("提示"),
		QStringLiteral("添加员工成功"));
	m_pixPath = "";
	ui.nameLineEdit->clear();
	ui.headLabel->setText(QStringLiteral("  员工头像  "));
}
