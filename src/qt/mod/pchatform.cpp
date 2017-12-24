#include "pchatform.h"
#include "ui_pchatform.h"

pchatForm::pchatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pchatForm)
{
    ui->setupUi(this);
}

pchatForm::~pchatForm()
{
    delete ui;
}
