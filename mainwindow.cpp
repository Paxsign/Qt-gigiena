#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sum=0;
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

void MainWindow::on_pushButton_3_clicked()
{
    qDebug()<<sum;
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLineEdit *lnd1 = new QLineEdit(ui->sp_deistviya->currentText());
    QLineEdit *lnd2 = new QLineEdit(ui->time->text());
    QLineEdit *lnd3 = new QLineEdit("12345");
    layout->addWidget(lnd1,8);
    layout->addWidget(lnd2,2);
    layout->addWidget(lnd3,2);

    ui->verticalLayout_7->addLayout(layout);
    ui->verticalLayout_7->setAlignment(Qt::AlignTop);
    sum = lnd3->text().toDouble()+sum;
    ui->summa_kalori_potrach->setText(QString::number(sum));

}
