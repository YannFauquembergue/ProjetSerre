#pragma once

#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
//#include <QSettings>
#include <QTimer>
#include "QModbusTcpClient.h"

struct ValuesX
{
    float sensorInput1;   // Température extérieure
    float debitEauCourante;
    float debitEauPluie;

    bool level;
    bool eau;
};

class Poseidon2 : public QModbusTcpClient
{
    Q_OBJECT

public:
    Poseidon2(QString ip, int port = 502, QObject* parent = nullptr);
    ~Poseidon2();

    void trameLevel();
    void trameDebit();
    void trameTemperature();

public slots:
    void resetCounterDebit();
    void activatePump();
    void stopPump();
    void eauPluie();
    void eauCourante();
    void reseauEau();

    void onFC4ResultReceived(quint16 startAddress, QVector<quint16> values);
    void onFC2ResultReceived(quint16 startAddress, QVector<bool> values);

    ValuesX getValues() { return dataCache; }
private:
    ValuesX dataCache;
};
