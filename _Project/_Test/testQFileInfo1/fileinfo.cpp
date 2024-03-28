#include "fileinfo.h"
#include "ui_fileinfo.h"
#include <QFileDialog>
#include <QDateTime>

FileInfo::FileInfo(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileInfo)
{
    ui->setupUi(this);
    setWindowTitle("文件信息");
}

FileInfo::~FileInfo()
{
    delete ui;
}

void FileInfo::getFileInfo(QString &fileName)
{
    QFileInfo info(fileName);

    qint64 size = info.size(); //文件大小
    QDateTime createTime = info.created(); //文件创建时间
    QDateTime lastMTime = info.lastModified();
    QDateTime lastRTime = info.lastRead();

    //文件属性信息
    bool bIsDir = info.isDir();
    bool bIsFile = info.isFile();
    bool bIsSymLink = info.isSymLink();
    bool bIsHidden = info.isHidden();

    bool bIsReadable = info.isReadable();
    bool bIsWritable = info.isWritable();
    bool bIsExcutable = info.isExecutable();

    ui->fileSizeLineEdit->setText(QString::number(size));
    ui->fileCreateLineEdit->setText(createTime.toString());
    ui->fileModifyLineEdit->setText(lastMTime.toString());
    ui->fileReadLineEdit->setText(lastRTime.toString());

    ui->isDirChekBox->setChecked(bIsDir);
    ui->isFileCheckBox->setChecked(bIsFile);
    ui->isSymLinkCheckBox->setChecked(bIsSymLink);
    ui->isHiddenCheckBox_2->setChecked(bIsHidden);
    ui->isWriteableCheckBox->setChecked(bIsWritable);
    ui->isReadableCheckBox->setChecked(bIsReadable);
    ui->isExecutableCheckBox->setChecked(bIsExcutable);

}


void FileInfo::on_browseFileBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "打开文件",
                                                    ".",
                                                    "file(*)");

//    QString path = QFileDialog::getExistingDirectory(this,
//                                                     "选择目录",
//                                                     ".");

//    ui->fileNameLineEdit_2->setText(path);
//    getFileInfo(path);

        ui->fileNameLineEdit_2->setText(fileName);
        getFileInfo(fileName);
}
