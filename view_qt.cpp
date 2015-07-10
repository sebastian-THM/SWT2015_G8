#include "view_qt.h"
#include "ui_view_qt.h"
#include "parser.h"

View_QT::View_QT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::View_QT)
{
    ui->setupUi(this);
}

View_QT::~View_QT()
{
    delete ui;
}

void View_QT::on_pushButton_clicked()
{

}

void View_QT::on_pushButton_2_clicked()
{

}
