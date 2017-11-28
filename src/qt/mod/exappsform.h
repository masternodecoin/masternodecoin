#ifndef EXAPPSFORM_H
#define EXAPPSFORM_H

#include <QWidget>

namespace Ui {
class exAppsForm;
}

class exAppsForm : public QWidget
{
    Q_OBJECT

public:
    explicit exAppsForm(QWidget *parent = 0);
    ~exAppsForm();

private:
    Ui::exAppsForm *ui;
};

#endif // EXAPPSFORM_H
