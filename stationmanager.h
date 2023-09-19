#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H
#include <QString>
#include <QList>

class StationManager
{
public:
    struct Channel {
        bool active;
        QString kks;
        QString detType;
    };

    struct Station {
        QString name;
        QString kks;
        int address;
        Channel channels[16];
    };

    typedef QList<Station> StationList;

    static StationManager* instance();
    StationList allStations();
    bool setCurrentStationByKKS(QString KKS);
    bool setCurrentStationByName(QString Name);
    Station currentStation();

private:
    int m_currStationIndex;
    StationList m_stationList;
    StationManager();
    ~StationManager();
    static StationManager *m_instance;
};

#endif // STATIONMANAGER_H
