#ifndef FUN_H
#define FUN_H

#include <QWidget>

namespace Ui {
class Fun;
}

class Fun : public QWidget
{
    Q_OBJECT

public:
    explicit Fun(QWidget *parent = 0);
    ~Fun();

private:
    Ui::Fun *ui;
};

#endif // FUN_H
