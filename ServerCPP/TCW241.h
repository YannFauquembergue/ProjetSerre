#pragma once

#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
//#include <QSettings>
#include <math.h>
#include "QModbusTcpClient.h"

struct Values
{
    float analogInput1;   // Humidité sol 1
    float analogInput2;   // Humidité sol 2
    float analogInput3;   // Humidité sol 3

    float sensorInput1;   // Température intérieure
    float sensorInput2;   // Humidité intérieure

    float consoElectrique; // Humitdité 1 + 2 + 3 (Volts)

    bool isArrosoir; // Etat Arrosoir
    bool isBrumisation; // Etat Brumisation
    bool isVerinFenetre; // Etat VerinFenetre
    bool isChauffage1; // Etat Chauffage1
};

class TCW241 : public QModbusTcpClient
{
    Q_OBJECT

public:
    TCW241(QString ip, int port = 502, QObject * parent = nullptr);
    ~TCW241();

    //fonctions pour allumer ou eteindre l'arrosoir
    void Relay1ON(); void Relay1OFF();
    //fonctions pour allumer ou eteindre la brumisation
    void Relay2ON(); void Relay2OFF();
    //fonctions pour allumer ou eteindre le chauffage
    void Relay3ON(); void Relay3OFF();
    //fonctions pour ouvrir ou fermer la fenetre
    void Relay4ON(); void Relay4OFF();

public slots:
    void readData1();
    void readData2();

    void onFC3ResultReceived(quint16 startAddress, QVector<quint16> values);
    Values getValues() { return dataCache; }

private:
    Values dataCache;

    void decodeFloatValue(quint16 v1, quint16 v2, float* output);
    float calculHumidite(float);

signals:
    void dataReceived();
};