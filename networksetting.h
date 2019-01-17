#ifndef NETWORKSETTING_H
#define NETWORKSETTING_H

#include <QObject>
#include <QWidget>
#include "QComboBox"
#include "QLineEdit"
#include "QLabel"
#include "QPushButton"

class NetWorkSetting : public QWidget
{
    Q_OBJECT
public:
    explicit NetWorkSetting(QWidget *parent = 0);
    void networkTest();
    /*void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);*/
signals:

public slots:
private:
    QPushButton *buttonMin;
    QPushButton *buttonClose;
    bool isMousePressed = false;
    QPoint MousePressPos;
    QLabel *titleBar;
};

#endif // NETWORKSETTING_H
