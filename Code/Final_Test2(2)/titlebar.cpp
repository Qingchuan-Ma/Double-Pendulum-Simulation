#include <QDesktopServices>
#include "titlebar.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("TitleBar{border:2px groove gray;border-radius:10px;padding:2px 4px;}");
    helper=new Help;
    contact=new Connect;
    setFixedHeight(43);
    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pOtherButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(30, 30);
    m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMinimizeButton->setFixedSize(30, 30);
    m_pOtherButton->setFixedSize(30, 30);
    m_pCloseButton->setFixedSize(30, 30);

    m_pTitleLabel->setObjectName("whiteLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pOtherButton->setObjectName("OtherButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMinimizeButton->setToolTip("Minimize");
    m_pOtherButton->setToolTip("More");
    m_pCloseButton->setToolTip("Close");

    m_pCloseButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/images/close.png);}"
                                  "QPushButton:hover{border-image: url(:/new/prefix1/images/close2.png);}"
                                  "QPushButton:pressed{border-image: url(:/new/prefix1/images/close2.png);}");
    m_pMinimizeButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/images/min.png);}"
                                     "QPushButton:hover{border-image: url(:/new/prefix1/images/min2.png);}"
                                     "QPushButton:pressed{border-image: url(:/new/prefix1/images/min2.png);}");
    m_pOtherButton->setStyleSheet("QPushButton{border-image: url(:/new/prefix1/images/Others.png);}"
                                  "QPushButton:hover{border-image: url(:/new/prefix1/images/Others2.png);}"
                                  "QPushButton:pressed{border-image: url(:/new/prefix1/images/Others2.png);}");

    moreMenu = new QMenu(this);
    helpAction = new QAction(moreMenu);
    save1Action = new QAction(moreMenu);
    save2Action = new QAction(moreMenu);
    aboutAction = new QAction(moreMenu);

    moreMenu->setStyleSheet("QMenu{border:2px groove gray;border-radius:10px;padding:2px 4px;}"
                            "QMenu {background-color: white;}"
                            "QMenu::item:selected {background: rgba(224, 224, 224);}");
    moreMenu->addAction(save1Action);
    moreMenu->addAction(save2Action);
    moreMenu->addSeparator();
    moreMenu->addAction(helpAction);
    moreMenu->addAction(aboutAction);

    helpAction->setToolTip("About the program");
    save1Action->setToolTip("Saving the data");
    save2Action->setToolTip("Saving the data");
    aboutAction->setToolTip("Connecting us and reporting bug!");

    connect(moreMenu,SIGNAL(triggered(QAction *)),this,SLOT(onMenu_Triggered(QAction *)));//菜单响应连接
    helpAction->setText(tr("Help..."));
    helpAction->setIcon(QIcon(QPixmap(":/new/prefix1/images/help.png")));

    save1Action->setText(tr("Save Double"));
    save1Action->setIcon(QIcon(QPixmap(":/new/prefix1/images/save.png")));

    save2Action->setText(tr("Save Triple"));
    save2Action->setIcon(QIcon(QPixmap(":/new/prefix1/images/save.png")));

    aboutAction->setText(tr("About..."));
    aboutAction->setIcon(QIcon(QPixmap(":/new/prefix1/images/about.png")));

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(6);
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addWidget(m_pOtherButton);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(8, 0, 5, 0);

    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pOtherButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

}

TitleBar::~TitleBar()
{

}


void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
      return true;
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
       else if (pButton == m_pOtherButton)
        {
            QPoint pos (m_pOtherButton->mapToGlobal(QPoint(0,0)).x(),m_pOtherButton->mapToGlobal(QPoint(0,0)).y()+31);
            moreMenu->exec(pos);
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void TitleBar::onMenu_Triggered(QAction *action)
{
    if(action == helpAction)
    {
        helper->show();
    }
    else if(action == save1Action)
    {
        emit save1();
    }
    else if(action == save2Action)
    {
        emit save2();
    }
    else if(action == aboutAction)
    {
        contact->show();
    }
}
