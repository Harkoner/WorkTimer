
#include "mainwindow.h"
#include "myjson.h"
#include "mytimer.h"
#include "ui_mainwindow.h"

#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    time = new myTimer();
    connect(time, &myTimer::timeChanged, this, &MainWindow::timeChanged);

    // init json
    json.read();
    QTimer* saveTimer = new QTimer(this);
    connect(saveTimer, &QTimer::timeout, this, &MainWindow::saveJson);
    saveTimer->start(60000);

    // init view
    viewFillTasks();
    initEnables();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initEnables()
{
    ui->label_all_time->setText("");
    ui->label_real_time->setText("");

    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_add->setEnabled(false);
    if(ui->comboBox_tasks->currentText() == "")
    {
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_start->setEnabled(false);
    }
    else
    {
        ui->pushButton_delete->setEnabled(true);
        ui->pushButton_start->setEnabled(true);
    }
}

void MainWindow::viewFillTasks()
{
//    ui->comboBox_tasks->addItem(" ");

    for(const taskModel &task : json.tasks)
    {
        if(!task.expired)
        {
            ui->comboBox_tasks->addItem(task.title);
        }
    }
}

void MainWindow::on_pushButton_start_clicked()
{
    time->stop();
    isWorking = true;
    QString currentTaskStr = ui->comboBox_tasks->currentText();
    taskModel *task = json.getTaskByTitle(currentTaskStr);
    if(task != nullptr)
    {
        // to setup current task to timer
        time->xtaskTime = &task->time;
        time->xglobalTime = &json.global;
        time->setConnection(&task->time, &json.global);

        // to read current data from time
        currentTaskTime = &task->time;
        globalTime = &json.global;
        time->start();

        // ui view things
        ui->pushButton_pause->setEnabled(true);
        ui->pushButton_stop->setEnabled(true);
        ui->pushButton_start->setEnabled(false);
    }
}

void MainWindow::on_pushButton_pause_clicked()
{
//    time->pause();
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
}


void MainWindow::on_pushButton_stop_clicked()
{
    // clear interface
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_pause->setEnabled(false);
    ui->pushButton_stop->setEnabled(false);
    time->stop();
    isWorking = false;
    saveJson();
}

void MainWindow::timeChanged()
{
    QString myText;
    QString sec = QString::number(currentTaskTime->seconds);
    QString minutes = QString::number(currentTaskTime->minutes);
    QString hours = QString::number(currentTaskTime->hours);
    myText = hours + ":" + minutes + ":" + sec;
    ui->label_real_time->setText(myText);

    QString gmyText;
    QString gsec = QString::number(globalTime->seconds);
    QString gminutes = QString::number(globalTime->minutes);
    QString ghours = QString::number(globalTime->hours);
    QString gdays = QString::number(globalTime->days);
    gmyText = gdays + ":" + ghours + ":" + gminutes + ":" + gsec;
    ui->label_all_time->setText(gmyText);
}

void MainWindow::saveJson()
{
    json.save();
}

void MainWindow::on_pushButton_delete_clicked()
{
    QString currentTaskStr = ui->comboBox_tasks->currentText();
    ui->comboBox_tasks->removeItem(ui->comboBox_tasks->currentIndex());

    taskModel *task = json.getTaskByTitle(currentTaskStr);
    if(task != nullptr)
    {
        task->expired = true;
    }
    saveJson();
}


void MainWindow::on_pushButton_add_clicked()
{
    QString newTaskStr = ui->lineEdit_task_name->text();
    taskModel *xtask = json.getTaskByTitle(newTaskStr);

    if(xtask != nullptr)
    {
        xtask->expired = false;
        saveJson();
        ui->comboBox_tasks->addItem(newTaskStr);
        ui->comboBox_tasks->setCurrentText(newTaskStr);
        ui->lineEdit_task_name->setText("");
        return;
    }

    taskModel task;
    task.title = newTaskStr;
    json.tasks.append(task);
    saveJson();

    ui->comboBox_tasks->addItem(newTaskStr);
    ui->comboBox_tasks->setCurrentText(newTaskStr);

    ui->lineEdit_task_name->setText("");
}


void MainWindow::on_lineEdit_task_name_textChanged(const QString &arg1)
{
    if(arg1 == "")
        ui->pushButton_add->setEnabled(false);
    else
        ui->pushButton_add->setEnabled(true);
}


void MainWindow::on_comboBox_tasks_currentIndexChanged(int index)
{
    if(ui->comboBox_tasks->currentText() == "")
    {
        ui->pushButton_delete->setEnabled(false);
        ui->pushButton_start->setEnabled(false);
    }
    else
    {
        ui->pushButton_delete->setEnabled(true);
        ui->pushButton_start->setEnabled(true);
    }
}

