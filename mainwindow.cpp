#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inputtime.h"
#include "ui_inputtime.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->pushButton, SIGNAL(clicked()),this,SLOT(startComputeButton_clicked()) );

    l_horizontalLayout = new QVBoxLayout(ui->listView);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::startComputeButton_clicked()
{
    qDebug()<<"开始执行: void MainWindow::startComputeButton_clicked()";
    //清空l_horizontalLayout布局内的所有元素
    if(ui->radioButton->isChecked()==true){
        qDebug()<<"twelve_hour_set = true";
        twelve_hour_set = true;
    }else{
        twelve_hour_set = false;
        qDebug()<<"twelve_hour_set = false";
    }

    QLayoutItem *child;
    while ((child = l_horizontalLayout->takeAt(0)) != 0)
    {
            //setParent为NULL，防止删除之后界面不消失
            if(child->widget())
            {
                child->widget()->setParent(NULL);
            }
            delete child;
    }
    QString work_day_qstr = ui->workDayEdit->text();
    qDebug() << work_day_qstr;

    if(work_day_qstr == ""){
        QMessageBox::information(this, "通知！", "请输入工作天数");
    }
    else{
        bool ok = false;
        work_day = work_day_qstr.toInt(&ok, 10);
        qDebug() << work_day;
        startComputeButton_next(0.0);
    }
}


void MainWindow::startComputeButton_next(double work_time)
{
    qDebug()<<"开始执行: void MainWindow::startComputeButton_next()";
    //启动inputtime.ui录入时间，返回work_time，再将work_time压入容器
    //day_show = 0表示还未启动inputtime.ui
    if(day_show != 0){
        work_time_list.push_back(work_time);
    }

    if(work_day == 0)
    {
        qDebug()<<"时长统计完成";
        double all_work_time = 0;
        double aver_work_time = 0;

        for (int i = 0; i < work_time_list.size(); i++)
        {
            qDebug() << work_time_list[i]<< " ";
            QString work_time_show = "第" + QString::number(i+1,10) + "天: " + QString::number(work_time_list[i],'f',2) + " h";
            QLabel* qlabel = new QLabel(work_time_show);
            l_horizontalLayout->addWidget(qlabel);
            all_work_time += work_time_list[i];
        }

        aver_work_time = all_work_time/work_time_list.size();
        QString all_work_time_show = "总时长: " + QString::number(all_work_time,'f',2) + " h";
        QString aver_work_time_show = "平均时长: " + QString::number(aver_work_time,'f',2) + " h";
        QLabel* qlabel_2 = new QLabel(all_work_time_show);
        QLabel* qlabel_3 = new QLabel(aver_work_time_show);
        l_horizontalLayout->addWidget(qlabel_2);
        l_horizontalLayout->addWidget(qlabel_3);

        work_time_list.clear();
        day_show = 0;
        ui->workDayEdit->clear();

        return;
    }
    //work_day:录入的天数，day_show:录入第day_show天。
    work_day--;
    day_show++;
    InputTime* inputtime_obj = new InputTime(day_show,twelve_hour_set,std::bind(&MainWindow::startComputeButton_next,this,std::placeholders::_1) );
}

void MainWindow::radioButton(){
//    if(ui->radioButton->isCheckable()==true){
//        qDebug()<<"twelve_hour_set = true";
//        twelve_hour_set = true;
//    }else{
//        twelve_hour_set = false;
//        qDebug()<<"twelve_hour_set = false";
//    }
}
