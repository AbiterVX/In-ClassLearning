#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDragEnterEvent>
#include<QUrl>
#include<QFile>
#include<QTextStream>
#include<QMimeData>
#include<QFileInfo>
#include<QFileDialog>
#include<QMutex>
#include<QWaitCondition>


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    FileCompress=new PressPicture();

    /*ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(startThread()));*/

}
/*void MainWindow::handleResults(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::startThread()
{
    WorkerThread *workThread =new WorkerThread(this);
    connect(workThread,SIGNAL(resultReady(int)),this,SLOT(handleResults(int)));
    connect(workThread,SIGNAL(finished()),workThread,SLOT(deleteLater()));
    workThread->start();
}*/


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();

    }
    else
    {
        event->ignore();
    }
}
void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData =event->mimeData();
    if(mimeData->hasUrls())
    {
        QList<QUrl>urlList=mimeData->urls();
        QString fileName =urlList.at(0).toLocalFile();
        if(!fileName.isEmpty())
        {
            QFile file(fileName);
            if(!file.open(QIODevice::ReadOnly))
            {
                return;
            }
            QTextStream in(&file);
            ui->textEdit->setText((in.readAll()));
        }

    }
}

void MainWindow::on_pushButton_clicked()
{


    QString FilePath=ui->textEdit->toPlainText();

    //ui->progressBar->setValue(0);
    if(FilePath=="")
    {
        return;
    }
    QString FileSuffix;
    QString FileName;
    QFileInfo fileinfo(FilePath);
    FileName=fileinfo.fileName();

    FileSuffix=fileinfo.suffix();

    QString Cut=FilePath.mid(0,8);
    if(Cut=="file:///")
    {
        FilePath=FilePath.mid(8,FilePath.size()-8);
    }

    QString CompressFilePath=FilePath.mid(0,FilePath.size()-FileSuffix.size()-1);


    if(FileSuffix=="bmp"){
        ui->textEdit_2->clear();
        ui->textEdit_2->append("Begin and wait...");      
        qApp->processEvents();

        CompressFilePath+="Press.txt";
        FileCompress->ReadBitMap(FilePath);
        FileCompress->Compress(CompressFilePath);

        ui->textEdit_2->append("Finish!");
    }
    else if(FileSuffix=="txt"){
        ui->textEdit_2->clear();
        ui->textEdit_2->append("Begin and wait...");
        qApp->processEvents();

        CompressFilePath+="UnPress.bmp";
        FileCompress->UnCompress(FilePath,CompressFilePath);

        ui->textEdit_2->append("Finish!");
    }


}
void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    ui->textEdit_2->clear();
}
void MainWindow::on_pushButton_3_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File..."),".",
                                                  tr("Files(*.bmp *.txt)") );
    ui->textEdit->setText(fileName);
}




