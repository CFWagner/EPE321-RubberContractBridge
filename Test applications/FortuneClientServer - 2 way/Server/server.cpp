/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>
#include <QDebug>

#include "server.h"

Server::Server(QWidget *parent): QDialog(parent), hostCombo(new QComboBox), statusLabel(new QLabel), clientOutLabel(new QLabel)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    statusLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);



    //! [2]
    fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
             << tr("You've got to think about tomorrow.")
             << tr("You will be surprised by a loud noise.")
             << tr("You will feel hungry again in another hour.")
             << tr("You might have mail.")
             << tr("You cannot kill time without injuring eternity.")
             << tr("Computers are not intelligent. They only think they are.");
    //! [2]
    hostCombo->setEditable(true);
    // find out IP addresses of this machine
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add non-localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (!ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    // add localhost addresses
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i).isLoopback())
            hostCombo->addItem(ipAddressesList.at(i).toString());
    }
    auto hostLabel = new QLabel(tr("&Server name:"));
    hostLabel->setBuddy(hostCombo);

    auto quitButton = new QPushButton(tr("Quit"));
    quitButton->setAutoDefault(false);


    connect(quitButton, &QAbstractButton::clicked, this, &QWidget::close);
    //! [3]
//    initServer();
    connect(hostCombo, &QComboBox::editTextChanged,this, &Server::initServer);
    //connect(tcpServer, &QTcpServer::newConnection, this, &Server::sendFortune);

    //! [3]

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = nullptr;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        auto outerVerticalLayout = new QVBoxLayout(this);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
        auto outerHorizontalLayout = new QHBoxLayout;
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        auto groupBox = new QGroupBox(QGuiApplication::applicationDisplayName());
        mainLayout = new QVBoxLayout(groupBox);
        outerHorizontalLayout->addWidget(groupBox);
        outerHorizontalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::Ignored));
        outerVerticalLayout->addLayout(outerHorizontalLayout);
        outerVerticalLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding));
    } else {
        mainLayout = new QVBoxLayout(this);
    }
    mainLayout->addWidget(hostLabel, 0);
    mainLayout->addWidget(hostCombo, 0);
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(clientOutLabel, 0);

    setWindowTitle(QGuiApplication::applicationDisplayName());

}

void Server::initServer()
{
//! [0] //! [1]

//! [0]
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        qInfo() << ipAddressesList.at(i).toString().toUtf8().data() << "\n";
        // https://stackoverflow.com/questions/3886105/how-to-print-to-console-when-using-qt
//        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
//            ipAddressesList.at(i).toIPv4Address()) {
//            ipAddress = ipAddressesList.at(i).toString();

//            break;
//        }
    }
    qInfo() << "qInfo: " << hostCombo->currentText();
    ipAddress = QHostAddress(hostCombo->currentText()).toString();
//    ipAddress = QHostAddress().toString();
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    qInfo() << "Server - 1";
    if (clientConnection != nullptr){
        qInfo() << "Server - 2";
        disconnect(clientConnection, &QIODevice::readyRead,0,0);
        qInfo() << "Server - 3";
        clientConnection->disconnectFromHost();
        clientConnection = nullptr;
    }
    qInfo() << "Server - 4";
    if (tcpServer != nullptr){
        qInfo() << "Server - 5";
        disconnect(tcpServer, &QTcpServer::newConnection, 0, 0);
        qInfo() << "Server - 6";
        tcpServer->close();
        qInfo() << "Server - 7";
    } else{
        qInfo() << "Server - 8";
        tcpServer = new QTcpServer(this);
        qInfo() << "Server - 9";
    }
    if (!tcpServer->listen(QHostAddress(ipAddress))) {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
    qInfo() << "Server - 10";
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::connectClient);
    qInfo() << "Server - 11";
    statusLabel->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Run the Fortune Client example now.")
                         .arg(ipAddress).arg(tcpServer->serverPort()));
    qInfo() << "Server - 12";
}

void Server::connectClient()
{
    clientConnection = tcpServer->nextPendingConnection();


//    if (!clientConnection) {
//        serverStatusLabel->setText(tr("Error: got invalid pending connection!"));
//        return;
//    }

    connect(clientConnection, &QIODevice::readyRead,this, &Server::sendFortune);
    connect(clientConnection, &QAbstractSocket::disconnected,clientConnection, &QObject::deleteLater);

    tcpServer->close();
}

//! [4]
void Server::sendFortune()
{
//    QByteArray data_buffer = clientConnection->readAll();
    in.setDevice(clientConnection);
    in.setVersion(QDataStream::Qt_5_10);
    // Read the data
    in.startTransaction();
    qint64 inputFromClient;
    in >> inputFromClient;
    if (!in.commitTransaction())
        return;

//    qInfo() << "Server write block: " << inputFromClient;
    clientOutLabel->setText(QString::number(inputFromClient));
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);

    out << fortunes[QRandomGenerator::global()->bounded(fortunes.size())];
//! [4] //! [7]

//    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
//    connect(clientConnection, &QAbstractSocket::disconnected,
//            clientConnection, &QObject::deleteLater);
//! [7] //! [8]

    clientConnection->write(block);
//    clientConnection->disconnectFromHost();
//! [5]
}


