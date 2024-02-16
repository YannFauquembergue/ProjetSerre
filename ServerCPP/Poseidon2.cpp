#include "Poseidon2.h"

Poseidon2::Poseidon2(QString ip, int port, QObject* parent)
    : QModbusTcpClient(ip, port, parent)
{
    this->dataCache.eau = false; // eau de pluie->true et eau courante->false
    this->dataCache.level = false; // niveau d'eau (flotteur = true ou false)

    this->dataCache.sensorInput1 = -1; // Temperature exterieure
    this->dataCache.debitEauCourante = -1; // Debit eau courante
    this->dataCache.debitEauPluie = -1; // Debit eau de pluie

    QObject::connect(this, &Poseidon2::onReadMultipleInputRegistersSentence, this, &Poseidon2::onFC4ResultReceived);
    QObject::connect(this, &Poseidon2::onReadMultipleInputsStatusSentence, this, &Poseidon2::onFC2ResultReceived); // FCT 2 plusieurs valeurs
}

Poseidon2::~Poseidon2()
{
}

void Poseidon2::resetCounterDebit()
{
    // Fonction 16
    //char trame[] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x0B, 0x11, 0x10, 0x00, static_cast<char>(0xCB), 0x00, 0x01, 0x02, 0x00, 0x00 };

    //this->presetMultipleRegistersFC16(203, values); // On reset le nombre de débit sur l'adresse 203 (CB) en écrivant sur 1 registre  (00 01) et à écrite sur deux octets (02) qui est à la valeur 0 (00 00)
}

//envoi de la trame de lecture pour récupérer la température
void Poseidon2::trameTemperature()
{
    //char trameTemp[] = { 0x00, TEMPERATURE_ID, 0x00, 0x00, 0x00, 0x06, 0x11, 0x04, 0x00, 0x64, 0x00, 0x01 };

    this->readMultipleInputRegistersFC4(100, 1);
}


// Lecture du NIVEAU D'EAU
void Poseidon2::trameLevel()
{
    //char trameNiv[] = { 0x00, LEVEL_ID, 0x00, 0x00, 0x00, 0x06, 0x11, 0x02, 0x00, 0x63, 0x00, 0x01 };

    this->readMultipleInputsStatusFC2(99, 1);
}

// Lecture du niveau du débit de l'eau
void Poseidon2::trameDebit()
{  //input 2 : adresse 203
    //char trameDeb[] = { 0x00, DEBIT_ID, 0x00, 0x00, 0x00, 0x06, 0x11, 0x04, 0x00, static_cast<char>(0xCB), 0x00, 0x01 };
    //input 3 : adresse 205
    //char trameDeb[] = { 0x00, DEBIT_ID, 0x00, 0x00, 0x00, 0x06, 0x11, 0x04, 0x00, static_cast<char>(0xCD), 0x00, 0x01 };
    //input 4 : adresse 207
    //char trameDeb[] = { 0x00, DEBIT_ID, 0x00, 0x00, 0x00, 0x06, 0x11, 0x04, 0x00, static_cast<char>(0xCF), 0x00, 0x01 };

    this->readMultipleInputRegistersFC4(200, 8);
}

// Fonction de réponse pour savoir si y'a de l'eau dans le bac
void Poseidon2::onFC2ResultReceived(quint16 startAddress, QVector<bool> values)
{
    // NIVEAU D'EAU
    if (values[0] == true) // Si y'a de l'eau (que le flotteur flotte)
    {
        qDebug() << "EAU DE PLUIE  = " << values[0];
        this->dataCache.level = true;
        reseauEau(); // Pour voir si on peut passer sur l'eau de pluie

    }
    else // Sinon si y'a pas d'eau (que le flotteur ne flotte pas)
    {
        qDebug() << "EAU COURANTE = " << values[0];
        this->dataCache.level = false;
        this->reseauEau(); // Pour passer sur l'eau courante
    }
}

