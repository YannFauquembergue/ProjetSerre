#pragma once

#include <QtDebug>
#include <QJsonDocument>
#include <QJsonObject>
//#include <QNetworkAccessManager>
//#include <QNetworkReply>
#include <QTimer>
//#include <QUrlQuery>
#include <QWebSocket>
#include <QWebSocketServer>

#include "TCW241.h"
#include "Poseidon2.h"
#include "QModbusTcpClient.h"

class Serveur : public QObject
{
    Q_OBJECT

public:
    Serveur(QObject * parent = nullptr);
    ~Serveur();

public slots:
    void onWebSocketConnected();
    void onWebSocketDisconnected();
    void sendReadRequests();

    void onWebDataReceived(const QString& message);
    void onDataUpdated();

private:
    QList<QWebSocket*> wSocket;
    QWebSocketServer* wSocketServer;

    //Parametres present dans le fichier config.ini
    //QSettings* params;
    // Chrono pour envoyer les données en websocket
    QTimer* chrono;
    //variable contenant l'ip et le port des cartes E/S
    TCW241* tcw;
    Poseidon2* poseidon;
    //Variable utilisee pour l'envoi en BDD
    //QNetworkAccessManager* mgr = new QNetworkAccessManager();
};


