#pragma once
#include <QPixmap>
#include <QSize>
#include <QProxyStyle>


class CustomProxyStyle : public QProxyStyle
{
	// 构造函数，设置父对象
	CustomProxyStyle(QObject* parent)
	{
		setParent(parent);
	}

	// 重写绘制样式元素的方法
	virtual void drawPrimitive(PrimitiveElement element, const QStyleOption* option,
		QPainter* painter, const QWidget* widget = nullptr) const
	{
		// 如果绘制的是焦点框元素
		if (PE_FrameFocusRect == element)
		{
			// 不绘制 Windows 默认的焦点框，直接返回
			return;
		}

		else
		{
			// 绘制其他样式元素
			QProxyStyle::drawPrimitive(element, option, painter, widget);
		}
	}

};


class CommonUtils
{
public:
	CommonUtils();
public:
	// 获取圆形图像
	static QPixmap getRoundImage(const QPixmap& src, QPixmap& mask, QSize maskSize = QSize(0, 0));

	// 加载样式表
	static void loadStyleSheet(QWidget* widget, const QString& sheetName);

	// 设置默认皮肤颜色
	static void setDefaultSkinColor(const QColor& color);

	// 获取默认皮肤颜色
	static QColor getDefaultSkinColor();
};

