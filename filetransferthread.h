#ifndef FILETRANSFERTHREAD_H
#define FILETRANSFERTHREAD_H

#include <QWidget>
#include "QObject"
#include "QThread"
#include "QTcpSocket"
#include "QFile"

class fileTransferThread : public QThread
{
    Q_OBJECT
public:
    explicit fileTransferThread(QObject *parent, QString filePath, int socketId);
protected:
    void run();
private:
    QTcpSocket *tcpClient;
    QString filePath;
    QFile *localFile;
    qint64 totalBytes;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    qint64 loadSize;
    QString fileName;
    QByteArray outBlock;
    int socketId;
public slots:
    void startTransfer();
    void updateClientProcess(qint64 numsBytes);
    void displayError(QAbstractSocket::SocketError);
signals:
    void updateProgress(qint64 totalBytes, qint64 bytesWritten, int socketId);
    void transferError(QString errorString);
};

#endif // FILETRANSFERTHREAD_H
