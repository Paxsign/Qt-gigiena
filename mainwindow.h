#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

private:
    Ui::MainWindow *ui;
    double sum,sum_time,IMT,Pr;
    QStandardItemModel *csvModel;
    float belki, zhir, uglevod,zhiv_belk,rast_zhir ;
    float Ca, P, vC;
    float kkal;
    float kkal_zavtrak,zav_zhiv_belk,zav_rast_belk,zav_zhiv_zhir,zav_rast_zhir,zav_ugl,zav_Ca,zav_C,zav_P;
    float kkal_obed,obed_zhiv_belk,obed_rast_belk,obed_zhiv_zhir,obed_rast_zhir,obed_ugl,obed_Ca,obed_C,obed_P;
    float kkal_uzin,uzin_zhiv_belk,uzin_rast_belk,uzin_zhiv_zhir,uzin_rast_zhir,uzin_ugl,uzin_Ca,uzin_C,uzin_P;
    float kkal_perekus,perekus_zhiv_belk,perekus_rast_belk,perekus_zhiv_zhir,perekus_rast_zhir,perekus_ugl,perekus_Ca,perekus_C,perekus_P;
    float kkal_perekus2,perekus2_zhiv_belk,perekus2_rast_belk,perekus2_zhiv_zhir,perekus2_rast_zhir,perekus2_ugl,perekus2_Ca,perekus2_C,perekus2_P;
    float ub,zb;
};

#endif // MAINWINDOW_H
