#include "CommonUtils.h"
#include <QPainter>        // ������ͼ�� QPainter ��ͷ�ļ�
#include <QFile>           // �����ļ������� QFile ��ͷ�ļ�
#include <QWidget>         // ����QWidget���ͷ�ļ�
#include <QApplication>    // ����Ӧ�ó����� QApplication ��ͷ�ļ�
#include <QSettings>       // ���������ļ��� QSettings ��ͷ�ļ�

// CommonUtils ��Ĺ��캯��
CommonUtils::CommonUtils()
{

}

// ��ȡԲ��ͼ��ľ�̬��Ա����
QPixmap CommonUtils::getRoundImage(const QPixmap& src, QPixmap& mask, QSize maskSize)
{
	// ���δָ�����ֳߴ磬��ʹ�����ֵ�ʵ�ʳߴ�
	if (maskSize == QSize(0, 0))
	{
		maskSize = mask.size();
	}
	else
	{
		// ʹ�� scaled ������������ͼ������Ӧָ���ĳߴ�
		mask = mask.scaled(maskSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}

	// ����һ�� QImage ������Ϊ���ͼ��
	QImage resultImage(maskSize, QImage::Format_ARGB32_Premultiplied);

	// ����һ�� QPainter �������ڻ���ͼ��
	QPainter painter(&resultImage);

	// ���û���ģʽΪ CompositionMode_Source
	painter.setCompositionMode(QPainter::CompositionMode_Source);

	// ���͸����ɫ
	painter.fillRect(resultImage.rect(), Qt::transparent);

	// ���û���ģʽΪ CompositionMode_SourceOver
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

	// ��ָ��λ�û�������ͼ��
	painter.drawPixmap(0, 0, mask);

	// ���û���ģʽΪ CompositionMode_SourceIn
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);

	// ��ָ��λ�û���ԭʼͼ��ʹ�����ű��ֳ����
	painter.drawPixmap(0, 0, src.scaled(maskSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

	// �������Ʋ���
	painter.end();

	// �� QImage ת��Ϊ QPixmap�������ؽ��ͼ��
	return QPixmap::fromImage(resultImage);
}

// ������ʽ��ľ�̬��Ա����
void CommonUtils::loadStyleSheet(QWidget* widget, const QString& sheetName)
{
	// ������ʽ���ļ�·��
	QFile file(":/Resources/QSS/" + sheetName + ".css");

	// ����ʽ���ļ�
	file.open(QFile::ReadOnly);

	// ����ļ��򿪳ɹ�
	if (file.isOpen())
	{
		// ����ؼ�ԭ�е���ʽ��
		widget->setStyleSheet("");

		// ��ȡ��ʽ�����ݲ����ø��ؼ�
		QString qsstyleSheet = QLatin1String(file.readAll());
		widget->setStyleSheet(qsstyleSheet);
	}

	// �ر��ļ�
	file.close();
}

// ����Ĭ��Ƥ����ɫ�ľ�̬��Ա����
void CommonUtils::setDefaultSkinColor(const QColor& color)
{
	// ��ȡӦ�ó����Ŀ¼·��
	const QString&& path = QApplication::applicationDirPath() + "/" + QString("tradeprintinfo.ini");

	// ���������ļ�����ʹ�� INI ��ʽ
	QSettings settings(path, QSettings::IniFormat);

	// ����Ĭ��Ƥ����ɫ�� RGB ֵ
	settings.setValue("DefaultSkin/red", color.red());
	settings.setValue("DefaultSkin/green", color.green());
	settings.setValue("DefaultSkin/blue", color.blue());
}

// ��ȡĬ��Ƥ����ɫ�ľ�̬��Ա����
QColor CommonUtils::getDefaultSkinColor()
{
	QColor color;

	// ��ȡ�����ļ�·��
	const QString&& path = QApplication::applicationDirPath() + "/" + QString("tradeprintinfo.ini");

	// ��������ļ������ڣ�������Ĭ��Ƥ����ɫ�����浽�����ļ���
	if (!QFile::exists(path))
	{
		setDefaultSkinColor(QColor(22, 154, 218));
	}

	// ���������ļ�����ʹ�� INI ��ʽ
	QSettings settings(path, QSettings::IniFormat);

	// �������ļ��ж�ȡĬ��Ƥ����ɫ�� RGB ֵ
	color.setRed(settings.value("DefaultSkin/red").toInt());
	color.setGreen(settings.value("DefaultSkin/green").toInt());
	color.setBlue(settings.value("DefaultSkin/blue").toInt());

	// ����Ĭ��Ƥ����ɫ
	return color;
}