// 包含头文件
#include "WindowManager.h"
#include "TalkWindow.h"
#include "TalkWindowItem.h"
#include <QSqlQueryModel>

// 使用全局静态对象创建WindowManager的单例
Q_GLOBAL_STATIC(WindowManager, theInstance)

// WindowManager类的构造函数
WindowManager::WindowManager()
	: QObject(nullptr),
	m_talkwindowshell(nullptr)
{
}

// WindowManager类的析构函数
WindowManager::~WindowManager()
{
}

// 查找窗口名称对应的窗口部件
QWidget* WindowManager::findWindowName(const QString& qsWindowName)
{
	// 检查窗口名称是否存在于窗口映射中
	if (m_windowMap.contains(qsWindowName))
	{
		// 返回窗口映射中与窗口名称对应的窗口部件
		return m_windowMap.value(qsWindowName);
	}

	// 若未找到，则返回空指针
	return nullptr;
}

// 删除窗口名称对应的窗口部件
void WindowManager::deleteWindowName(const QString& qsWindowName)
{
	// 从窗口映射中移除窗口名称对应的窗口部件
	m_windowMap.remove(qsWindowName);
}

// 添加窗口名称和对应的窗口部件到窗口映射中
void WindowManager::addWindowName(const QString& qsWindowName, QWidget* qWidget)
{
	// 若窗口名称在窗口映射中不存在，则添加到窗口映射中
	if (!m_windowMap.contains(qsWindowName))
	{
		m_windowMap.insert(qsWindowName, qWidget);
	}
}

// 获取WindowManager的单例实例
WindowManager* WindowManager::getInstance()
{
	return theInstance(); // 返回WindowManager的单例对象
}

TalkWindowShell * WindowManager::getTalkWindowShell()
{
	return m_talkwindowshell;
}

// 添加新的对话窗口
void WindowManager::addNewTalkWindow(const QString& uid /*, GroupType groupType, const QString& strPeople*/)
{
	// 如果对话窗口外壳为空，则创建新的对话窗口外壳
	if (m_talkwindowshell == nullptr)
	{
		m_talkwindowshell = new TalkWindowShell;

		// 监听对话窗口外壳的销毁事件，将其置空
		connect(m_talkwindowshell, &TalkWindowShell::destroyed, [this](QObject* obj)
		{
			m_talkwindowshell = nullptr;
		});
	}

	// 查找对应于uid的窗口部件
	QWidget* widget = findWindowName(uid);

	// 如果未找到对应的窗口部件，则创建新的对话窗口和对话窗口项
	if (!widget)
	{
		TalkWindow* talkwindow = new TalkWindow(m_talkwindowshell, uid/*, groupType*/);
		TalkWindowItem* talkwindowItem = new TalkWindowItem(talkwindow);

		//判断是群聊还是单聊
		QSqlQueryModel sqlDepModel;
		QString strSql = QString("SELECT department_name, sign FROM tab_department WHERE departmentID = %1").arg(uid);
		sqlDepModel.setQuery(strSql);
		int rows = sqlDepModel.rowCount();

		QString strWindowName, strMsgLabel;

		if (rows == 0) //单聊
		{
			QString sql = QString("SELECT employee_name, employee_sign FROM tab_employees WHERE employeeID = %1").arg(uid);
			sqlDepModel.setQuery(sql);

		}
		QModelIndex indexDepIndex, signIndex;
		indexDepIndex = sqlDepModel.index(0, 0); //0行0列
		signIndex = sqlDepModel.index(0, 1); //0行1列
		strWindowName = sqlDepModel.data(signIndex).toString();
		strMsgLabel = sqlDepModel.data(indexDepIndex).toString();

		talkwindow->setWindowName(strWindowName); //窗口名称
		talkwindowItem->setMsgLabelContent(strMsgLabel); //左侧联系人文本显示

		m_talkwindowshell->addTalkWindow(talkwindow, talkwindowItem, uid);

		/*
		// 根据不同的群组类型设置对话窗口的标题和消息标签内容
		switch (groupType)
		{
		case COMPANY:
			talkwindow->setWindowName(QStringLiteral("公司群"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("公司公告"));
			break;
		case PERSONELGROUP:
			talkwindow->setWindowName(QStringLiteral("人事部"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("私聊消息"));
			break;
		case MARKETGROUP:
			talkwindow->setWindowName(QStringLiteral("市场部"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("市场信息"));
			break;
		case DEVELOPMENTGROUP:
			talkwindow->setWindowName(QStringLiteral("研发部"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("技术讨论"));
			break;
		case PTOP:
			// 对于点对点聊天，设置窗口名称为空字符串，消息标签内容为strPeople
			talkwindow->setWindowName(QStringLiteral(""));
			talkwindowItem->setMsgLabelContent(strPeople);
			break;
		default:
			break;
		}
		*/

		// 将对话窗口添加到对话窗口外壳中
	
	}
	else
	{
		// 左侧聊天列表设置为选中
		QListWidgetItem* item = m_talkwindowshell->getTalkWindowItemMap().key(widget);
		item->setSelected(true);

		//设置右侧当前聊天窗口
		m_talkwindowshell->setCurrentWidget(widget);
	}

	// 显示对话窗口外壳并激活
	m_talkwindowshell->show();
	m_talkwindowshell->activateWindow();
}
