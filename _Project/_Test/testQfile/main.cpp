#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QDataStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("Hello.txt");
    if (file.open(QIODevice::ReadOnly))
    {
        char buffer[100];
        qint32 n = file.readLine(buffer,sizeof(buffer));
        if( n != -1)
        {
            qDebug() << "长度:" << n
                     << "内容:" << buffer
                     << endl;
            file.close();
        }
        else
        {
            qDebug() << file.errorString();
        }
    }

    double dPI = 3.1415926;
    int age = 13;
    QFile dataFile;
    dataFile.setFileName("data.txt");
    if(dataFile.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&dataFile);
//        out.setRealNumberPrecision(3);
//        out.setFieldWidth(10);
//        out.setFieldAlignment(QTextStream::AlignRight);

        out << QString("PI:") << dPI;
    }


    QFile binFile("info.bat");
    if(binFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QDataStream out1(&binFile);
        out1 << QString("贾玲");

        binFile.close();
    }
    else
    {
        qDebug() << binFile.errorString();
    }




    return a.exec();
}
