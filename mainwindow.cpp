#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
#include <QThreadPool>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1.创建任务类对象
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;

    //主线程发送个数给子线程,指向17行
    connect(this,&MainWindow::starting,gen,&Generate::recvNum);
    //2.启动子线程
    connect(ui->startButton,&QPushButton::clicked,this,[=]()
    {
        emit starting(10000);
        QThreadPool::globalInstance()->start(gen);
    });
    //接受排序数据
    connect(gen,&Generate::sendData,bubble,&BubbleSort::recvArray);
    connect(gen,&Generate::sendData,quick,&QuickSort::recvArray);

    //接受子线程发送的数据
    connect(gen,&Generate::sendData,[=](QVector<int> list)
    {
        QThreadPool::globalInstance()->start(bubble);
        QThreadPool::globalInstance()->start(quick);
        for (int i =0;i<list.size();i++) {
            ui->randomList->addItem(QString::number(list.at(i)));

        }
    });
    connect(bubble,&BubbleSort::finish,[=](QVector<int> list)
    {
        for (int i =0;i<list.size();i++) {
            ui->bubbleList->addItem(QString::number(list.at(i)));

        }
    });
    connect(quick,&QuickSort::finish,[=](QVector<int> list)
    {
        for (int i =0;i<list.size();i++) {
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

