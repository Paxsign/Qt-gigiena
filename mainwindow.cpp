#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <QCompleter>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    uglevod=0;
    sum=0;
    belki=0;
    zhiv_belk=0;
    zhir=0;
    rast_zhir=0;
    Ca=0;
    P=0;
    vC=0;
    kkal=0;
    kkal_obed=0;
    kkal_uzin=0;
    kkal_perekus=0;
    kkal_zavtrak=0;

    ui->tableWidget->hide();

    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(10);
    csvModel->setHorizontalHeaderLabels(QStringList() <<"Продукт"<<"животн_белки"<<"растит_белки"<<"животн_жир"<<"растит_жир"<<"углеводы"<<"Ca"<<"P"<<"ккал"<<"С");

    QFile file("tablitsa_produktov_2_1.csv");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Создаём поток для извлечения данных из файла
        QTextStream in(&file);
        // Считываем данные до конца файла
        while (!in.atEnd())
        {
            // ... построчно
            QString line = in.readLine();
            // Добавляем в модель по строке с элементами
            QList<QStandardItem *> standardItemsList;
            // учитываем, что строка разделяется точкой с запятой на колонки
            for (QString item : line.split(";")) {
                standardItemsList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemsList);
        }
        file.close();

        QCompleter* completer = new QCompleter( this );
            completer->setModel( csvModel );
            completer->setCaseSensitivity( Qt::CaseInsensitive );
            ui->produkt->setCompleter( completer );

}
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
{int hh;
    if (ui->zen->isChecked()){ hh=1; }
    if (ui->muz->isChecked()){ hh=0; }
    double ff = (ui->voo->text().toDouble())*(ui->time->text().toDouble())*ui->tableWidget->item(ui->sp_deistviya->currentIndex()-1,hh)->text().toDouble();
    //qDebug()<<ui->tableWidget->takeItem(ui->sp_deistviya->currentIndex(),0)->text().toDouble();
    qDebug()<<ff;

    //qDebug()<<sum;
    QHBoxLayout *layout = new QHBoxLayout(this);
    QLineEdit *lnd1 = new QLineEdit(ui->sp_deistviya->currentText());
    QLineEdit *lnd2 = new QLineEdit(ui->time->text());
    QLineEdit *lnd3 = new QLineEdit(QString::number(ff));
    layout->addWidget(lnd1,8);
    layout->addWidget(lnd2,2);
    layout->addWidget(lnd3,2);

    ui->verticalLayout_7->addLayout(layout);
    ui->verticalLayout_7->setAlignment(Qt::AlignTop);
    sum = lnd3->text().toDouble()+sum;
    ui->summa_kalori_potrach->setText(QString::number(sum));

}

