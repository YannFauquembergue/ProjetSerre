#include "TCW241.h"

TCW241::TCW241(QString ip, int port, QObject* parent)
    : QModbusTcpClient(ip, port, parent)
{
    dataCache.analogInput1 = -1;
    dataCache.analogInput2 = -1;
    dataCache.analogInput3 = -1;
    dataCache.sensorInput1 = -1;
    dataCache.sensorInput2 = -1;

    dataCache.isArrosoir = false;
    dataCache.isBrumisation = false;
    dataCache.isVerinFenetre = false;
    dataCache.isChauffage1 = false;

    QObject::connect(this, &TCW241::onReadMultipleHoldingRegistersSentence, this, &TCW241::onFC3ResultReceived);
}

TCW241::~TCW241()
{
}

// On calcul  l'humidité par rapport à la tension (A REVOIR)
float TCW241::calculHumidite(float Vout)
{
    Vout *= 1000; //conversion V -> mV demande
    float humid = -1.91 * pow(10, -9) * pow(Vout, 3);
    humid += 1.33 * pow(10, -5) * pow(Vout, 2);
    humid += 9.56 * pow(10, -3) * Vout;
    humid -= 2.16 * pow(10, 1);

    if (humid < 0.0f)
        humid = 0.02f;
    else if (humid > 100.0f)
        humid = 100.0f;

    return humid;
}

// On décoder les valeurs floats/reeels qu'on reçoit (sur 8 bits)
void TCW241::decodeFloatValue(quint16 v1, quint16 v2, float* output)
{
    char* ptr = (char*)output;
    ptr[3] = (v1 & 0xFF00) >> 8;
    ptr[2] = v1 & 0x00FF;
    ptr[1] = (v2 & 0xFF00) >> 8;
    ptr[0] = v2 & 0x00FF;
}

//fonctions pour allumer l'arrosoir
void TCW241::Relay1ON()
{
    forceSingleCoilFC5(100, true);
    dataCache.isArrosoir = true;
}

//fonctions pour eteindre l'arrosoir
void TCW241::Relay1OFF()
{
    forceSingleCoilFC5(100, false);
    dataCache.isArrosoir = false;
}

//fonctions pour allumer la brumisation
void TCW241::Relay2ON()
{
    forceSingleCoilFC5(101, true);
    dataCache.isBrumisation = true;
}

//fonctions pour eteindre la brumisation
void TCW241::Relay2OFF()
{
    forceSingleCoilFC5(101, false);
    dataCache.isBrumisation = false;
}

//fonctions pour allumer le chauffage
void TCW241::Relay3ON()
{
    forceSingleCoilFC5(102, true);
    dataCache.isChauffage1 = true;
}

//fonctions pour eteindre le chauffage
void TCW241::Relay3OFF()
{
    forceSingleCoilFC5(102, false);
    dataCache.isChauffage1 = false;
}

//fonctions pour ouvrir la fenetre
void TCW241::Relay4ON()
{
    forceSingleCoilFC5(103, true);
    dataCache.isVerinFenetre = true;
}

//fonctions pour fermer la fenetre
void TCW241::Relay4OFF()
{
    forceSingleCoilFC5(103, false);
    dataCache.isVerinFenetre = false;
}

// On va prendre la tension des capteurs d'humidité
void TCW241::readData1()
{
    readMultipleHoldingRegistersFC3(300, 6);
}

// Renvoie la température intérieur et humidité intérieur
void TCW241::readData2()
{
    readMultipleHoldingRegistersFC3(100, 4);
}

void TCW241::onFC3ResultReceived(quint16 startAddress, QVector<quint16> values)
{
    // Analog inputs : (On lit la tension des 3 capteurd d'humidité du sol)
    if (startAddress == 300)
    {
        decodeFloatValue(values[0], values[1], &dataCache.analogInput1);
        decodeFloatValue(values[2], values[3], &dataCache.analogInput2);
        decodeFloatValue(values[4], values[5], &dataCache.analogInput3);

        dataCache.consoElectrique = dataCache.analogInput1 + dataCache.analogInput2 + dataCache.analogInput3;

        // on calcule ensuite l'humidité par rapport à la tension de chaque capteur
        dataCache.analogInput1 = this->calculHumidite(dataCache.analogInput1);
        dataCache.analogInput2 = this->calculHumidite(dataCache.analogInput2);
        dataCache.analogInput3 = this->calculHumidite(dataCache.analogInput3);
    }
    else if(startAddress == 100) // Sensor inputs : On lit les deux valeurs du capteurs (le taux d'humidité intérieur et la température intérieur)
    {
        decodeFloatValue(values[0], values[1], &dataCache.sensorInput1);
        decodeFloatValue(values[2], values[3], &dataCache.sensorInput2);
    }

    emit dataReceived(); // On dit qu'on à recu des données
}