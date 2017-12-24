#ifndef OKBOUNTYFORM_H
#define OKBOUNTYFORM_H

#include <QWidget>

namespace Ui {
class okBountyForm;
}

class okBountyForm : public QWidget
{
    Q_OBJECT

public:
    explicit okBountyForm(QWidget *parent = 0);
    ~okBountyForm();

private:
    Ui::okBountyForm *ui;
};

#endif // OKBOUNTYFORM_H
