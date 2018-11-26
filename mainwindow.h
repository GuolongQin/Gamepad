#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <select.h>
#include <QVector>
#include <QtGamepad/QtGamepad>
#include <QEventLoop>
#include <pthread.h>
#include <unistd.h>

namespace Ui {
class mainwindow;
}

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = 0);
    QGamepad *m_gamepad;
    ~mainwindow();
    void Detected(int deviceID);

private slots:
    void on_btn_conn_clicked();

private:
    Ui::mainwindow *ui;

    double sense_val;
    double rocker_lx;
    double rocker_ly;

    pthread_t m_pthread;
    QEventLoop m_evloop;
private slots:
    void rocker_left_x(double arg);
    void rocker_right_x(double arg);
    void rocker_left_y(double arg);
    void rocker_right_y(double arg);

    void btn_left(bool arg);
    void btn_x(bool arg);
    void btn_y(bool arg);

    void l2_set(double arg);
    void r2_set(double arg);

    void mouse_left(bool arg);
    void mouse_right(bool arg);

    void timeout_handle();


    void on_sensor_valueChanged(int value);

    QVector<Select*> dd;
};

#endif // MAINWINDOW_H
