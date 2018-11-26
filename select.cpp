#include "select.h"
#include "ui_select.h"

Select::Select(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Select)
{
    ui->setupUi(this);
}

Select::~Select()
{
    delete ui;
}
