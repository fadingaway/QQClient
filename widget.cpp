#include "widget.h"
#include "QLabel"
#include "QVBoxLayout"
#include "QPixmap"
#include "QMouseEvent"
#include "QPoint"
#include "filetransferthread.h"
#include "QHBoxLayout"
#include "QDebug"
#include "QPainter"
#include "QPainterPath"
#include "QPropertyAnimation"
#include "QStringList"
#include "QFileDialog"
static int socketId = 0;
Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    chooseFileButton = new QPushButton(this);
    chooseFileButton->setText("Choose File");
    connect(chooseFileButton, &QPushButton::clicked, this, &Widget::startToTransfer);

    listView = new QListWidget(this);
    mainLayout->addWidget(chooseFileButton);
    mainLayout->addWidget(listView);

    this->setLayout(mainLayout);
}

void Widget::startToTransfer()
{
    qDebug()<<"startToTransfer";
    QStringList fileList = QFileDialog::getOpenFileNames(this);
    if(fileList.size() >0)
    {
        for(int i = 0; i<fileList.size(); i++)
        {
            QString filename = fileList.at(i);
            qDebug()<<"filename = "<<filename;
            fileTransferThread *thread = new fileTransferThread(this, filename, socketId++);
            connect(thread, &fileTransferThread::updateProgress, this, updateProgressStatus);
            connect(thread, &QThread::finished, thread, &QThread::deleteLater);
            thread->start();
        }
    }
    else
        return;
}

void Widget::updateProgressStatus(qint64 totalSize, qint64 receivedSize, int socketId)
{
    qDebug()<<"----------start------------";
    qDebug()<<"update Progress Bar";
    qDebug()<<"socketId = "<<socketId;
    qDebug()<<"progressbarMap size = "<<progressBarMap.size();
    qDebug()<<"totalSize = "<<totalSize;
    qDebug()<<"receivedSize = "<<receivedSize;
    mutex.lock();
    if(progressBarMap.size() ==0 ||!progressBarMap.contains(socketId))
    {
        qDebug()<<"     create new ProgressBar";
        QProgressBar *progressBar = new QProgressBar(listView);
        progressBar->setMaximum(totalSize);
        progressBar->setValue(receivedSize);
        QListWidgetItem *item = new QListWidgetItem(listView);
        item->setSizeHint(progressBar->size());
        listView->setItemWidget(item, progressBar);
        progressBarMap.insert(socketId, progressBar);
    }
    else
    {
        if(progressBarMap.contains(socketId))
        {
            qDebug()<<"     update exists progress bar";
            QProgressBar *progressBar = progressBarMap.value(socketId);
            progressBar->setMaximum(totalSize);
            progressBar->setValue(receivedSize);
            progressBarMap.remove(socketId);
            progressBarMap.insert(socketId, progressBar);

//            if(totalSize == receivedSize)
//            {
//                progressBarMap.remove(socketId);
//                refreshProgressBarListView();
//            }
        }
    }
    mutex.unlock();
    qDebug()<<"----------end------------";
}

void Widget::refreshProgressBarListView()
{
    qDebug()<<"refresh Progress Bar ListView";
    listView->clear();
    qDebug()<<"progressBarMap Size = "<<progressBarMap.size();
    if(progressBarMap.size()>0)
    {
        for(QMap<int, QProgressBar *>::iterator it = progressBarMap.begin();
            it != progressBarMap.end();
            it++)
        {
            QListWidgetItem *item = new QListWidgetItem(listView);
            item->setSizeHint(it.value()->size());
            listView->setItemWidget(item, it.value());
        }
    }
}