// Fonction de réponse pour récupérer la température et/ou le débit d'eau
void Poseidon2::onFC4ResultReceived(quint16 startAddress, QVector<quint16> values)
{
    // Temperature
    if (startAddress == 100) // Si trame de réponse pour la température extérieure
    {
        qint16 conv = values[0];
        this->dataCache.sensorInput1 = conv / 10.0; //Valeur temp ext/10 (pour l'avoir en float, reel)
        qDebug() << "Temperature exterieur (Sensor 240) :" << dataCache.sensorInput1 << "  C (Degres)";
    }
    else if (startAddress == 200) // Sinon si trame pour le debit d'eau
    {
        if (dataCache.eau == true) // Si y'a de l'eau (qu'on est sur le réseau d'eau de pluie)
        {
            this->dataCache.debitEauCourante = 0.0;
            this->dataCache.debitEauPluie = values[0]; // A changer

            qDebug() << "Conso Eau de pluie : " << this->dataCache.debitEauPluie << " L";
        }
        else if (dataCache.eau == false) // Sinon si y'a pas d'eau (qu'on est sur le réseau d'eau courante)
        {
            this->dataCache.debitEauCourante = values[0]; // A changer
            this->dataCache.debitEauPluie = 0.0;

            qDebug() << "Conso Eau courante : " << this->dataCache.debitEauCourante << " L";
        }
        else
        {
            this->dataCache.debitEauCourante = 0.0;
            this->dataCache.debitEauPluie = 0.0; // A changer

            qDebug() << "Conso d'eau : " <<  "0 L";
        }

        qDebug() << "Debit d'eau :" << values << "impulsions";
    }
}

// Fonction pour activer la pompe de relevage d'eau de pluie
void Poseidon2::activatePump()
{
    //char trame[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x11, 0x05, 0x00, static_cast<char>(0xC8), static_cast<char>(0xFF), 0x00 };
    this->forceSingleCoilFC5(200, true); // On active donc la pompe de relevage (FF 00 = ON) à l'adresse 200 (C8)

    qDebug() << "La pompe est allumee\n";
}

// Fonction pour arrêter la pompe de relevage d'eau de pluie
void Poseidon2::stopPump()
{
    //char trame[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x11, 0x05, 0x00, static_cast<char>(0xC8), 0x00, 0x00 };
    this->forceSingleCoilFC5(200, false); // On désactive donc la pompe de relevage (00 00 = OFF) à l'adresse 200 (C8)

    qDebug() << "La pompe est eteinte\n";
}

// Fonction pourr passer sur l'eau de  pluie
void Poseidon2::eauPluie()
{
    //char trame[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x11, 0x05, 0x00, static_cast<char>(0xC7), 0x00, 0x00 };
    this->forceSingleCoilFC5(199, false); // On désactive donc la vanne eau courante (00 00 = OFF) à l'adresse 199 (C7)

    qDebug() << "NOUS SOMMES MAINTENANT SUR L'EAU DE PLUIE";
    this->dataCache.eau = true;
}

// Fonction pourr passer sur l'eau courante
void Poseidon2::eauCourante()
{
    //char trame[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x11, 0x05, 0x00, static_cast<char>(0xC7), static_cast<char>(0xFF), 0x00 };
    this->forceSingleCoilFC5(199, true); // On active donc la vanne eau courante (FF 00 = ON) à l'adresse 199 (C7)

    qDebug() << "NOUS SOMMES MAINTENANT SUR L'EAU COURANTE";
    this->dataCache.eau = false;
}

// Fonction pour changer le réseau d'eau en fonction du niveau d'eau et de la température extérieure
void Poseidon2::reseauEau()
{
    if (dataCache.level == true && dataCache.sensorInput1 > 3.0f) // Si y'a de l'eau et que la température est supérieur à 3 degrés
    {
        this->activatePump();
        this->resetCounterDebit();
        this->eauPluie();

        qDebug() << "Activation du reseau d'eau de pluie";
    }
    else if (dataCache.level != true || dataCache.sensorInput1 < 3.0f) // Sinon si y'a pas d'eau ou qu'on est inférieur à 3 degrés
    {
        this->stopPump();
        this->resetCounterDebit();
        this->eauCourante();

        qDebug() << "Activation du reseau d'eau courante";
    }
}