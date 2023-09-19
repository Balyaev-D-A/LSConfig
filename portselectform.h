#ifndef PORTSELECTFORM_H
#define PORTSELECTFORM_H

#include <QWidget>

namespace Ui {
class PortSelectForm;
}

class PortSelectForm : public QWidget
{
    Q_OBJECT

public:
    explicit PortSelectForm(QWidget *parent = nullptr);
    ~PortSelectForm();

private:
    Ui::PortSelectForm *ui;
};

#endif // PORTSELECTFORM_H
