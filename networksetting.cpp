#include "networksetting.h"
#include "QGridLayout"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QGraphicsDropShadowEffect"
#include "QDebug"
#include "QPoint"
#include "QMouseEvent"
#include "QLabel"
#include "QDebug"

NetWorkSetting::NetWorkSetting(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(483,350);
    this->setStyleSheet("background-color:black;");

    titleBar = new QLabel(this);
    titleBar->setFixedSize(431, 50);
    titleBar->setStyleSheet("background-color:rgb(40,166,215);"
                         "border-radius:3px;");
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(15);
    effect->setOffset(0,-1);
    titleBar->setGraphicsEffect(effect);
    titleBar->setContentsMargins(0,0,0,0);

    QVBoxLayout *mainLayout = new QVBoxLayout;



    QHBoxLayout *titleLayout = new QHBoxLayout;
    buttonMin = new QPushButton;
    buttonMin->setFlat(true);
    buttonMin->setFixedSize(25,25);
    buttonMin->setStyleSheet("QPushButton{border-image:url(:/Image/min.png)} "
                             "QPushButton:hover{background-color:#00BFFF;}"
                             "QPushButton:pressed{background-color:#009ACD;}"
                             "QToolTip{background-color:white;font-family:微软雅黑;}");
    connect(buttonMin, &QPushButton::clicked, this, &NetWorkSetting::showMinimized);

    buttonClose = new QPushButton;
    buttonClose->setFlat(true);
    buttonClose->setFixedSize(25,25);
    buttonClose->setStyleSheet("QPushButton{border-image:url(:/Image/exit.png)} "
                               "QPushButton:hover{background-color:#00BFFF;}"
                               "QPushButton:pressed{background-color:#009ACD;}"
                               "QToolTip{background-color:white;font-family:微软雅黑;}");
    connect(buttonClose, &QPushButton::clicked, this, &NetWorkSetting::close);

    titleLayout->addSpacing(350);
    titleLayout->addWidget(buttonMin,0, Qt::AlignRight|Qt::AlignTop);
    titleLayout->addWidget(buttonClose,0, Qt::AlignRight|Qt::AlignTop);
    titleBar->setLayout(titleLayout);

    //center content
    QLabel *content = new QLabel(this);
    content->setFixedSize(431,245);
    content->setStyleSheet("QLabel{background-color:rgb(234,242,248);"
                           "border-left:1px solid rgb(152,159,175);"
                                            "border-right:1px solid rgb(152,159,175);"
                                            "font-family:微软雅黑;"
                                            "font-size:9pt;}"
                           "QLineEdit{background-color:white;}"
                           "QComboBox{background-color:white;}");
    QGridLayout *gridLayout = new QGridLayout;

    gridLayout->setVerticalSpacing(10);
    gridLayout->setColumnMinimumWidth(0, 40);

    //row 1
    QLabel *labelNetworkSetting = new QLabel(tr("网络设置"),this);
    labelNetworkSetting->setStyleSheet("border-style:none;");
    gridLayout->addWidget(labelNetworkSetting,1,0,1,10, Qt::AlignLeft|Qt::AlignTop);

    //row 2
    QLabel *labelType = new QLabel(tr("类型:"),this);
    labelType->setStyleSheet("border-style:none;");
    QComboBox *comboType = new QComboBox(this);
    comboType->setEditable(true);
    comboType->addItem(tr("不使用代理"));
    comboType->addItem(tr("使用TCP连接"));
    comboType->addItem(tr("使用UDP连接"));
    comboType->addItem(tr("使用FTP连接"));
    comboType->setCurrentIndex(0);
    comboType->setStyleSheet("background-color:white;"
                             "font-size:9pt;"
                             "font-family:微软雅黑;");
    gridLayout->addWidget(labelType,2,0,1,1, Qt::AlignRight);
    gridLayout->addWidget(comboType,2,1,1,4);

    QLabel *labelAddress = new QLabel(tr("地址:"),this);
    labelAddress->setStyleSheet("border-style:none;");
    QLineEdit *editAddress = new QLineEdit(this);
    editAddress->setFixedHeight(25);
    gridLayout->addWidget(labelAddress,2,5,1,1);
    gridLayout->addWidget(editAddress,2,6,1,3);

    QLabel *labelPort = new QLabel(tr("端口:"),this);
    labelPort->setStyleSheet("border-style:none;");
    QLineEdit *editPort = new QLineEdit(this);
    editPort->setFixedSize(50,25);
    gridLayout->addWidget(labelPort,2,9,1,1);
    gridLayout->addWidget(editPort,2,10,1,2);

    //row 3
    QLabel *labelUserName  = new QLabel(tr("用户名:"), this);
    labelUserName->setStyleSheet("border-style:none;");
    QLineEdit *editUserName = new QLineEdit(this);
    editUserName->setFixedHeight(25);
    gridLayout->addWidget(labelUserName,3,0,1,1, Qt::AlignRight);
    gridLayout->addWidget(editUserName,3,1,1,4);

    QLabel *labelPassword = new QLabel(tr("密码:"),this);
    labelPassword->setStyleSheet("border-style:none;");
    QLineEdit *editPassword = new QLineEdit(this);
    editPassword->setFixedHeight(25);
    gridLayout->addWidget(labelPassword,3,5,1,1);
    gridLayout->addWidget(editPassword,3,6,1,3);


    QLabel *labelRegion = new QLabel(tr("域:"), this);
    labelRegion->setStyleSheet("border-style:none;");
    QLineEdit *editRegion = new QLineEdit(this);
    editRegion->setFixedSize(50,25);
    gridLayout->addWidget(labelRegion,3,9,1,1, Qt::AlignRight);
    gridLayout->addWidget(editRegion,3,10,1,2);

    //row 4
    QPushButton *buttonTest = new QPushButton(tr("测试"),this);
    buttonTest->setFixedSize(50,25);
    buttonTest->setStyleSheet("QPushButton{background-color:rgb(246,248,250);"
                                          "border:1px solid rgb(152,159,175);"
                                          "border-radius:2px;"
                                          "font-size:9pt;"
                                          "font-family:微软雅黑;} "
                              "QPushButton:hover{background-color:#00BFFF;}"
                              "QPushButton:pressed{background-color:#009ACD;}");
    gridLayout->addWidget(buttonTest,4,10,1,1, Qt::AlignRight);
    connect(buttonTest, &QPushButton::clicked, this, &NetWorkSetting::networkTest);

    //row 5
    QLabel *labelLoginServer = new QLabel(tr("登录服务器:"),this);
    labelLoginServer->setStyleSheet("border-style:none;");
    gridLayout->addWidget(labelLoginServer,5,0,1,2);

    //row 6
    QLabel *labelLoginType = new QLabel(tr("类型:"), this);
    labelLoginType->setStyleSheet("border-style:none;");
    QComboBox *comboLoginType = new QComboBox(this);
    comboLoginType->setEditable(true);
    QStringList list = QStringList()<<"不使用高级选项"<<"unknown"<<"Unknown";
    comboLoginType->addItems(list);
    comboLoginType->setFixedHeight(25);
    comboLoginType->setStyleSheet("background-color:white;"
                                  "font-size:9pt;"
                                  "font-family:微软雅黑;");
    gridLayout->addWidget(labelLoginType,6,0,1,1, Qt::AlignRight);
    gridLayout->addWidget(comboLoginType,6,1,1,4);

    QLabel *labelLoginAddress = new QLabel(tr("地址:"),this);
    labelLoginAddress->setStyleSheet("border-style:none;");
    QComboBox *comboLoginAddress = new QComboBox(this);
    comboLoginAddress->setEditable(true);
    comboLoginAddress->setFixedHeight(25);
    comboLoginAddress->setStyleSheet("QComboBox{border-style:none;"
                                                "border:1px solid rgb(193,194,196);"
                                                "background-color:white;"
                                                "font-size:9pt;"
                                                "font-family:微软雅黑;}"
                                     "QComboBox::drop-down{border:none;}");
    gridLayout->addWidget(labelLoginAddress,6,5,1,1);
    gridLayout->addWidget(comboLoginAddress,6,6,1,3);

    QLabel *labelLoginPort = new QLabel(tr("端口:"), this);
    labelLoginPort->setStyleSheet("border-style:none;");
    QLineEdit *editLoginPort = new QLineEdit(this);
    editLoginPort->setFixedSize(50,25);
    gridLayout->addWidget(labelLoginPort,6,9,1,1);
    gridLayout->addWidget(editLoginPort,6,10,1,2);
    gridLayout->setContentsMargins(20,0,20,50);
    content->setLayout(gridLayout);
    content->setContentsMargins(0,20,0,0);

    QLabel *bottom = new QLabel(this);
    bottom->setStyleSheet("background-color:rgb(204,227,242);"
                          "border-style:solid;");
    bottom->setFixedSize(431,35);
    bottom->setContentsMargins(0,0,0,0);
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    QPushButton *buttonOk = new QPushButton(tr("确定"), this);
    buttonOk->setFixedSize(80,25);
    buttonOk->setFlat(true);
    buttonOk->setStyleSheet("QPushButton{background-color:rgb(246,248,250);"
                                        "border:1px solid rgb(152,159,175);"
                                        "border-radius:3px;"
                                        "font-size:9pt;"
                                        "font-family:微软雅黑;} "
                            "QPushButton:hover{background-color:#00BFFF;}"
                            "QPushButton:pressed{background-color:#009ACD;}");

    QPushButton *buttonCancel = new QPushButton(tr("取消"), this);
    buttonCancel->setFixedSize(80,25);
    buttonCancel->setFlat(true);
    buttonCancel->setStyleSheet("QPushButton{background-color:rgb(246,248,250);"
                                "border:1px solid rgb(152,159,175);"
                                "border-width:1px;"
                                "border-radius:3px;"
                                "font-size:9pt;"
                                "font-family:微软雅黑;} "
                    "QPushButton:hover{background-color:#00BFFF;}"
                    "QPushButton:pressed{background-color:#009ACD;}");

    bottomLayout->addSpacing(220);
    bottomLayout->addWidget(buttonOk, Qt::AlignRight);
    bottomLayout->addWidget(buttonCancel, Qt::AlignRight);
    bottomLayout->setContentsMargins(5,5,5,5);
    bottomLayout->setSpacing(0);
    bottom->setLayout(bottomLayout);


    mainLayout->setSpacing(0);
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(content);
    mainLayout->addWidget(bottom);
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->setContentsMargins(20,0,20,0);
    this->setLayout(mainLayout);
}

void NetWorkSetting::networkTest()
{
    qDebug()<<"1";
}
/*
void NetWorkSetting::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        isMousePressed = true;
        MousePressPos = event->pos();
    }
}

void NetWorkSetting::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isMousePressed = false;
}

void NetWorkSetting::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousePressed && event->buttons()==Qt::LeftButton)
    {
        move(event->pos() - MousePressPos + this->pos());
    }
}
*/