void MainWindow::on_pushButton_2_clicked()
{
    QVBoxLayout *eda;
    QList<QStandardItem*> gg= csvModel->findItems(ui->produkt->text());//поиск элемента в модели

    QModelIndex i = csvModel->indexFromItem(gg.at(0));//индекс елемента

    int num=i.row();//номер строки в индексе элемента QModelIndex.collum - получить номер столбца.

    if (ui->zavtrak->isChecked()){
        eda=ui->verticalLayout_2;
    };
    if (ui->obed->isChecked()){
        eda=ui->verticalLayout_8;
    };
    if (ui->uzin->isChecked()){
        eda=ui->verticalLayout_9;
    };
    if (ui->perekus->isChecked()){
        eda=ui->verticalLayout_10;
    };


    QHBoxLayout *layout = new QHBoxLayout(this);    // создание горизонтального слоя QHBox (вертикальный QVBox)
        QLabel *lbl = new QLabel(csvModel->item(num,0)->text() , this);  //создание лабеля
        QLabel *lbl1 = new QLabel(csvModel->item(num,1)->text() , this);
        QLabel *lbl2 = new QLabel(csvModel->item(num,2)->text() , this);
        QLabel *lbl3 = new QLabel(csvModel->item(num,3)->text() , this);
        QLabel *lbl4 = new QLabel(csvModel->item(num,4)->text() , this);
        QLabel *lbl5 = new QLabel(csvModel->item(num,5)->text() , this);
        QLabel *lbl6 = new QLabel(csvModel->item(num,6)->text() , this);
        QLabel *lbl7 = new QLabel(csvModel->item(num,7)->text() , this);
        QLabel *lbl8 = new QLabel(csvModel->item(num,8)->text() , this);
        QLabel *lbl9 = new QLabel(csvModel->item(num,9)->text() , this);
        lbl->setWordWrap(true);
        layout->addWidget(lbl);                     //запихиваем лабель в горизонтальный слой
        layout->addWidget(lbl1);
        layout->addWidget(lbl2);
        layout->addWidget(lbl3);
        layout->addWidget(lbl4);
        layout->addWidget(lbl5);
        layout->addWidget(lbl6);
        layout->addWidget(lbl7);
        layout->addWidget(lbl8);
        layout->addWidget(lbl9);
        eda->addLayout(layout); //запихиваем горизонтальный слой в вертикальный созданнвй в дизайнере
        eda->setAlignment(Qt::AlignTop);
        eda->setSpacing(15);
        eda->setStretch(7,2);
        eda->setStretch(8,2);
        eda->setStretch(9,2);

        if (ui->zavtrak->isChecked()){
           kkal_zavtrak=kkal_zavtrak + ((lbl8->text().toFloat()/100)*ui->prod_kolvo->text().toFloat());
        };
        if (ui->obed->isChecked()){
           kkal_obed=kkal_obed + ((lbl8->text().toFloat()/100)*ui->prod_kolvo->text().toFloat());
        };
        if (ui->uzin->isChecked()){
            kkal_uzin=kkal_uzin + ((lbl8->text().toFloat()/100)*ui->prod_kolvo->text().toFloat());
        };
        if (ui->perekus->isChecked()){
            kkal_perekus=kkal_perekus + ((lbl8->text().toFloat()/100)*ui->prod_kolvo->text().toFloat());
        };

        rast_zhir=rast_zhir + lbl4->text().toFloat();
        zhiv_belk=zhiv_belk + lbl1->text().toFloat();
        belki=belki + lbl2->text().toFloat()+lbl1->text().toFloat();
        uglevod=uglevod + lbl5->text().toFloat();
        zhir=zhir + lbl3->text().toFloat()+lbl4->text().toFloat();
        Ca=Ca + lbl6->text().toFloat();
        P=P + lbl7->text().toFloat();
        vC=vC + lbl9->text().toFloat();

         zb = zhir/belki;
         ub = uglevod/belki;

        kkal =kkal + ((lbl8->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()); // сумма калорий (kkal обьявлен в заголовочном файле как float)
        ui->sum_kalori->setText(QString::number(kkal));
        ui->kkal_zav->setText(QString::number(kkal_zavtrak));
        ui->kkal_obed->setText(QString::number(kkal_obed));
        ui->kkal_uzin->setText(QString::number(kkal_uzin));
        ui->kkal_perekus->setText(QString::number(kkal_perekus));
}

void MainWindow::on_pushButton_4_clicked()
{qDebug()<<QString::number(belki);
    QTableWidgetItem* uglev=new QTableWidgetItem;
    QTableWidgetItem* belk=new QTableWidgetItem;
    QTableWidgetItem* zhirr=new QTableWidgetItem;
    QTableWidgetItem* Calc=new QTableWidgetItem;
    QTableWidgetItem* Phos=new QTableWidgetItem;
    QTableWidgetItem* vitC=new QTableWidgetItem;
    QTableWidgetItem* kratnost=new QTableWidgetItem;
    QTableWidgetItem* promez=new QTableWidgetItem;
    QTableWidgetItem* zhivkbel=new QTableWidgetItem;
    QTableWidgetItem* bel_kkal=new QTableWidgetItem;
    QTableWidgetItem* ugl_kkal=new QTableWidgetItem;
    QTableWidgetItem* zhir_kkal=new QTableWidgetItem;
    QTableWidgetItem* rastkzhir=new QTableWidgetItem;
    QTableWidgetItem* sootn=new QTableWidgetItem;
    belk->setText(QString::number(belki));
    ui->tableWidget_2->setItem(1,0,belk);
    uglev->setText(QString::number(uglevod));
    ui->tableWidget_2->setItem(9,0,uglev);
    zhirr->setText(QString::number(zhir));
    ui->tableWidget_2->setItem(5,0,zhirr);
    Calc->setText(QString::number(Ca));
    ui->tableWidget_2->setItem(13,0,Calc);
    Phos->setText(QString::number(P));
    ui->tableWidget_2->setItem(14,0,Phos);
    vitC->setText(QString::number(vC));
    ui->tableWidget_2->setItem(15,0,vitC);
    kratnost->setText(ui->lineEdit->text());
    ui->tableWidget_2->setItem(17,0,kratnost);
    promez->setText(ui->lineEdit_2->text());
    ui->tableWidget_2->setItem(18,0,promez);
    zhivkbel->setText(QString::number((zhiv_belk/belki)*100));
    ui->tableWidget_2->setItem(2,0,zhivkbel);
    rastkzhir->setText(QString::number((rast_zhir/zhir)*100));
    ui->tableWidget_2->setItem(6,0,rastkzhir);
    bel_kkal->setText(QString::number((belki*4*100)/kkal));
    ui->tableWidget_2->setItem(3,0,bel_kkal);
    ugl_kkal->setText(QString::number((uglevod*4*100)/kkal));
    ui->tableWidget_2->setItem(10,0,ugl_kkal);
    zhir_kkal->setText(QString::number((zhir*9*100)/kkal));
    ui->tableWidget_2->setItem(7,0,zhir_kkal);
    QString fff="1:" + QString::number(zb,'f',2)+':'+QString::number(ub,'f',2);
    sootn->setText(fff);
    ui->tableWidget_2->setItem(11,0,sootn);
}
