#include "inputtime.h"
#include "ui_inputtime.h"
#include <QDebug>

InputTime::InputTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputTime)
{
    ui->setupUi(this);
}


InputTime::InputTime(int day_show, bool twelve_hour_set, std::function<void(double work_time)> callback_f):
    ui(new Ui::InputTime), twelve_hour_flag(twelve_hour_set), callback(callback_f)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, &QPushButton::clicked,this,&InputTime::RunInput);
    connect(ui->pushButton, &QPushButton::clicked,this,&InputTime::CancelInput);

    QIntValidator *validator = new QIntValidator(0, 600, this);
    ui->lineEdit->setValidator(validator);

    QString tem_str = "第" + QString::number(day_show,10) + "天";
    ui->label->setText(tem_str);


    if(twelve_hour_flag == true){
        qDebug()<<"使用12小时制";
        QTime maxtime(11,59,59);
        QTime mintime(00,00,00);
        ui->timeEdit->setMaximumTime(maxtime);
        ui->timeEdit->setMinimumTime(mintime);
        ui->timeEdit_2->setMaximumTime(maxtime);
        ui->timeEdit_2->setMinimumTime(mintime);
    }
    this->setWindowTitle("输入工时");
    show();

}


InputTime::~InputTime()
{
    delete ui;
}


void InputTime::RunInput(){

    qDebug()<<"开始执行: InputTime::RunInput()";
    double work_hour = 0;
    if(twelve_hour_flag == false){

        int start_hour = ui->timeEdit_2->time().hour();
        int start_min = ui->timeEdit_2->time().minute();
        int end_hour = ui->timeEdit->time().hour();
        int end_min = ui->timeEdit->time().minute();
        if(end_min < start_min){
            end_hour -= 1;
            end_min += 60;
        }
        if(end_hour < start_hour){
            end_hour += 24;
        }
        work_hour = end_hour - start_hour + (end_min-start_min)/60.0;
        if(ui->lineEdit->text()!=""){
            work_hour = work_hour - ui->lineEdit->text().toDouble()/60.0;
        }
    }
    else{
        int start_hour = ui->timeEdit_2->time().hour();
        int start_min = ui->timeEdit_2->time().minute();
        int end_hour = ui->timeEdit->time().hour();
        int end_min = ui->timeEdit->time().minute();
        if(end_min < start_min){
            end_hour -= 1;
            end_min += 60;
        }
        if(end_hour <= start_hour){
            end_hour += 12;
        }
        work_hour = end_hour - start_hour + (end_min-start_min)/60.0;
        if(ui->lineEdit->text()!=""){
            work_hour = work_hour - ui->lineEdit->text().toDouble()/60.0;
        }
    }


    qDebug()<<"work_hour: "<<work_hour;
    close();
    callback(work_hour);
}

void InputTime::CancelInput(){

    qDebug()<<"***InputTime::CancelInput()***";
    ui->timeEdit->clear();
    ui->timeEdit_2->clear();
}
