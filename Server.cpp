#include "Server.h"
#include <QJsonDocument>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <qthread.h>

Serveur::Serveur(QObject * parent)
    : QObject(parent)
{
    //params = new QSettings("config.ini", QSettings::IniFormat);
    tcw = new TCW241("192.168.65.6", 502, this);
    tcw->connectToHost();
    poseidon = new Poseidon2("192.168.65.119", 502, this);
    poseidon->connectToHost();
    chrono = new QTimer();
    wSocketServer = new QWebSocketServer(QStringLiteral("Server WebSocket"), QWebSocketServer::NonSecureMode);

    QObject::connect(tcw, SIGNAL(dataReceived()), this, SLOT(onDataUpdated()));
    QObject::connect(chrono, SIGNAL(timeout()), this, SLOT(sendReadRequests()));

    chrono->start(5000); //toutes les 60 secondes, on envoie tout les trames pour récupérer les données

    if (this->wSocketServer->listen(QHostAddress::AnyIPv4, 12345))
    {
        QObject::connect(wSocketServer, SIGNAL(newConnection()), this, SLOT(onWebSocketConnected()));
        qDebug() << "Server WebSocket: Debut d'ecoute sur le port" << 12345;
    }
    else
        qDebug() << "Server WebSocket: Erreur d'ecoute sur le port" << 12345;

    /* Envoi en BDD (A FAIRE PAR LA SUITE)
    QObject::connect(chrono1, SIGNAL(timeout()), this, SLOT(envoiBDD()));
    chrono1->start(600000); //toutes les 10 minutes, on stocke les donnees en BDD
    */
}

Serveur::~Serveur()
{
    delete tcw, poseidon, chrono, wSocketServer;
}

// Connexion d'un nouveau client
void Serveur::onWebSocketConnected()
{
    if (sender() == wSocketServer) // Si c'est un objet QWebSocketServer
    {
        // [WebSocket]
        QWebSocket* clientWeb = wSocketServer->nextPendingConnection();
        wSocket.append(clientWeb);

        // [WebSocket]
        QObject::connect(clientWeb, &QWebSocket::textMessageReceived, this, &Serveur::onWebDataReceived);
        QObject::connect(clientWeb, SIGNAL(disconnected()), this, SLOT(onWebSocketDisconnected()));

        qDebug("Nouveau client connecte");
    }
}

// Deconnexion d'un client
void Serveur::onWebSocketDisconnected()
{
    if (sender() == wSocketServer) // Si c'est un objet QWebSocketServer
    {
        // [WebSocket]
        QWebSocket* clientWeb = qobject_cast<QWebSocket*>(sender());

        // [WebSocket]
        QObject::disconnect(clientWeb, &QWebSocket::textMessageReceived, this, &Serveur::onWebDataReceived);
        QObject::disconnect(clientWeb, SIGNAL(disconnected()), this, SLOT(onWebSocketDisconnected()));

        // [WebSocket]
        wSocket.removeOne(clientWeb);
        clientWeb->deleteLater();

        qDebug("Client deconnecte");
    }
}

// ENVOIE DES DIFFERENTES TRAMES de données
void Serveur::sendReadRequests()
{
    poseidon->trameTemperature(); // Récupére la température
    QThread::msleep(20);

    tcw->readData1();
    poseidon->trameLevel(); // Récupére le niveau d'eau (si y'en à ou pas)
    tcw->readData2();

    QThread::msleep(20);
    poseidon->trameDebit();
}

