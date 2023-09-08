#ifndef STATIONSELECTFORM_H
#define STATIONSELECTFORM_H

#include <QWidget>

namespace Ui {
class StationSelectForm;
}

class StationSelectForm : public QWidget
{
    Q_OBJECT

public:
    explicit StationSelectForm(QWidget *parent = nullptr);
    ~StationSelectForm();

private slots:
    void on_chooseButton_clicked();

private:
    Ui::StationSelectForm *ui;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void choosed(int index);
    void closed();
};

#endif // STATIONSELECTFORM_H
