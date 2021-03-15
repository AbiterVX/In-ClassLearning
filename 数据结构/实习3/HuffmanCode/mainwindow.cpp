#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDragEnterEvent>
#include<QUrl>
#include<QFile>
#include<QTextStream>
#include<QMimeData>
#include<QFileInfo>
#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    FileCompress=new HufumanCompress();

    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(startThread()));

}
void MainWindow::handleResults(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::startThread()
{
    WorkerThread *workThread =new WorkerThread(this);
    connect(workThread,SIGNAL(resultReady(int)),this,SLOT(handleResults(int)));
    connect(workThread,SIGNAL(finished()),workThread,SLOT(deleteLater()));
    workThread->start();
}







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







void MainWindow::on_pushButton_clicked()  //确认
{
     QString FilePath=ui->textEdit->toPlainText();

     ui->progressBar->setValue(0);
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


     if(FileSuffix!="huf")
     {
         FileCompress->Compress(FilePath,FileSuffix);
     }
     else
     {
         FileCompress->DeCompress(FilePath,FileSuffix);
     }

}

void MainWindow::on_pushButton_2_clicked()
{
     ui->textEdit->clear();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("Open File..."),".",
                                                  tr("DOC Files(*.doc *.docx *.huf *.tif)") );
    //QString fileName=QFileDialog::getSaveFileName();
    ui->textEdit->setText(fileName);
}








