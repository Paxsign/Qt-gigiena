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
    sum_time=0;
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
    zav_C=0;
    zav_P=0;
    zav_Ca=0;
    zav_ugl=0;
    zav_rast_belk=0;
    zav_rast_zhir=0;
    zav_zhiv_belk=0;
    zav_zhiv_zhir=0;
    obed_C=0;
    obed_P=0;
    obed_Ca=0;
    obed_ugl=0;
    obed_rast_belk=0;
    obed_rast_zhir=0;
    obed_zhiv_belk=0;
    obed_zhiv_zhir=0;
    uzin_C=0;
    uzin_P=0;
    uzin_Ca=0;
    uzin_ugl=0;
    uzin_rast_belk=0;
    uzin_rast_zhir=0;
    uzin_zhiv_belk=0;
    uzin_zhiv_zhir=0;
    perekus_C=0;
    perekus_P=0;
    perekus2_C=0;
    perekus2_P=0;
    perekus_Ca=0;
    perekus2_Ca=0;
    perekus_ugl=0;
    perekus2_ugl=0;
    perekus_rast_belk=0;
    perekus_rast_zhir=0;
    perekus_zhiv_belk=0;
    perekus_zhiv_zhir=0;
    perekus2_rast_belk=0;
    perekus2_rast_zhir=0;
    perekus2_zhiv_belk=0;
    perekus2_zhiv_zhir=0;
    kkal_perekus2=0;
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
     Pr = (ui->taliya->text().toDouble()/ui->bedra->text().toDouble());
    QString R = QString::number(Pr);


    IMT = (ui->ves->text().toDouble())/(((ui->rost->text().toDouble())/100)*(ui->rost->text().toDouble())/100);
    QString IMTs = QString::number(IMT);


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
    double ff = (ui->voo->text().toDouble()/24)*(ui->time->text().toDouble())*ui->tableWidget->item(ui->sp_deistviya->currentIndex()-1,hh)->text().toDouble();
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
    sum_time = sum_time+ui->time->text().toFloat();
    ui->sum_time->setText(QString::number(sum_time));
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
    if (ui->perekus2->isChecked()){
        eda=ui->verticalLayout_11;
    };

    QHBoxLayout *layout = new QHBoxLayout(this);    // создание горизонтального слоя QHBox (вертикальный QVBox)
        QLabel *lbl = new QLabel(csvModel->item(num,0)->text() , this);  //создание лабеля
        QLabel *lbl1 = new QLabel(QString::number((csvModel->item(num,1)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        QLabel *lbl2 = new QLabel(QString::number((csvModel->item(num,2)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        QLabel *lbl3 = new QLabel(QString::number((csvModel->item(num,3)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        QLabel *lbl4 = new QLabel(QString::number((csvModel->item(num,4)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        QLabel *lbl5 = new QLabel(QString::number((csvModel->item(num,5)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        QLabel *lbl6 = new QLabel(QString::number((csvModel->item(num,6)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        QLabel *lbl7 = new QLabel(QString::number((csvModel->item(num,7)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        QLabel *lbl8 = new QLabel(QString::number((csvModel->item(num,8)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        QLabel *lbl9 = new QLabel(QString::number((csvModel->item(num,9)->text().toFloat()/100)*ui->prod_kolvo->text().toFloat()) , this);
        lbl->setWordWrap(true);
        layout->addWidget(lbl,5);                     //запихиваем лабель в горизонтальный слой
        layout->addWidget(lbl1,3);
        layout->addWidget(lbl2,3);
        layout->addWidget(lbl3,3);
        layout->addWidget(lbl4,3);
        layout->addWidget(lbl5,3);
        layout->addWidget(lbl6,2);
        layout->addWidget(lbl7,2);
        layout->addWidget(lbl8,2);
        layout->addWidget(lbl9,2);

        eda->addLayout(layout); //запихиваем горизонтальный слой в вертикальный созданнвй в дизайнере
        eda->setAlignment(Qt::AlignTop);
        eda->setSpacing(10);


        if (ui->zavtrak->isChecked()){
           kkal_zavtrak=kkal_zavtrak + (lbl8->text().toFloat());
           zav_zhiv_belk=zav_zhiv_belk + (lbl1->text().toFloat());
           zav_rast_belk=zav_rast_belk + (lbl2->text().toFloat());
           zav_zhiv_zhir=zav_zhiv_zhir + (lbl3->text().toFloat());
           zav_rast_zhir=zav_rast_zhir + (lbl4->text().toFloat());
           zav_ugl=zav_ugl + (lbl5->text().toFloat());
           zav_Ca=zav_Ca + (lbl6->text().toFloat());
           zav_P=zav_P + (lbl7->text().toFloat());
           zav_C=zav_C + (lbl9->text().toFloat());


        };
        if (ui->obed->isChecked()){
           kkal_obed=kkal_obed + (lbl8->text().toFloat());
           obed_zhiv_belk=obed_zhiv_belk + (lbl1->text().toFloat());
           obed_rast_belk=obed_rast_belk + (lbl2->text().toFloat());
           obed_zhiv_zhir=obed_zhiv_zhir + (lbl3->text().toFloat());
           obed_rast_zhir=obed_rast_zhir + (lbl4->text().toFloat());
           obed_ugl=obed_ugl + (lbl5->text().toFloat());
           obed_Ca=obed_Ca + (lbl6->text().toFloat());
           obed_P=obed_P + (lbl7->text().toFloat());
           obed_C=obed_C + (lbl9->text().toFloat());
        };
        if (ui->uzin->isChecked()){
            kkal_uzin=kkal_uzin + (lbl8->text().toFloat());
            uzin_zhiv_belk=uzin_zhiv_belk + (lbl1->text().toFloat());
            uzin_rast_belk=uzin_rast_belk + (lbl2->text().toFloat());
            uzin_zhiv_zhir=uzin_zhiv_zhir + (lbl3->text().toFloat());
            uzin_rast_zhir=uzin_rast_zhir + (lbl4->text().toFloat());
            uzin_ugl=uzin_ugl + (lbl5->text().toFloat());
            uzin_Ca=uzin_Ca + (lbl6->text().toFloat());
            uzin_P=uzin_P + (lbl7->text().toFloat());
            uzin_C=uzin_C + (lbl9->text().toFloat());
        };
        if (ui->perekus->isChecked()){
            kkal_perekus=kkal_perekus + (lbl8->text().toFloat());
            perekus_zhiv_belk=perekus_zhiv_belk + (lbl1->text().toFloat());
            perekus_rast_belk=perekus_rast_belk + (lbl2->text().toFloat());
            perekus_zhiv_zhir=perekus_zhiv_zhir + (lbl3->text().toFloat());
            perekus_rast_zhir=perekus_rast_zhir + (lbl4->text().toFloat());
            perekus_ugl=perekus_ugl + (lbl5->text().toFloat());
            perekus_Ca=perekus_Ca + (lbl6->text().toFloat());
            perekus_P=perekus_P + (lbl7->text().toFloat());
            perekus_C=perekus_C + (lbl9->text().toFloat());
        };
        if (ui->perekus2->isChecked()){
            kkal_perekus2=kkal_perekus2 + (lbl8->text().toFloat());
            perekus2_zhiv_belk=perekus2_zhiv_belk + (lbl1->text().toFloat());
            perekus2_rast_belk=perekus2_rast_belk + (lbl2->text().toFloat());
            perekus2_zhiv_zhir=perekus2_zhiv_zhir + (lbl3->text().toFloat());
            perekus2_rast_zhir=perekus2_rast_zhir + (lbl4->text().toFloat());
            perekus2_ugl=perekus2_ugl + (lbl5->text().toFloat());
            perekus2_Ca=perekus2_Ca + (lbl6->text().toFloat());
            perekus2_P=perekus2_P + (lbl7->text().toFloat());
            perekus2_C=perekus2_C + (lbl9->text().toFloat());
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

        kkal =kkal + (lbl8->text().toFloat()); // сумма калорий (kkal обьявлен в заголовочном файле как float)
        ui->sum_kalori->setText(QString::number(kkal));
        ui->kkal_zav->setText(QString::number(kkal_zavtrak));
        ui->kkal_obed->setText(QString::number(kkal_obed));
        ui->kkal_uzin->setText(QString::number(kkal_uzin));
        ui->kkal_perekus->setText(QString::number(kkal_perekus));
        ui->kkal_perekus2->setText(QString::number(kkal_perekus2));
        ui->zav_zhiv_belk->setText(QString::number(zav_zhiv_belk));
        ui->zav_rast_belk->setText(QString::number(zav_rast_belk));
        ui->zav_zhiv_zhir->setText(QString::number(zav_zhiv_zhir));
        ui->zav_rast_zhir->setText(QString::number(zav_rast_zhir));
        ui->zav_C->setText(QString::number(zav_C));
        ui->zav_Ca->setText(QString::number(zav_Ca));
        ui->zav_P->setText(QString::number(zav_P));
        ui->zav_ugl->setText(QString::number(zav_ugl));

        ui->perekus_zhiv_belk->setText(QString::number(perekus_zhiv_belk));
        ui->perekus_rast_belk->setText(QString::number(perekus_rast_belk));
        ui->perekus_zhiv_zhir->setText(QString::number(perekus_zhiv_zhir));
        ui->perekus_rast_zhir->setText(QString::number(perekus_rast_zhir));
        ui->perekus_C->setText(QString::number(perekus_C));
        ui->perekus_Ca->setText(QString::number(perekus_Ca));
        ui->perekus_P->setText(QString::number(perekus_P));
        ui->perekus_ugl->setText(QString::number(perekus_ugl));

        ui->obed_zhiv_belk->setText(QString::number(obed_zhiv_belk));
        ui->obed_rast_belk->setText(QString::number(obed_rast_belk));
        ui->obed_zhiv_zhir->setText(QString::number(obed_zhiv_zhir));
        ui->obed_rast_zhir->setText(QString::number(obed_rast_zhir));
        ui->obed_C->setText(QString::number(obed_C));
        ui->obed_Ca->setText(QString::number(obed_Ca));
        ui->obed_P->setText(QString::number(obed_P));
        ui->obed_ugl->setText(QString::number(obed_ugl));

        ui->uzin_zhiv_belk->setText(QString::number(uzin_zhiv_belk));
        ui->uzin_rast_belk->setText(QString::number(uzin_rast_belk));
        ui->uzin_zhiv_zhir->setText(QString::number(uzin_zhiv_zhir));
        ui->uzin_rast_zhir->setText(QString::number(uzin_rast_zhir));
        ui->uzin_C->setText(QString::number(uzin_C));
        ui->uzin_Ca->setText(QString::number(uzin_Ca));
        ui->uzin_P->setText(QString::number(uzin_P));
        ui->uzin_ugl->setText(QString::number(uzin_ugl));

        ui->perekus2_zhiv_belk->setText(QString::number(perekus2_zhiv_belk));
        ui->perekus2_rast_belk->setText(QString::number(perekus2_rast_belk));
        ui->perekus2_zhiv_zhir->setText(QString::number(perekus2_zhiv_zhir));
        ui->perekus2_rast_zhir->setText(QString::number(perekus2_rast_zhir));
        ui->perekus2_C->setText(QString::number(perekus2_C));
        ui->perekus2_Ca->setText(QString::number(perekus2_Ca));
        ui->perekus2_P->setText(QString::number(perekus2_P));
        ui->perekus2_ugl->setText(QString::number(perekus2_ugl));

        ui->produkt->clear();
        ui->prod_kolvo->clear();
}

void MainWindow::on_pushButton_4_clicked()
{   int i;
    i=1;
    QString ending;
    QTableWidgetItem* uglev=new QTableWidgetItem;
    QTableWidgetItem* uglev_norm=new QTableWidgetItem;
    QTableWidgetItem* belk=new QTableWidgetItem;
    QTableWidgetItem* belk_norm=new QTableWidgetItem;
    QTableWidgetItem* zhirr=new QTableWidgetItem;
    QTableWidgetItem* zhirr_norm=new QTableWidgetItem;
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
    QTableWidgetItem* kkal_zav_procent=new QTableWidgetItem;
    QTableWidgetItem* kkal_obed_procent=new QTableWidgetItem;
    QTableWidgetItem* kkal_uzin_procent=new QTableWidgetItem;
    QTableWidgetItem* kkal_perekus_procent=new QTableWidgetItem;
    belk->setText(QString::number(belki));
    ui->tableWidget_2->setItem(1,0,belk);
    belk_norm->setText(ui->ves->text());
    ui->tableWidget_2->setItem(1,1,belk_norm);
    uglev->setText(QString::number(uglevod));
    ui->tableWidget_2->setItem(9,0,uglev);
    uglev_norm->setText(QString::number(ui->ves->text().toFloat()*4));
    ui->tableWidget_2->setItem(9,1,uglev_norm);
    zhirr_norm->setText(ui->ves->text());
   ui->tableWidget_2->setItem(5,1,zhirr_norm);
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

    kkal_zav_procent->setText(QString::number((kkal_zavtrak*100)/kkal)+"%");
    ui->tableWidget_2->setItem(20,0,kkal_zav_procent);
    kkal_obed_procent->setText(QString::number((kkal_obed*100)/kkal)+"%");
    ui->tableWidget_2->setItem(21,0,kkal_obed_procent);
    kkal_uzin_procent->setText(QString::number((kkal_uzin*100)/kkal)+"%");
    ui->tableWidget_2->setItem(22,0,kkal_uzin_procent);
    kkal_perekus_procent->setText(QString::number(((kkal_perekus+kkal_perekus2)*100)/kkal)+"%");
    ui->tableWidget_2->setItem(23,0,kkal_perekus_procent);


    if (ui->tableWidget_2->item(2,0)->text().toFloat()>55) {
        QTableWidgetItem* itog_bel=new QTableWidgetItem;
        itog_bel->setText("выше нормы");
        ui->tableWidget_2->setItem(2,2,itog_bel);
    }
   else if (ui->tableWidget_2->item(2,0)->text().toFloat()<55) {
        QTableWidgetItem* itog_bel=new QTableWidgetItem;
        itog_bel->setText("меньше нормы");
        ui->tableWidget_2->setItem(2,2,itog_bel);
        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(2)->text()+" "+ui->tableWidget_2->item(2,2)->text()+";\n"+"Необходимо повысить употребление продуктов, содержащих животный белок (мясо, творог, молочные продукты, яйца)"+";\n";
    i=i+1;
    }
    else {
        QTableWidgetItem* itog_bel=new QTableWidgetItem;
        itog_bel->setText("норма");
        ui->tableWidget_2->setItem(2,2,itog_bel);
    }

    if(ui->tableWidget_2->item(3,0)->text().toFloat()>14){
        QTableWidgetItem* itog_belkkal=new QTableWidgetItem;
        itog_belkkal->setText("выше нормы");
        ui->tableWidget_2->setItem(3,2,itog_belkkal);
    }
    else if(ui->tableWidget_2->item(3,0)->text().toFloat()<11){
        QTableWidgetItem* itog_belkkal=new QTableWidgetItem;
        itog_belkkal->setText("меньше нормы");
        ui->tableWidget_2->setItem(3,2,itog_belkkal);
        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(3)->text()+" "+ui->tableWidget_2->item(3,2)->text()+";\n"+"Чаще употреблять продукты, богатые животным и растительным белком(мясо, молочные продукты, бобовые, орехи и семечки, тофу)"+";\n";
    i=i+1;
    }
    else {
        QTableWidgetItem* itog_belkkal=new QTableWidgetItem;
        itog_belkkal->setText("норма");
        ui->tableWidget_2->setItem(3,2,itog_belkkal);
    }

    if(ui->tableWidget_2->item(6,0)->text().toFloat()>30){
        QTableWidgetItem* itog_zhir=new QTableWidgetItem;
        itog_zhir->setText("больше нормы");
        ui->tableWidget_2->setItem(6,2,itog_zhir);
    }
    else if (ui->tableWidget_2->item(6,0)->text().toFloat()<25) {
        QTableWidgetItem* itog_zhir=new QTableWidgetItem;
        itog_zhir->setText("меньше нормы");
        ui->tableWidget_2->setItem(6,2,itog_zhir);
        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(6)->text()+" "+ui->tableWidget_2->item(6,2)->text()+";\n"+"Увеличить потребление продуктов, богатых растительными жирами(растительные масла, орехи, авокадо, льняное семя)"+";\n";
    i=i+1;
    }
    else {
        QTableWidgetItem* itog_zhir=new QTableWidgetItem;
        itog_zhir->setText("норма");
        ui->tableWidget_2->setItem(6,2,itog_zhir);
    }

    if(ui->tableWidget_2->item(7,0)->text().toFloat()>35){
        QTableWidgetItem* itog_zhirkkal=new QTableWidgetItem;
        itog_zhirkkal->setText("больше нормы");
        ui->tableWidget_2->setItem(7,2,itog_zhirkkal);
    }
    else if (ui->tableWidget_2->item(7,0)->text().toFloat()<30) {
        QTableWidgetItem* itog_zhirkkal=new QTableWidgetItem;
        itog_zhirkkal->setText("меньше нормы");
        ui->tableWidget_2->setItem(7,2,itog_zhirkkal);
        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(7)->text()+" "+ui->tableWidget_2->item(7,2)->text()+";\n"+"Увеличить потребление продуктов, богатых жирами(масла, сало, орехи, жирная рыба, мясо)"+";\n";
    i=i+1;
    }
    else {
        QTableWidgetItem* itog_zhirkkal=new QTableWidgetItem;
        itog_zhirkkal->setText("норма");
        ui->tableWidget_2->setItem(7,2,itog_zhirkkal);
    }

    if(ui->tableWidget_2->item(10,0)->text().toFloat()>56){
        QTableWidgetItem* itog_ugl=new QTableWidgetItem;
        itog_ugl->setText("больше нормы");
        ui->tableWidget_2->setItem(10,2,itog_ugl);
    }
    else if (ui->tableWidget_2->item(10,0)->text().toFloat()<30) {
        QTableWidgetItem* itog_ugl=new QTableWidgetItem;
        itog_ugl->setText("меньше нормы");
        ui->tableWidget_2->setItem(10,2,itog_ugl);
ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(10)->text()+" "+ui->tableWidget_2->item(10,2)->text()+";\n"+"Чаще употреблять продукты, с высоким содержанием углеводов(мучные изделия, крупы, овощи и фрукты)"+";\n";
   i=i+1;
    }
    else {
        QTableWidgetItem* itog_ugl=new QTableWidgetItem;
        itog_ugl->setText("норма");
        ui->tableWidget_2->setItem(10,2,itog_ugl);
    }

    if(ui->tableWidget_2->item(13,0)->text().toFloat()<1000){
        QTableWidgetItem* itog_Ca=new QTableWidgetItem;
        itog_Ca->setText("меньше нормы");
        ui->tableWidget_2->setItem(13,2,itog_Ca);
        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(13)->text()+" "+ui->tableWidget_2->item(13,2)->text()+";\n"+"Увеличить потребление продуктов, содержащих кальций(твердые сыры, кунжут, фасоль, шоколад, рыба, творог)"+";\n";
   i=i+1;
    }
    else {
        QTableWidgetItem* itog_Ca=new QTableWidgetItem;
        itog_Ca->setText("норма");
        ui->tableWidget_2->setItem(13,2,itog_Ca);
    }
    if(ui->tableWidget_2->item(14,0)->text().toFloat()<800){
        QTableWidgetItem* itog_P=new QTableWidgetItem;
        itog_P->setText("меньше нормы");
        ui->tableWidget_2->setItem(14,2,itog_P);

        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(14)->text()+" "+ui->tableWidget_2->item(14,2)->text()+";\n"+"(Чаще употреблять продукты, содержащие фосфор(морская рыба, сыр, фасоль, гречневая крупа, горох, мясо)"+";\n";
    i=i+1;
    }
    else {
        QTableWidgetItem* itog_P=new QTableWidgetItem;
        itog_P->setText("норма");
        ui->tableWidget_2->setItem(14,2,itog_P);
    }
    if(ui->tableWidget_2->item(15,0)->text().toFloat()<90){
        QTableWidgetItem* itog_C=new QTableWidgetItem;
        itog_C->setText("меньше нормы");
        ui->tableWidget_2->setItem(15,2,itog_C);

        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(15)->text()+" "+ui->tableWidget_2->item(15,2)->text()+";\n"+"Чаще употреблять продукты, содержащие витамин C(цитрусовые, шиповник, капуста, облепиха, яблоко, черная смородина, помидоры)"+";\n";
    i=i+1;
    }
    else {
        QTableWidgetItem* itog_C=new QTableWidgetItem;
        itog_C->setText("норма");
        ui->tableWidget_2->setItem(15,2,itog_C);
    }
    if(ui->tableWidget_2->item(1,0)->text().toFloat()<ui->tableWidget_2->item(1,1)->text().toFloat())
    {
        QTableWidgetItem* itog_belk=new QTableWidgetItem;
        itog_belk->setText("ниже нормы");
        ui->tableWidget_2->setItem(1,2,itog_belk);
        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(1)->text()+" "+ui->tableWidget_2->item(1,2)->text()+";\n";
    i=i+1;
    }
    else
    {
        QTableWidgetItem* itog_belk=new QTableWidgetItem;
        itog_belk->setText("нормa");
      ui->tableWidget_2->setItem(1,2,itog_belk);
    }
    if(ui->tableWidget_2->item(5,0)->text().toFloat()<ui->tableWidget_2->item(5,1)->text().toFloat())
    {
        QTableWidgetItem* itog_ugl=new QTableWidgetItem;
        itog_ugl->setText("ниже нормы");
        ui->tableWidget_2->setItem(5,2,itog_ugl);
        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(5)->text()+" "+ui->tableWidget_2->item(5,2)->text()+";\n";
        i=i+1;
    }
    else
    {
        QTableWidgetItem* itog_ugl=new QTableWidgetItem;
        itog_ugl->setText("нормa");
        ui->tableWidget_2->setItem(5,2,itog_ugl);

    }

    if(ui->tableWidget_2->item(9,0)->text().toFloat()<ui->tableWidget_2->item(9,1)->text().toFloat())
    {
        QTableWidgetItem* itog_zhir=new QTableWidgetItem;
        itog_zhir->setText("ниже нормы");
        ui->tableWidget_2->setItem(9,2,itog_zhir);
        ending=ending+QString::number(i)+"."+ui->tableWidget_2->verticalHeaderItem(9)->text()+" "+ui->tableWidget_2->item(9,2)->text()+";\n";
        i=i+1;
    }
    else
    {
        QTableWidgetItem* itog_zhir=new QTableWidgetItem;
        itog_zhir->setText("норма");
        ui->tableWidget_2->setItem(9,2,itog_zhir);
    }

    if (IMT<17){
        ending=ending+QString::number(i)+"."+"Выраженный дефицит массы тела"+";\n";
        i=i+1;
    }
    else if (IMT>16 & IMT<18.5) {
        ending=ending+QString::number(i)+"."+"Недостаточная (дефицит) масса тела"+";\n";
        i=i+1;

    }
    else if (IMT>18.5 & IMT<25) {
        ending=ending+QString::number(i)+"."+"ИМТ: Норма"+";\n";
        i=i+1;
}
    else if (IMT>24 & IMT<30) {
        ending=ending+QString::number(i)+"."+"ИМТ: Избыточная масса тела"+";\n";
        i=i+1;
    }
    else if (IMT>29 & IMT<35) {
        ending=ending+QString::number(i)+"."+"ИМТ: Ожирение"+";\n";
        i=i+1;
    }
    else if (IMT>34 & IMT<40) {
        ending=ending+QString::number(i)+"."+"ИМТ: Ожирение резкое"+";\n";
        i=i+1;
    }
    else if (IMT>=40) {
        ending=ending+QString::number(i)+"."+"ИМТ: Очень резко выраженное ожирение"+";\n";
        i=i+1;
    }
    if (Pr>0.8 & ui->zen->isChecked()) {ending=ending+QString::number(i)+"."+"От/Об выше нормы"+";\n";
    i=i+1;}
    if (Pr>0.9 & ui->muz->isChecked()) {ending=ending+QString::number(i)+"."+"От/Об выше нормы"+";\n";
    i=i+1;}
    ui->textEdit->setText(ending);
}


void MainWindow::on_pushButton_6_clicked()
{
    QVBoxLayout *eda;

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
    if (ui->perekus2->isChecked()){
        eda=ui->verticalLayout_11;
    };


    QHBoxLayout *layout = new QHBoxLayout(this);    // создание горизонтального слоя QHBox (вертикальный QVBox)
        QLabel *lbl = new QLabel(ui->produkt_svoi->text() , this);  //создание лабеля
        QLabel *lbl1 = new QLabel(QString::number((ui->prod_kolvo_svoi_2->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        QLabel *lbl2 = new QLabel(QString::number((ui->prod_kolvo_svoi_3->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        QLabel *lbl3 = new QLabel(QString::number((ui->prod_kolvo_svoi_4->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        QLabel *lbl4 = new QLabel(QString::number((ui->prod_kolvo_svoi_5->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        QLabel *lbl5 = new QLabel(QString::number((ui->prod_kolvo_svoi_6->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        QLabel *lbl6 = new QLabel(QString::number((ui->prod_kolvo_svoi_7->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        QLabel *lbl7 = new QLabel(QString::number((ui->prod_kolvo_svoi_8->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        QLabel *lbl8 = new QLabel(QString::number((ui->prod_kolvo_svoi_9->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        QLabel *lbl9 = new QLabel(QString::number((ui->prod_kolvo_svoi_10->text().toFloat()/100)*ui->prod_kolvo_svoi->text().toFloat()) , this);
        lbl->setWordWrap(true);
        layout->addWidget(lbl,5);                     //запихиваем лабель в горизонтальный слой
        layout->addWidget(lbl1,3);
        layout->addWidget(lbl2,3);
        layout->addWidget(lbl3,3);
        layout->addWidget(lbl4,3);
        layout->addWidget(lbl5,3);
        layout->addWidget(lbl6,2);
        layout->addWidget(lbl7,2);
        layout->addWidget(lbl8,2);
        layout->addWidget(lbl9,2);

        eda->addLayout(layout); //запихиваем горизонтальный слой в вертикальный созданнвй в дизайнере
        eda->setAlignment(Qt::AlignTop);
        eda->setSpacing(10);


        if (ui->zavtrak->isChecked()){
           kkal_zavtrak=kkal_zavtrak + (lbl8->text().toFloat());
           zav_zhiv_belk=zav_zhiv_belk + (lbl1->text().toFloat());
           zav_rast_belk=zav_rast_belk + (lbl2->text().toFloat());
           zav_zhiv_zhir=zav_zhiv_zhir + (lbl3->text().toFloat());
           zav_rast_zhir=zav_rast_zhir + (lbl4->text().toFloat());
           zav_ugl=zav_ugl + (lbl5->text().toFloat());
           zav_Ca=zav_Ca + (lbl6->text().toFloat());
           zav_P=zav_P + (lbl7->text().toFloat());
           zav_C=zav_C + (lbl9->text().toFloat());


        };
        if (ui->obed->isChecked()){
           kkal_obed=kkal_obed + (lbl8->text().toFloat());
           obed_zhiv_belk=obed_zhiv_belk + (lbl1->text().toFloat());
           obed_rast_belk=obed_rast_belk + (lbl2->text().toFloat());
           obed_zhiv_zhir=obed_zhiv_zhir + (lbl3->text().toFloat());
           obed_rast_zhir=obed_rast_zhir + (lbl4->text().toFloat());
           obed_ugl=obed_ugl + (lbl5->text().toFloat());
           obed_Ca=obed_Ca + (lbl6->text().toFloat());
           obed_P=obed_P + (lbl7->text().toFloat());
           obed_C=obed_C + (lbl9->text().toFloat());
        };
        if (ui->uzin->isChecked()){
            kkal_uzin=kkal_uzin + (lbl8->text().toFloat());
            uzin_zhiv_belk=uzin_zhiv_belk + (lbl1->text().toFloat());
            uzin_rast_belk=uzin_rast_belk + (lbl2->text().toFloat());
            uzin_zhiv_zhir=uzin_zhiv_zhir + (lbl3->text().toFloat());
            uzin_rast_zhir=uzin_rast_zhir + (lbl4->text().toFloat());
            uzin_ugl=uzin_ugl + (lbl5->text().toFloat());
            uzin_Ca=uzin_Ca + (lbl6->text().toFloat());
            uzin_P=uzin_P + (lbl7->text().toFloat());
            uzin_C=uzin_C + (lbl9->text().toFloat());
        };
        if (ui->perekus->isChecked()){
            kkal_perekus=kkal_perekus + (lbl8->text().toFloat());
            perekus_zhiv_belk=perekus_zhiv_belk + (lbl1->text().toFloat());
            perekus_rast_belk=perekus_rast_belk + (lbl2->text().toFloat());
            perekus_zhiv_zhir=perekus_zhiv_zhir + (lbl3->text().toFloat());
            perekus_rast_zhir=perekus_rast_zhir + (lbl4->text().toFloat());
            perekus_ugl=perekus_ugl + (lbl5->text().toFloat());
            perekus_Ca=perekus_Ca + (lbl6->text().toFloat());
            perekus_P=perekus_P + (lbl7->text().toFloat());
            perekus_C=perekus_C + (lbl9->text().toFloat());
        };
        if (ui->perekus2->isChecked()){
            kkal_perekus2=kkal_perekus2 + (lbl8->text().toFloat());
            perekus2_zhiv_belk=perekus2_zhiv_belk + (lbl1->text().toFloat());
            perekus2_rast_belk=perekus2_rast_belk + (lbl2->text().toFloat());
            perekus2_zhiv_zhir=perekus2_zhiv_zhir + (lbl3->text().toFloat());
            perekus2_rast_zhir=perekus2_rast_zhir + (lbl4->text().toFloat());
            perekus2_ugl=perekus2_ugl + (lbl5->text().toFloat());
            perekus2_Ca=perekus2_Ca + (lbl6->text().toFloat());
            perekus2_P=perekus2_P + (lbl7->text().toFloat());
            perekus2_C=perekus2_C + (lbl9->text().toFloat());
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

        kkal =kkal + (lbl8->text().toFloat()); // сумма калорий (kkal обьявлен в заголовочном файле как float)
        ui->sum_kalori->setText(QString::number(kkal));
        ui->kkal_zav->setText(QString::number(kkal_zavtrak));
        ui->kkal_obed->setText(QString::number(kkal_obed));
        ui->kkal_uzin->setText(QString::number(kkal_uzin));
        ui->kkal_perekus->setText(QString::number(kkal_perekus));
        ui->kkal_perekus2->setText(QString::number(kkal_perekus2));

        ui->zav_zhiv_belk->setText(QString::number(zav_zhiv_belk));
        ui->zav_rast_belk->setText(QString::number(zav_rast_belk));
        ui->zav_zhiv_zhir->setText(QString::number(zav_zhiv_zhir));
        ui->zav_rast_zhir->setText(QString::number(zav_rast_zhir));
        ui->zav_C->setText(QString::number(zav_C));
        ui->zav_Ca->setText(QString::number(zav_Ca));
        ui->zav_P->setText(QString::number(zav_P));
        ui->zav_ugl->setText(QString::number(zav_ugl));

        ui->perekus_zhiv_belk->setText(QString::number(perekus_zhiv_belk));
        ui->perekus_rast_belk->setText(QString::number(perekus_rast_belk));
        ui->perekus_zhiv_zhir->setText(QString::number(perekus_zhiv_zhir));
        ui->perekus_rast_zhir->setText(QString::number(perekus_rast_zhir));
        ui->perekus_C->setText(QString::number(perekus_C));
        ui->perekus_Ca->setText(QString::number(perekus_Ca));
        ui->perekus_P->setText(QString::number(perekus_P));
        ui->perekus_ugl->setText(QString::number(perekus_ugl));

        ui->obed_zhiv_belk->setText(QString::number(obed_zhiv_belk));
        ui->obed_rast_belk->setText(QString::number(obed_rast_belk));
        ui->obed_zhiv_zhir->setText(QString::number(obed_zhiv_zhir));
        ui->obed_rast_zhir->setText(QString::number(obed_rast_zhir));
        ui->obed_C->setText(QString::number(obed_C));
        ui->obed_Ca->setText(QString::number(obed_Ca));
        ui->obed_P->setText(QString::number(obed_P));
        ui->obed_ugl->setText(QString::number(obed_ugl));

        ui->uzin_zhiv_belk->setText(QString::number(uzin_zhiv_belk));
        ui->uzin_rast_belk->setText(QString::number(uzin_rast_belk));
        ui->uzin_zhiv_zhir->setText(QString::number(uzin_zhiv_zhir));
        ui->uzin_rast_zhir->setText(QString::number(uzin_rast_zhir));
        ui->uzin_C->setText(QString::number(uzin_C));
        ui->uzin_Ca->setText(QString::number(uzin_Ca));
        ui->uzin_P->setText(QString::number(uzin_P));
        ui->uzin_ugl->setText(QString::number(uzin_ugl));

        ui->perekus2_zhiv_belk->setText(QString::number(perekus2_zhiv_belk));
        ui->perekus2_rast_belk->setText(QString::number(perekus2_rast_belk));
        ui->perekus2_zhiv_zhir->setText(QString::number(perekus2_zhiv_zhir));
        ui->perekus2_rast_zhir->setText(QString::number(perekus2_rast_zhir));
        ui->perekus2_C->setText(QString::number(perekus2_C));
        ui->perekus2_Ca->setText(QString::number(perekus2_Ca));
        ui->perekus2_P->setText(QString::number(perekus2_P));
        ui->perekus2_ugl->setText(QString::number(perekus2_ugl));
        ui->prod_kolvo_svoi->clear();
        ui->produkt_svoi->clear();
        ui->prod_kolvo_svoi_2->clear();
        ui->prod_kolvo_svoi_3->clear();
        ui->prod_kolvo_svoi_4->clear();
        ui->prod_kolvo_svoi_5->clear();
        ui->prod_kolvo_svoi_6->clear();
        ui->prod_kolvo_svoi_7->clear();
        ui->prod_kolvo_svoi_8->clear();
        ui->prod_kolvo_svoi_9->clear();
        ui->prod_kolvo_svoi_10->clear();
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->produkt->setEnabled(false);
    ui->prod_kolvo->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_6->setEnabled(true);
    ui->prod_kolvo_svoi->setEnabled(true);
    ui->produkt_svoi->setEnabled(true);
    ui->prod_kolvo_svoi_2->setEnabled(true);
    ui->prod_kolvo_svoi_3->setEnabled(true);
    ui->prod_kolvo_svoi_4->setEnabled(true);
    ui->prod_kolvo_svoi_5->setEnabled(true);
    ui->prod_kolvo_svoi_6->setEnabled(true);
    ui->prod_kolvo_svoi_7->setEnabled(true);
    ui->prod_kolvo_svoi_8->setEnabled(true);
    ui->prod_kolvo_svoi_9->setEnabled(true);
    ui->prod_kolvo_svoi_10->setEnabled(true);

}

void MainWindow::on_radioButton_clicked()
{
    ui->produkt->setEnabled(true);
    ui->prod_kolvo->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->produkt_svoi->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->prod_kolvo_svoi->setEnabled(false);
    ui->prod_kolvo_svoi_2->setEnabled(false);
    ui->prod_kolvo_svoi_3->setEnabled(false);
    ui->prod_kolvo_svoi_4->setEnabled(false);
    ui->prod_kolvo_svoi_5->setEnabled(false);
    ui->prod_kolvo_svoi_6->setEnabled(false);
    ui->prod_kolvo_svoi_7->setEnabled(false);
    ui->prod_kolvo_svoi_8->setEnabled(false);
    ui->prod_kolvo_svoi_9->setEnabled(false);
    ui->prod_kolvo_svoi_10->setEnabled(false);
}
