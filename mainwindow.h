#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QVBoxLayout>

#include "inputtime.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QVector<double> work_time_list;
    int work_day=0;
    int day_show=0;
    bool twelve_hour_set = false;
    InputTime* inputtime;
    QVBoxLayout* l_horizontalLayout;

private:
     void startComputeButton_next(double work_time);

private slots:
    void startComputeButton_clicked();
    void radioButton();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
