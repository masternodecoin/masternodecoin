#include "psearchform.h"
#include "ui_psearchform.h"

pSearchForm::pSearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pSearchForm)
{
    ui->setupUi(this);
}

pSearchForm::~pSearchForm()
{
    delete ui;
}
