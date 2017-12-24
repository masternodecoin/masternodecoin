#include "okbountyform.h"
#include "ui_okbountyform.h"

okBountyForm::okBountyForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::okBountyForm)
{
    ui->setupUi(this);
}

okBountyForm::~okBountyForm()
{
    delete ui;
}
