#ifndef TITLE_BAR
#define TITLE_BAR

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QMenu>
#include "help.h"
#include "connect.h"

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

protected:

    // 进行鼠界面的拖动
    virtual void mousePressEvent(QMouseEvent *event);

    // 设置界面标题与图标
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:

    void onClicked();
    void onMenu_Triggered(QAction *action);

private:
    QLabel *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pOtherButton;
    QPushButton *m_pCloseButton;
    QMenu *moreMenu;
    QAction *helpAction;
    QAction *save1Action;
    QAction *save2Action;
    QAction *aboutAction;
    Help *helper;
    Connect *contact;

signals:
    void save1();
    void save2();
};

#endif // TITLE_BAR
