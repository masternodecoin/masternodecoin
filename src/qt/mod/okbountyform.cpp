#include "okbountyform.h"
#include "ui_okbountyform.h"

okBountyForm::okBountyForm(OKBWidget *okbwidget, QWidget *parent) :
    QWidget(parent),
    okbWidget(okbwidget),
    ui(new Ui::okBountyForm)
{
    ui->setupUi(this);
    ui->textBrowser->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->textBrowser_2->setTextInteractionFlags(Qt::NoTextInteraction);

    ui->checkBox->setChecked(false);//one key bounty function close at the beginning
}

okBountyForm::~okBountyForm()
{
    delete ui;
}

//
void okBountyForm::showOKBWidget()
{
    QString str = QApplication::clipboard()->text(); //
    //
    if(str.length() != 34)//
        return;
    if(str.at(0) != 'M')//
        return;

    for(int i=1;i< 34; i++)
    {
        QChar t = str.at(i);
        if(!((t>='a' && t<='z'|| t>='A'&&t<='Z')||( t>='0'&& t<='9')))
        {
            return;
        }
    }

    if(okbWidget)
        okbWidget->okbAction(str);
}

void okBountyForm::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->checkState() == Qt::Checked)
    {
        connect(QApplication::clipboard(),SIGNAL(dataChanged()),this,SLOT(showOKBWidget()));
    }else
    {
        disconnect(QApplication::clipboard(),SIGNAL(dataChanged()),this,SLOT(showOKBWidget()));
    }
}

void okBountyForm::on_textBrowser_anchorClicked(const QUrl &arg1)
{
    QDesktopServices::openUrl(arg1);
}
