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

private:
    Ui::MainWindow *ui;
    double sum;
    QStandardItemModel *csvModel;
    float kkal;
    float kkal_zavtrak;
    float kkal_obed;
    float kkal_uzin;
    float kkal_perekus;
};

#endif // MAINWINDOW_H
