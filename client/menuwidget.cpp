#include "menuwidget.h"

MenuWidget::MenuWidget(QWidget* parent, QStatusBar *statusBar)
        : QWidget((QWidget*)parent)
{
    QFrame * panel = new QFrame(this);
    panel->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    QPushButton *bConnect = new QPushButton("Connect", panel);
    //QPushButton *bStart = new QPushButton("Game Mode", panel);
    QPushButton *bExit = new QPushButton("Exit", panel);
    QVBoxLayout *panelLayout = new QVBoxLayout;
    panelLayout->addWidget(bConnect);
    //panelLayout->addWidget(bStart);
    panelLayout->addWidget(bExit);
    panel->setLayout(panelLayout);

    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch(1);
    hLayout->addWidget(panel);
    hLayout->addStretch(1);
    vLayout->addStretch(1);
    vLayout->addLayout(hLayout);
    vLayout->addStretch(1);

    setLayout(vLayout);

    connect(this, SIGNAL(showStatusMessage(QString,int)), statusBar, SLOT(showMessage(QString, int)));

    connect(this, SIGNAL(enterGameState(QString)), parent, SLOT(enterGameState(QString)));
    //connect(bStart, SIGNAL(clicked()), this, SLOT(startGame()));
    connect(bConnect, SIGNAL(clicked()), this, SLOT(askAddress()));
    connect(bExit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MenuWidget::~MenuWidget()
{
}

void MenuWidget::askAddress()
{
    bool ok;
    QString address = QInputDialog::getText(this, "Address", "Address:", QLineEdit::Normal, "", &ok);
    if (ok)
        startGame(address);
}

void MenuWidget::startGame(QString address)
{
    emit enterGameState(address);
    //emit enterGameState("E:\\Documents\\Kurssit\\MMJ\\Qt_client\\Client\\debug\\test.avi");
}
