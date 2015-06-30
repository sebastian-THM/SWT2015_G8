#ifndef VIEW_QT_H
#define VIEW_QT_H

#include <QMainWindow>

namespace Ui {
class View_QT;
}

class View_QT : public QMainWindow
{
    Q_OBJECT

public:
    explicit View_QT(QWidget *parent = 0);
    ~View_QT();

private:
    Ui::View_QT *ui;
};

#endif // VIEW_QT_H
