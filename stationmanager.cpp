#include "stationmanager.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QApplication>

StationManager *StationManager::m_instance = 0;

StationManager* StationManager::instance()
{
    if (m_instance == 0) m_instance = new StationManager();
    return m_instance;
}

StationManager::StationManager()
{
    QFile file(QApplication::applicationDirPath() + "/localstations.xml");
    Station station;
    QXmlStreamAttributes attrs;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QXmlStreamReader xml(&file);
        while (!xml.atEnd() && !xml.hasError())
        {
            xml.readNext();
            if (xml.isStartDocument()) continue;
            if (xml.isStartElement()) {
                if (xml.name() != "Localstation") continue;
                attrs = xml.attributes();
                if (!attrs.hasAttribute("addr")) continue;
                station.address = attrs.value("addr").toInt();
                if (attrs.hasAttribute("name")) station.name = attrs.value("name").toString();
                else station.name = "Нет имени";
                if (attrs.hasAttribute("kks")) station.kks = attrs.value("kks").toString();
                else station.kks = "Нет KKS";
                for (int i=0; i<15; i++) station.channels[i].active = false;
                while (!((xml.isEndElement()) && (xml.name() == "Localstation")))
                {
                    xml.readNext();
                    if (xml.isStartElement()) {
                        if (xml.name() != "Channel") continue;
                        attrs = xml.attributes();
                        int num = attrs.value("num").toInt() - 1;
                        station.channels[num].active = true;
                        while (!((xml.isEndElement()) && (xml.name() == "Channel")))
                        {
                            xml.readNext();
                            if (xml.isStartElement() && xml.name() == "KKS") {
                                station.channels[num].kks = xml.readElementText();
                                continue;
                            }
                            if (xml.isStartElement() && xml.name() == "Type") {
                                station.channels[num].detType = xml.readElementText();
                                continue;
                            }
                        }
                    }
                }
                m_stationList.append(station);
            }
        }
    }

}

StationManager::StationList StationManager::allStations()
{
    return m_stationList;
}
