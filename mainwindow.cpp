#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QCursor>
#include <windows.h>

double val_rocker_lx;
double val_rocker_ly;
double val_rocker_l2;
double val_rocker_r2;

int val;

void *Thread_Handle(void* arg){


    printf("\r\n Thread Entered\r\n");
    for(;;){
        usleep(10000);
        QPoint pos = QCursor::pos();
        pos.setX(pos.x()+val*val_rocker_lx*(0.5+val_rocker_l2)*(1.3-val_rocker_r2));
        pos.setY(pos.y()+val*val_rocker_ly*(0.5+val_rocker_l2)*(1.3-val_rocker_r2));
        QCursor::setPos(pos);
    }



}

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    this->ui->sp_l->setDecimals(6);
    this->ui->sp_r->setDecimals(6);
    this->ui->sp_lw->setDecimals(6);
    this->ui->sp_ls->setDecimals(6);
    this->ui->sp_la->setDecimals(6);
    this->ui->sp_ld->setDecimals(6);
    this->ui->sp_rw->setDecimals(6);
    this->ui->sp_rs->setDecimals(6);
    this->ui->sp_ra->setDecimals(6);
    this->ui->sp_rd->setDecimals(6);

    this->sense_val = 10;
    this->rocker_lx = 0;
    this->rocker_ly = 0;

    val_rocker_lx = 0;
    val_rocker_ly = 0;

    val_rocker_l2 = 0;
    val_rocker_r2 =0;

    this->ui->sensor->setValue(15);
    val = this->ui->sensor->value();

    pthread_create(&this->m_pthread,NULL,Thread_Handle,NULL);

}

mainwindow::~mainwindow()
{
    delete ui;
}


void mainwindow::Detected(int deviceID){

    qDebug()<<"deviceID";

}

void mainwindow::on_btn_conn_clicked()
{
    this->m_gamepad = new QGamepad(0,this);
    if(this->m_gamepad->isConnected()){
        connect(this->m_gamepad,SIGNAL(axisLeftXChanged(double)),this,SLOT(rocker_left_x(double)));
        connect(this->m_gamepad,SIGNAL(axisLeftYChanged(double)),this,SLOT(rocker_left_y(double)));
        connect(this->m_gamepad,SIGNAL(axisRightXChanged(double)),this,SLOT(rocker_right_x(double)));
        connect(this->m_gamepad,SIGNAL(axisRightYChanged(double)),this,SLOT(rocker_right_y(double)));
        connect(this->m_gamepad,SIGNAL(buttonR1Changed(bool)),this,SLOT(btn_left(bool)));
        connect(this->m_gamepad,SIGNAL(buttonXChanged(bool)),this,SLOT(btn_x(bool)));
        connect(this->m_gamepad,SIGNAL(buttonYChanged(bool)),this,SLOT(btn_y(bool)));

        connect(this->m_gamepad,SIGNAL(buttonL2Changed(double)),this,SLOT(l2_set(double)));
        connect(this->m_gamepad,SIGNAL(buttonR2Changed(double)),this,SLOT(r2_set(double)));

        connect(this->m_gamepad,SIGNAL(buttonXChanged(bool)),this,SLOT(mouse_left(bool)));
        connect(this->m_gamepad,SIGNAL(buttonYChanged(bool)),this,SLOT(mouse_right(bool)));

    }else{
        return;
    }
}

void mainwindow::rocker_left_x(double arg){
    qDebug()<<arg;
    if(arg>0){
        this->ui->sp_la->setValue(arg);
        this->ui->sp_ld->setValue(0);
    }else{
        this->ui->sp_la->setValue(0);
        this->ui->sp_ld->setValue(-arg);
    }
    val_rocker_lx = arg;
}
void mainwindow::rocker_left_y(double arg){
    qDebug()<<arg;
    if(arg>0){
        this->ui->sp_lw->setValue(arg);
        this->ui->sp_ls->setValue(0);
    }else{
        this->ui->sp_lw->setValue(0);
        this->ui->sp_ls->setValue(-arg);
    }
    val_rocker_ly = arg;
}

void mainwindow::rocker_right_x(double arg){
    qDebug()<<arg;
    if(arg>0){
        this->ui->sp_ra->setValue(arg);
        this->ui->sp_rd->setValue(0);
    }else{
        this->ui->sp_ra->setValue(0);
        this->ui->sp_rd->setValue(-arg);
    }



}
void mainwindow::rocker_right_y(double arg){
    qDebug()<<arg;
    if(arg>0){
        this->ui->sp_rw->setValue(arg);
        this->ui->sp_rs->setValue(0);

    }else{
        this->ui->sp_rw->setValue(0);
        this->ui->sp_rs->setValue(-arg);
    }

}

void mainwindow::timeout_handle(){

    if(!this->m_gamepad->isConnected()){
        return;
    }
    QPoint pos = QCursor::pos();
    pos.setX(pos.x()+this->sense_val*this->rocker_lx);
    pos.setY(pos.y()+this->sense_val*this->rocker_ly);
    QCursor::setPos(pos);
}

void mainwindow::mouse_left(bool arg){
    INPUT buffer[1];
    memset(buffer,0,sizeof(INPUT));
    buffer[0].type = INPUT_MOUSE;
    if(arg==true){
        buffer[0].mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
        SendInput(1,buffer,sizeof(INPUT));
    }else{
        buffer[0].mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
        SendInput(1,buffer,sizeof(INPUT));
    }
}
void mainwindow::mouse_right(bool arg){
    INPUT buffer[1];
    memset(buffer,0,sizeof(INPUT));
    buffer[0].type = INPUT_MOUSE;
    if(arg==true){
        buffer[0].mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN);
        SendInput(1,buffer,sizeof(INPUT));
    }else{
        buffer[0].mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTUP);
        SendInput(1,buffer,sizeof(INPUT));
    }
}


void mainwindow::l2_set(double arg){
    val_rocker_l2 = arg;


}
void mainwindow::r2_set(double arg){

    val_rocker_r2 = arg;

}
void mainwindow::on_sensor_valueChanged(int value)
{
    val = value;
}


void mainwindow::btn_left(bool arg){
    INPUT buffer[1];
    memset(buffer,0,sizeof(INPUT));
    buffer[0].type = INPUT_MOUSE;
    if(arg==true){
        buffer[0].mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEDOWN);
        SendInput(1,buffer,sizeof(INPUT));
    }else{
        buffer[0].mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEUP);
        SendInput(1,buffer,sizeof(INPUT));
    }
}


void mainwindow::btn_x(bool arg){

}
void mainwindow::btn_y(bool arg){


}
