#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>
#include "stationmanager.h"
#include "stationselectform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    StationManager::Station currStation;
    StationSelectForm *stationSelForm;

private slots:
    void stationSelFormClosed();
    void connectActionTriggered();
    void stationChoosed(int index);
};
#endif // MAINWINDOW_H
