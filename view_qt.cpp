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
    Parser *pParser = new Parser();
    ui->widget->Cut(ui->spinBox->value(),ui->spinBox_2->value());
}

void View_QT::on_pushButton_2_clicked()
{
    ui->widget->Move(ui->spinBox->value(),ui->spinBox_2->value());
}
