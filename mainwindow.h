
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myjson.h"
#include "mytimer.h"
#include "qtimer.h"
#include <QMainWindow>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void timeChanged();
    void saveJson();

private slots:
    void viewFillTasks();
    void on_pushButton_start_clicked();

    void on_pushButton_pause_clicked();

    void on_pushButton_stop_clicked();

    void initEnables();
    void on_pushButton_delete_clicked();

    void on_pushButton_add_clicked();

    void on_lineEdit_task_name_textChanged(const QString &arg1);

    void on_comboBox_tasks_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    myJson json;
    myTimer * time;

    timeModel *currentTaskTime;
    timeModel *globalTime;

    bool isWorking = false;
};

#endif // MAINWINDOW_H
