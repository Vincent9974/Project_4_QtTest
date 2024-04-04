// ����ͷ�ļ�
#include "WindowManager.h"
#include "TalkWindow.h"
#include "TalkWindowItem.h"
#include <QSqlQueryModel>

// ʹ��ȫ�־�̬���󴴽�WindowManager�ĵ���
Q_GLOBAL_STATIC(WindowManager, theInstance)

// WindowManager��Ĺ��캯��
WindowManager::WindowManager()
	: QObject(nullptr),
	m_talkwindowshell(nullptr)
{
}

// WindowManager�����������
WindowManager::~WindowManager()
{
}

// ���Ҵ������ƶ�Ӧ�Ĵ��ڲ���
QWidget* WindowManager::findWindowName(const QString& qsWindowName)
{
	// ��鴰�������Ƿ�����ڴ���ӳ����
	if (m_windowMap.contains(qsWindowName))
	{
		// ���ش���ӳ�����봰�����ƶ�Ӧ�Ĵ��ڲ���
		return m_windowMap.value(qsWindowName);
	}

	// ��δ�ҵ����򷵻ؿ�ָ��
	return nullptr;
}

// ɾ���������ƶ�Ӧ�Ĵ��ڲ���
void WindowManager::deleteWindowName(const QString& qsWindowName)
{
	// �Ӵ���ӳ�����Ƴ��������ƶ�Ӧ�Ĵ��ڲ���
	m_windowMap.remove(qsWindowName);
}

// ��Ӵ������ƺͶ�Ӧ�Ĵ��ڲ���������ӳ����
void WindowManager::addWindowName(const QString& qsWindowName, QWidget* qWidget)
{
	// �����������ڴ���ӳ���в����ڣ�����ӵ�����ӳ����
	if (!m_windowMap.contains(qsWindowName))
	{
		m_windowMap.insert(qsWindowName, qWidget);
	}
}

// ��ȡWindowManager�ĵ���ʵ��
WindowManager* WindowManager::getInstance()
{
	return theInstance(); // ����WindowManager�ĵ�������
}

TalkWindowShell * WindowManager::getTalkWindowShell()
{
	return m_talkwindowshell;
}

// ����µĶԻ�����
void WindowManager::addNewTalkWindow(const QString& uid /*, GroupType groupType, const QString& strPeople*/)
{
	// ����Ի��������Ϊ�գ��򴴽��µĶԻ��������
	if (m_talkwindowshell == nullptr)
	{
		m_talkwindowshell = new TalkWindowShell;

		// �����Ի�������ǵ������¼��������ÿ�
		connect(m_talkwindowshell, &TalkWindowShell::destroyed, [this](QObject* obj)
		{
			m_talkwindowshell = nullptr;
		});
	}

	// ���Ҷ�Ӧ��uid�Ĵ��ڲ���
	QWidget* widget = findWindowName(uid);

	// ���δ�ҵ���Ӧ�Ĵ��ڲ������򴴽��µĶԻ����ںͶԻ�������
	if (!widget)
	{
		TalkWindow* talkwindow = new TalkWindow(m_talkwindowshell, uid/*, groupType*/);
		TalkWindowItem* talkwindowItem = new TalkWindowItem(talkwindow);

		//�ж���Ⱥ�Ļ��ǵ���
		QSqlQueryModel sqlDepModel;
		QString strSql = QString("SELECT department_name, sign FROM tab_department WHERE departmentID = %1").arg(uid);
		sqlDepModel.setQuery(strSql);
		int rows = sqlDepModel.rowCount();

		QString strWindowName, strMsgLabel;

		if (rows == 0) //����
		{
			QString sql = QString("SELECT employee_name, employee_sign FROM tab_employees WHERE employeeID = %1").arg(uid);
			sqlDepModel.setQuery(sql);

		}
		QModelIndex indexDepIndex, signIndex;
		indexDepIndex = sqlDepModel.index(0, 0); //0��0��
		signIndex = sqlDepModel.index(0, 1); //0��1��
		strWindowName = sqlDepModel.data(signIndex).toString();
		strMsgLabel = sqlDepModel.data(indexDepIndex).toString();

		talkwindow->setWindowName(strWindowName); //��������
		talkwindowItem->setMsgLabelContent(strMsgLabel); //�����ϵ���ı���ʾ

		m_talkwindowshell->addTalkWindow(talkwindow, talkwindowItem, uid);

		/*
		// ���ݲ�ͬ��Ⱥ���������öԻ����ڵı������Ϣ��ǩ����
		switch (groupType)
		{
		case COMPANY:
			talkwindow->setWindowName(QStringLiteral("��˾Ⱥ"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("��˾����"));
			break;
		case PERSONELGROUP:
			talkwindow->setWindowName(QStringLiteral("���²�"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("˽����Ϣ"));
			break;
		case MARKETGROUP:
			talkwindow->setWindowName(QStringLiteral("�г���"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("�г���Ϣ"));
			break;
		case DEVELOPMENTGROUP:
			talkwindow->setWindowName(QStringLiteral("�з���"));
			talkwindowItem->setMsgLabelContent(QStringLiteral("��������"));
			break;
		case PTOP:
			// ���ڵ�Ե����죬���ô�������Ϊ���ַ�������Ϣ��ǩ����ΪstrPeople
			talkwindow->setWindowName(QStringLiteral(""));
			talkwindowItem->setMsgLabelContent(strPeople);
			break;
		default:
			break;
		}
		*/

		// ���Ի�������ӵ��Ի����������
	
	}
	else
	{
		// ��������б�����Ϊѡ��
		QListWidgetItem* item = m_talkwindowshell->getTalkWindowItemMap().key(widget);
		item->setSelected(true);

		//�����Ҳ൱ǰ���촰��
		m_talkwindowshell->setCurrentWidget(widget);
	}

	// ��ʾ�Ի�������ǲ�����
	m_talkwindowshell->show();
	m_talkwindowshell->activateWindow();
}
