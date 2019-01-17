#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "QLabel"
#include "QPushButton"
#include "QListWidget"
#include "QProgressBar"
#include "QMutex"
#include "QMutexLocker"

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
signals:
public slots:
    void startToTransfer();
    void updateProgressStatus(qint64, qint64, int);
    void refreshProgressBarListView();
private:
    QPushButton *chooseFileButton;
    QListWidget *listView;
    QMap<int, QProgressBar *> progressBarMap;
    mutable QMutex mutex;
};

#endif // WIDGET_H
