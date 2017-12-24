#ifndef PSEARCHFORM_H
#define PSEARCHFORM_H

#include <QWidget>

namespace Ui {
class pSearchForm;
}

class pSearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit pSearchForm(QWidget *parent = 0);
    ~pSearchForm();

private:
    Ui::pSearchForm *ui;
};

#endif // PSEARCHFORM_H
