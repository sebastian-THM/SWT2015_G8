#include "view_qt.h"
#include "ui_view_qt.h"
#include "parser.h"
#include <QFileDialog>
#include <QMessageBox>

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

void View_QT::on_StartButton_clicked()
{
    emit ui->renderArea->SendStart();
}

void View_QT::on_DataBrowserButton_clicked()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setEnabled(true);
    char text[201];
    int X;
    QStringList textlist;
    QString filename;

    filename = QFileDialog::getOpenFileName(this, tr("Datei auswählen"), "C://","All Files(*.*);; Text Files (*.txt)");
    QMessageBox::information(this, tr("Datei geladen"), "Zum starten des Lasers jetzt auf \"Star/Weiter\" drücken");
    ui->lineEdit->setText(filename);
    if(filename.isEmpty())
    {
        QMessageBox::information(this, tr("Fehler"), "Es wurde keine Datei ausgewählt");
        return;
    }
    else
    {
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Fehler beim Öffnen"), file.errorString());
            return;
        }

        file.seek(0);

        memset(text,'\0',201);
        while((X=file.readLine(text,200)) != -1)
        {
            text[X-1] = '\0';
            textlist.append(text);
            memset(text,'\0',201);
        }
        ui->plainTextEdit->setPlainText(textlist.join('\n') );
    }
    ui->plainTextEdit->setEnabled(false);
    emit ui->renderArea->SendOpenFile(ui->lineEdit->text().toStdString());
}

void View_QT::on_DataLoadButton_clicked()
{
    QMessageBox::information(this, tr("Datei geladen"), "Zum starten des Lasers jetzt auf \"Star/Weiter\" drücken");
    emit ui->renderArea->SendOpenFile(ui->lineEdit->text().toStdString());
}

void View_QT::on_PauseButton_clicked()
{
    emit ui->renderArea->SendPause();
}

void View_QT::on_lineEdit_returnPressed()
{
    QMessageBox::information(this, tr("Datei geladen"), "Zum starten des Lasers jetzt auf \"Star/Weiter\" drücken");
    emit ui->renderArea->SendOpenFile(ui->lineEdit->text().toStdString());
}

void View_QT::on_pushButton_clicked()
{
    emit ui->renderArea->SendOpenFile("NOFILE");
}
