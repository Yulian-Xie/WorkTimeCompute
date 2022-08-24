#ifndef INPUTTIME_H
#define INPUTTIME_H

#include <QWidget>
#include <future>


namespace Ui {
class InputTime;
}

class InputTime : public QWidget
{
    Q_OBJECT

public:
    explicit InputTime(QWidget *parent = nullptr);
    InputTime(int day_show,bool twelve_hour_flag,std::function<void(double work_time)> callback = nullptr);
    ~InputTime();

public:
    Ui::InputTime *ui;
    QVector<double> *work_time_list;
    static std::future<std::tuple<int,std::string>> AsycnExecute(InputTime* intputtime);
    bool twelve_hour_flag = false;

private:
    std::function<void(double work_time)> callback;

private slots:
    void RunInput();
    void CancelInput();

};

#endif // INPUTTIME_H
