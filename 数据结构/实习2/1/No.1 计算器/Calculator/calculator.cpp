#include "calculator.h"
#include "ui_calculator.h"

calculator::calculator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calculator)
{
    ui->setupUi(this);
}

calculator::~calculator()
{
    delete ui;
}
