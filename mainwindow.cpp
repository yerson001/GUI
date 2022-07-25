#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "videocap.h"
#include <QKeyEvent>
#include <QDebug>
#include "ctello.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mOpenCV_videoCapture = new VideoCap(this);

    connect(mOpenCV_videoCapture, &VideoCap::newPixmapCapture, this, [&]()
    {
       ui->videoframe->setPixmap(mOpenCV_videoCapture->pixmap().scaled(640,480));
    });

}

MainWindow::~MainWindow()
{
    delete ui;
    mOpenCV_videoCapture->terminate();
}


void MainWindow::on_pushButton_clicked()
{
    mOpenCV_videoCapture->start(QThread::HighestPriority);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    qDebug() << event->text();

    if(event->text()=='w')
    {
        qDebug() <<"se presiona la W";
    }
    if(event->text()=='s')
    {
        qDebug() <<"se presiona la S";
    }
    if(event->text()=='d')
    {
        qDebug() <<"se presiona la D";
    }
    if(event->text()=='a')
    {
        qDebug() <<"se presiona la A";
    }
    if(event->text()=='l')
    {
        qDebug() <<"se presiona la L";
        tello.SendCommand("land");
    }
    if(event->text()=='t')
    {
        qDebug() <<"se presiona la T";
        tello.SendCommand("takeoff");
        //busy = true;
    }

}
