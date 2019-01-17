#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent)
{
}

MyLabel::~MyLabel()
{

}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit clicked();
    }
    QLabel::mousePressEvent(event);
    event->accept();
}

void MyLabel::enterEvent(QEvent *event)
{
    QLabel::enterEvent(event);
    this->setPixmap(hoverPic);
}

void MyLabel::leaveEvent(QEvent *event)
{
    QLabel::leaveEvent(event);
    this->setPixmap(normalPic);
}

void MyLabel::setEnterPic(QPixmap &src)
{
    hoverPic = src;
}

void MyLabel::setLeavePic(QPixmap &src)
{
    normalPic = src;
}
