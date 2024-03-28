#pragma once
#include <QPixmap>
#include <QSize>
#include <QProxyStyle>


class CustomProxyStyle : public QProxyStyle
{
	// ���캯�������ø�����
	CustomProxyStyle(QObject* parent)
	{
		setParent(parent);
	}

	// ��д������ʽԪ�صķ���
	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption* option,
		QPainter* painter, const QWidget* widget = nullptr) const
	{
		// ������Ƶ��ǽ����Ԫ��
		if (PE_FrameFocusRect == element)
		{
			// ������ Windows Ĭ�ϵĽ����ֱ�ӷ���
			return;
		}

		else
		{
			// ����������ʽԪ��
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}

};


class CommonUtils
{
public:
	CommonUtils();
public:
	// ��ȡԲ��ͼ��
	static QPixmap getRoundImage(const QPixmap& src, QPixmap& mask, QSize maskSize = QSize(0, 0));

	// ������ʽ��
	static void loadStyleSheet(QWidget* widget, const QString& sheetName);

	// ����Ĭ��Ƥ����ɫ
	static void setDefaultSkinColor(const QColor& color);

	// ��ȡĬ��Ƥ����ɫ
	static QColor getDefaultSkinColor();
};

