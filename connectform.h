#ifndef CONNECTFORM_H
#define CONNECTFORM_H

#include <QWidget>

namespace Ui {
class ConnectForm;
}

class ConnectForm : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectForm(QWidget *parent = nullptr);
    ~ConnectForm();

private:
    Ui::ConnectForm *ui;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void updatePortInfo();
    void on_connectButton_clicked();
    void on_cancelButton_clicked();

    void on_portBox_currentIndexChanged(const QString &text);

signals:
    void choosed();
    void closed();
};

#endif // CONNECTFORM_H