// Mise à jour des données et envoie de celles-ci aux clients
void Serveur::onDataUpdated()
{
    Values valuesTCW241 = tcw->getValues();
    ValuesX valuesPoseidon = poseidon->getValues();

    // Créer un nouvel objet JSON avec la structure souhaitée
    QJsonObject donnees_serre;
    QJsonArray dataArray;

    // Ajout des capteurs
    QJsonObject capteurs;
    capteurs["HumiditeInterieure"] = QString::number(valuesTCW241.sensorInput2, 'f', 2) + " %";
    capteurs["TemperatureInterieure"] = QString::number(valuesTCW241.sensorInput1, 'f', 2) + " °C";
    capteurs["HumiditeSol1"] = QString::number(valuesTCW241.analogInput1, 'f', 2) + " %";
    capteurs["HumiditeSol2"] = QString::number(valuesTCW241.analogInput2, 'f', 2) + " %";
    capteurs["HumiditeSol3"] = QString::number(valuesTCW241.analogInput3, 'f', 2) + " %";
    capteurs["TemperatureExterieure"] = QString::number(valuesPoseidon.sensorInput1, 'f', 2) + " °C";
    capteurs["ConsommationElectrique"] = QString::number(valuesTCW241.consoElectrique, 'f', 2)  + " V";
    capteurs["ConsommationEauPluie"] = valuesPoseidon.debitEauPluie;
    capteurs["ConsommationEauCourante"] = valuesPoseidon.debitEauCourante;
    capteurs["NiveauEau"] = valuesPoseidon.level;

    // Ajout des actionneurs
    QJsonObject actionneurs;
    actionneurs["VerinFenetre"] = valuesTCW241.isVerinFenetre;
    actionneurs["Chauffage1"] = valuesTCW241.isChauffage1;
    actionneurs["Brumisation"] = valuesTCW241.isBrumisation;
    actionneurs["HumidifierSerre"] = valuesTCW241.isArrosoir;

    // Ajouter les objets capteurs et actionneurs au tableau
    dataArray.append(QJsonObject{ {"capteurs", capteurs} });
    dataArray.append(QJsonObject{ {"actionneurs", actionneurs} });

    // Ajouter le tableau au nouvel objet
    donnees_serre["donnees_serre"] = dataArray;

    // Conversion de l'objet JSON en chaîne JSON
    QJsonDocument jsonDocument(donnees_serre);
    QString jsonString = jsonDocument.toJson(QJsonDocument::Compact);  // Compact pour une chaîne JSON minimisée

    qDebug() << "---------------- TCW -----------------------------";
    qDebug() << "Analog input 1 (Humidite sol 1) : " << QString::number(valuesTCW241.analogInput1, 'f', 2).toFloat() << " % (Taux d'humidite)";
    qDebug() << "Analog input 2 (Humidite sol 2) : " << QString::number(valuesTCW241.analogInput2, 'f', 2).toFloat() << " % (Taux d'humidite)";
    qDebug() << "Analog input 3 (Humidite sol 3) : " << QString::number(valuesTCW241.analogInput3, 'f', 2).toFloat() << " % (Taux d'humidite)";
    qDebug() << "Consommation electrique totale : " << QString::number(valuesTCW241.consoElectrique, 'f', 2).toFloat() << " V (Volts)";
    qDebug() << "Sensor input 1 (TSH202v3 Value 1) Temp interieur : " << QString::number(valuesTCW241.sensorInput1, 'f', 2).toFloat() << " C (Degres)";
    qDebug() << "Sensor input 2 (TSH202v3 Value 2) Humidite interieur : " << QString::number(valuesTCW241.sensorInput2, 'f', 2).toFloat() << " % (Taux d'humidite)";
    qDebug() << "---------------- TCW -----------------------------";

    qDebug() << "---------------- POSEIDON 2 ----------------------";
    qDebug() << "Temperature exterieur (Sensor 240) :" << QString::number(valuesPoseidon.sensorInput1, 'f', 2).toFloat() << " C (Degres)";
    qDebug() << "---------------- POSEIDON 2 ----------------------";

    // Envoie des données à tout les clients connectés
    for (auto it = wSocket.begin(); it != wSocket.end(); it++)
        (*it)->sendTextMessage(jsonString);
}

// Réception des messages des clients coté WEB (actionneur)
void Serveur::onWebDataReceived(const QString& message)
{
    QWebSocket* objWeb = qobject_cast<QWebSocket*>(sender());
    QJsonObject jsonMessage = QJsonDocument::fromJson(message.toUtf8()).object(); // On décode en objet JSON      

    if (jsonMessage["VerinFenetre"].isBool()) // si on recoit une action sur le Verin
    {
        if (jsonMessage["VerinFenetre"].toBool() == true)
        {
            tcw->Relay4ON();
            qDebug() << "VerinFenetre activer";
        }
        else if (jsonMessage["VerinFenetre"].toBool() == false)
        {
            tcw->Relay4OFF();
            qDebug() << "VerinFenetre desactiver";
        }
    }
    else if (jsonMessage["Chauffage1"].isBool()) // SINON si on recoit une action sur le Chauffage
    {
        if (jsonMessage["Chauffage1"].toBool() == true)
        {
            tcw->Relay3ON();
            qDebug() << "Chauffage1 activer";
        }
        else if (jsonMessage["Chauffage1"].toBool() == false)
        {
            tcw->Relay3OFF();
            qDebug() << "Chauffage1 desactiver";
        }
    }
    else if (jsonMessage["Brumisation"].isBool()) // SINON si on recoit une action sur la brumisation
    {
        if (jsonMessage["Brumisation"].toBool() == true)
        {
            poseidon->reseauEau(); // On regarde d'abord sur quel réseau d'eau se mettre
            tcw->Relay1ON();

            qDebug() << "Brumisation activer";
        }
        else if (jsonMessage["Brumisation"].toBool() == false)
        {
            //fermeture brumisation
            tcw->Relay1OFF();
            poseidon->stopPump();
            poseidon->eauPluie(); // JSP Pourquoi

            qDebug() << "Brumisation desactiver";
        }
    }
    else if (jsonMessage["HumidifierSerre"].isBool()) // SINON si on recoit une action sur l'arrosoir
    {
        if (jsonMessage["HumidifierSerre"].toBool() == true)
        {
            poseidon->reseauEau(); // On regarde d'abord sur quel réseau d'eau se mettre
            //ouverture arrosage
            tcw->Relay2ON();

            qDebug() << "Brumisation activer";
        }
        else if (jsonMessage["HumidifierSerre"].toBool() == false)
        {
            //fermeture brumisation
            tcw->Relay2OFF();
            poseidon->stopPump();
            poseidon->eauPluie(); // JSP Pourquoi

            qDebug() << "Brumisation desactiver";
        }
    }

    onDataUpdated();
}