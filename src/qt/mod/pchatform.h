#ifndef PCHATFORM_H
#define PCHATFORM_H

#include <QWidget>

namespace Ui {
class pchatForm;
}

class pchatForm : public QWidget
{
    Q_OBJECT

public:
    explicit pchatForm(QWidget *parent = 0);
    ~pchatForm();

private:
    Ui::pchatForm *ui;
};

#endif // PCHATFORM_H
