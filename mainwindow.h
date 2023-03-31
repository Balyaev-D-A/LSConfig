#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QXmlStreamReader>

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
    struct CHANNEL {
        int num;
        bool enabled = false;
        QString deviceType;
        QString KKS;
    };
    struct LOCALSTATION {
        QString name;
        QString UNOKKS;
        quint8 address;
        CHANNEL channels[16];
    };
    QList<LOCALSTATION> m_localStations;
    Ui::MainWindow *ui;
    QXmlStreamReader m_xmlreader;
};
#endif // MAINWINDOW_H
