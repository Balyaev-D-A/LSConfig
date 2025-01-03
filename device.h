#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QSerialPort>
#include "settings.h"

#define NOERROR "Нет ошибки."

class Device
{
public:
    // Статусные признаки
    static const quint32 ST_SWITCH		= 0x00000001;
    static const quint32 ST_FAILURE		= 0x00000002;
    static const quint32 ST_SIGNALIZATOR	= 0x00000004;
    static const quint32 ST_VALVE		= 0x00000008;
    static const quint32 ST_VALVE_STATE	= 0x00000010;
    static const quint32 ST_ACTIVE		= 0x00000040;
    static const quint32 ST_NOT_RELIABLE	= 0x00000100;
    static const quint32 ST_IMITATION	= 0x00000200;
    static const quint32 ST_NO_SIGNAL	= 0x00000400;
    static const quint32 ST_EX_RATE		= 0x00000800;
    static const quint32 ST_EX_COMP		= 0x00001000;
    static const quint32 ST_AIR_CONSUM	= 0x00002000;
    static const quint32 ST_EX_LO_RANGE	= 0x00004000;
    static const quint32 ST_EX_HI_RANGE	= 0x00008000;
    static const quint32 ST_EX_LO_LIM1 	= 0x00010000;
    static const quint32 ST_EX_HI_LIM1 	= 0x00020000;
    static const quint32 ST_EX_LO_LIM2 	= 0x00010000;
    static const quint32 ST_EX_HI_LIM2 	= 0x00020000;

    enum {iChannelNumb = 16};

    struct TChannelInfo {
        // Статусные признаки
        quint32		m_dwState;
        // Измеренное значение
        float		m_fsValue;
    };

    struct TDeviceInfo {
        // Код устройства
        char			m_chDeviceId[32];
        // Обобщенное состояние устройства
        quint8			m_byDeviceStatus;
        // Признаки обобщенной неисправности модулей
        quint8			m_byAllModErrors;
        // Признаки обобщенной неисправности каналов
        quint16			m_wAllChnErrors;
        // Текущее время в устройстве
        quint32			m_dwCurrTime;
        // Информация по основным и альтернативным каналам
        TChannelInfo	m_cInfo[iChannelNumb];
    };

    // Конфигурация измерительного канала
    struct TChannelConfig {
        // Код размерности
        quint16        m_wUOMCode;
        // Код типа датчика
        quint16        m_wDetCode;
        // Максимально допустимая скорость счета
        float       m_fMaxRate;
        // Коэффициент масштабирования
        float       m_fScaleCoeff;
        // Собственный фон
        float       m_fBackground;
        // "Мертвое" время
        float       m_fDeadTime;
        // Нижняя граница диапазона измерения
        float       m_fMinValue;
        // Верхняя граница диапазона измерения
        float       m_fMaxValue;
        // Период контроля работоспособности
        quint16        m_wCheckTime;
        // Максимальное время измерения
        quint16        m_wMaximTime;
        // Порог 1
        float       m_fThreshold1;
        // Порог 2
        float       m_fThreshold2;
    };

    // Конфигурация устройства
    struct TDeviceConf {
        // Конфигурация измерительных каналов
        TChannelConfig		ChanConf[iChannelNumb];
        // Адрес в сети
        quint16                wAddress;
        // Идентификатор устройства
        char                szDeviceId[13];
    };

//    typedef float EX_CONST[2][iChannelNumb];

//    typedef struct {
//        quint8	byNumb;
//        float	faCoef[6];
//    } TERM_COEFF;

    enum ECommandCode {
            ccGetCurrentInfo			=  0,
            ccFullTest					=  1,
            ccImitationMode				=  2,
            ccNormalMode				=  3,
            ccPutConfig					=  4,
            ccGetConfig					=  5,
            ccSetDateTime				=  6,
            ccOpenValve					=  7,
            ccCloseValve				=  8,
            ccSetValveAutoMode			=  9,
            ccSetAddress				= 15,
            ccSetIdentificator			= 17,
            ccSetExConst				= 21,
            ccGetExConst				= 22,
            ccSetTermCoeff				= 23,
            ccGetTermCoeff				= 24,
            ccReadArchive				= 25,
            ccStopArchive				= 26,
            ccPutImitVal				= 50,
            ccGetImitVal				= 51
        };
        enum EResultsCode {
            rcSuccess 		= 0x0000,
            rcInProgress 	= 0x0001,
            rcUnknownError  = 0xFFFF,
            rcI2CError 		= 0xFFFE,
            rcWrEEPROMError = 0xFFFD,
            rcRdEEPROMError = 0xFFFC,
            rcNoResponse 	= 0xFFFB
        };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    explicit Device();
    ~Device();
    bool connectToDevice(QString port, quint8 address);
    void disconnectDevice();
    bool getCurrentInfo(Device::TDeviceInfo *devInfo);
    bool getCurrentConfig(Device::TDeviceConf *devConf);
    bool getChannelConfig(uint channel, TChannelConfig *config);
    bool putConfig(Device::TDeviceConf *devConf);
    bool putChannelConfig(uint channel, TChannelConfig *config);
    bool saveConfigToEEPROM();
    bool isConnected();
    QString errorString();
private:
    QSerialPort *m_pPort;
    bool m_connected = false;
    int m_failedRequestCount = 0;
    quint8 m_address = 0;
    QString m_errorString;
    Settings *m_settings;
    bool readHoldingRegisters(quint16 start, quint16 count, char *result);
    bool writeHoldingRegisters(quint16 start, quint16 count, char *data);
    bool executeCommand(quint16 *cmdData, quint16 cmdSize);
};

#endif // DEVICE_H
