#include "filetransferthread.h"
#include "QTcpSocket"
#include "QFile"
#include "QTextStream"
#include "QByteArray"
#include "QDataStream"
#include "QFileDialog"
#include "QHostAddress"
fileTransferThread::fileTransferThread(QObject *parent, QString filePath, int socketId)
    :QThread(parent), fileName(filePath), socketId(socketId)
{
    qDebug()<<"new File Thread";

    this->filePath = filePath;
    loadSize = 4*1024;
    totalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;
}

void fileTransferThread::run()
{
    qDebug()<<"thread run";

    bytesWritten = 0;
    tcpClient = new QTcpSocket;
    connect(tcpClient,SIGNAL(connected()),this,SLOT(startTransfer()),Qt::BlockingQueuedConnection);
    connect(tcpClient,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProcess(qint64)),Qt::BlockingQueuedConnection);
    connect(tcpClient,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)), Qt::DirectConnection);
    connect(tcpClient, &QTcpSocket::disconnected, tcpClient, &QTcpSocket::deleteLater);
    tcpClient->abort();
    tcpClient->connectToHost(QHostAddress::LocalHost, 56789);
    int count = 0;
    while(!tcpClient->waitForConnected())
    {
        qDebug()<<tcpClient->errorString();
        qDebug()<<"reconnecting...";
        tcpClient->connectToHost(QHostAddress::LocalHost, 56789);
        count++;
        if(count>=5)
        {
            qDebug()<<"failed to connect server!";
            tcpClient->close();
            this->quit();
            this->wait();
            return;
        }
    }
    this->exec();
}

void fileTransferThread::startTransfer()
{
    qDebug()<<"Start to Transfer";
    qDebug()<<"socketId = "<<socketId;
    localFile = new QFile(filePath);
    if(!localFile->open(QFile::ReadOnly))
    {
        qDebug()<<"Open File Error!";
        //emit transferError("Open File Error!");
        this->quit();
        this->wait();
        return;
    }
    totalBytes = localFile->size();
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_5_7);
    QString currentFileName = filePath.right(filePath.size() - filePath.lastIndexOf('/')-1);
    sendOut<<qint64(0)<<qint64(0)<<currentFileName;
    qDebug()<<"currentFileName = "<<currentFileName;
    totalBytes+= outBlock.size();
    sendOut.device()->seek(0);
    sendOut<<totalBytes<<qint64(outBlock.size()-sizeof(qint64)*2);
    bytesToWrite = totalBytes - tcpClient->write(outBlock);
    outBlock.resize(0);
    qDebug()<<"header send out.";
}

void fileTransferThread::updateClientProcess(qint64 numsBytes)
{
    qDebug()<<"update CLient Progress";
    bytesWritten += (int)numsBytes;
    if(bytesWritten >0)
    {
        outBlock = localFile->read(qMin(bytesToWrite, loadSize));
        bytesToWrite -= tcpClient->write(outBlock);
        outBlock.resize(0);
        qDebug()<<"content send out.";
    }
    else
    {
        localFile->close();
    }
    emit updateProgress(totalBytes, bytesWritten, socketId);
    if(bytesWritten == totalBytes)
    {
        localFile->close();
        this->quit();
        qDebug()<<"file receive complete.";
    }
}

void fileTransferThread::displayError(QAbstractSocket::SocketError) //显示错误
{
    qDebug() << tcpClient->errorString();
    emit transferError(tcpClient->errorString());
}
