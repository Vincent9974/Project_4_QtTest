#include "CommonUtils.h"
#include <QPainter>        // 包含绘图类 QPainter 的头文件
#include <QFile>           // 包含文件操作类 QFile 的头文件
#include <QWidget>         // 包含QWidget类的头文件
#include <QApplication>    // 包含应用程序类 QApplication 的头文件
#include <QSettings>       // 包含配置文件类 QSettings 的头文件

// CommonUtils 类的构造函数
CommonUtils::CommonUtils()
{

}

// 获取圆形图像的静态成员函数
QPixmap CommonUtils::getRoundImage(const QPixmap& src, QPixmap& mask, QSize maskSize)
{
	// 如果未指定遮罩尺寸，则使用遮罩的实际尺寸
	if (maskSize == QSize(0, 0))
	{
		maskSize = mask.size();
	}
	else
	{
		// 使用 scaled 方法缩放遮罩图像以适应指定的尺寸
		mask = mask.scaled(maskSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}

	// 创建一个 QImage 对象作为结果图像
	QImage resultImage(maskSize, QImage::Format_ARGB32_Premultiplied);

	// 创建一个 QPainter 对象，用于绘制图像
	QPainter painter(&resultImage);

	// 设置绘制模式为 CompositionMode_Source
	painter.setCompositionMode(QPainter::CompositionMode_Source);

	// 填充透明颜色
	painter.fillRect(resultImage.rect(), Qt::transparent);

	// 设置绘制模式为 CompositionMode_SourceOver
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

	// 在指定位置绘制遮罩图像
	painter.drawPixmap(0, 0, mask);

	// 设置绘制模式为 CompositionMode_SourceIn
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

	// 在指定位置绘制原始图像，使用缩放保持长宽比
	painter.drawPixmap(0, 0, src.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

	// 结束绘制操作
	painter.end();

	// 将 QImage 转换为 QPixmap，并返回结果图像
	return QPixmap::fromImage(resultImage);
}

// 加载样式表的静态成员函数
void CommonUtils::loadStyleSheet(QWidget* widget, const QString& sheetName)
{
	// 构造样式表文件路径
	QFile file(":/Resources/QSS/" + sheetName + ".css");

	// 打开样式表文件
	file.open(QFile::ReadOnly);

	// 如果文件打开成功
	if (file.isOpen())
	{
		// 清除控件原有的样式表
		widget->setStyleSheet("");

		// 读取样式表内容并设置给控件
		QString qsstyleSheet = QLatin1String(file.readAll());
		widget->setStyleSheet(qsstyleSheet);
	}

	// 关闭文件
	file.close();
}

// 设置默认皮肤颜色的静态成员函数
void CommonUtils::setDefaultSkinColor(const QColor& color)
{
	// 获取应用程序的目录路径
	const QString&& path = QApplication::applicationDirPath() + "/" + QString("tradeprintinfo.ini");

	// 创建配置文件对象，使用 INI 格式
	QSettings settings(path, QSettings::IniFormat);

	// 设置默认皮肤颜色的 RGB 值
	settings.setValue("DefaultSkin/red", color.red());
	settings.setValue("DefaultSkin/green", color.green());
	settings.setValue("DefaultSkin/blue", color.blue());
}

// 获取默认皮肤颜色的静态成员函数
QColor CommonUtils::getDefaultSkinColor()
{
	QColor color;

	// 获取配置文件路径
	const QString&& path = QApplication::applicationDirPath() + "/" + QString("tradeprintinfo.ini");

	// 如果配置文件不存在，则设置默认皮肤颜色并保存到配置文件中
	if (!QFile::exists(path))
	{
		setDefaultSkinColor(QColor(22, 154, 218));
	}

	// 创建配置文件对象，使用 INI 格式
	QSettings settings(path, QSettings::IniFormat);

	// 从配置文件中读取默认皮肤颜色的 RGB 值
	color.setRed(settings.value("DefaultSkin/red").toInt());
	color.setGreen(settings.value("DefaultSkin/green").toInt());
	color.setBlue(settings.value("DefaultSkin/blue").toInt());

	// 返回默认皮肤颜色
	return color;
}