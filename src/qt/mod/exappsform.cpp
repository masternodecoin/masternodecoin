#include "exappsform.h"
#include "ui_exappsform.h"

exAppsForm::exAppsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exAppsForm)
{
    ui->setupUi(this);
}

exAppsForm::~exAppsForm()
{
    delete ui;
}
