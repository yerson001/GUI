#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videocap.h"
#include "ctello.h"
using ctello::Tello;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    VideoCap *mOpenCV_videoCapture;
protected:
     void keyPressEvent(QKeyEvent* event);
     Tello tello{};
};
#endif // MAINWINDOW_H
