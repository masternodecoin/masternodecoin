#ifndef OKBOUNTYFORM_H
#define OKBOUNTYFORM_H

#include <QWidget>
#include <QClipboard>
#include <QDesktopServices>

#include "okb/okbwidget.h"

namespace Ui {
class okBountyForm;
}

class okBountyForm : public QWidget
{
    Q_OBJECT

public:
    explicit okBountyForm(OKBWidget *okbwidget,QWidget *parent = 0);
    ~okBountyForm();

private slots:
    void showOKBWidget();
    void on_checkBox_stateChanged(int arg1);
    void on_textBrowser_anchorClicked(const QUrl &arg1);

private:
    Ui::okBountyForm *ui;
    OKBWidget *okbWidget;
};

#endif // OKBOUNTYFORM_H
