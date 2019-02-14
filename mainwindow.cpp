#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double P = (ui->taliya->text().toDouble()/ui->bedra->text().toDouble());
    QString R = QString::number(P);
    ui->ot_ob->setText(R);

    double IMT = (ui->ves->text().toDouble())/(((ui->rost->text().toDouble())/100)*(ui->rost->text().toDouble())/100);
    QString IMTs = QString::number(IMT);
    ui->imt->setText(IMTs);

    if (ui->zen->isChecked())
    {
       double VO = 9.99*(ui->ves->text().toDouble())+6.25*(ui->rost->text().toDouble())-4.92*(ui->vozrast->text().toDouble())-161;
       QString VOs = QString::number(VO);
       ui->voo->setText(VOs);
    }
    if (ui->muz->isChecked())
    {
       double VO = 9.99*(ui->ves->text().toDouble())+6.25*(ui->rost->text().toDouble())-4.92*(ui->vozrast->text().toDouble())+5;
       QString VOs = QString::number(VO);
       ui->voo->setText(VOs);
    }

}
