#ifndef CALCULATEWIDGET_H
#define CALCULATEWIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QToolButton>
#include <QStyle>

class CalculateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalculateWidget(QWidget *parent = 0);
    ~CalculateWidget();
    void setTipInfo(QString info);
    void setTipIcon(QPixmap pixmap);

private:
    QLabel *ask_label;
    QLabel *msg_label;
    QToolButton *close_button;
public slots:
    bool closeWidget();

};

#endif // CALCULATEWIDGET_H
