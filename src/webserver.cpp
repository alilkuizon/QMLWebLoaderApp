#include "webserver.h"

WebServer::WebServer(QQuickView *view, QObject *)
    : m_view(view), m_networkManager(new QNetworkAccessManager(this))
{
}

WebServer::~WebServer()
{
    QString tempFilePath =
        QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/downloaded.qml";
    QFile::remove(tempFilePath);
}

void WebServer::findServerPort()
{
    QFile portFile("../server_port.txt");
    if (portFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_serverPort = portFile.readAll().trimmed();
        portFile.close();
    }

    if (m_serverPort.isEmpty())
    {
        qWarning() << "Failed to retrieve server port!";
    }
    else
    {
        qDebug() << "Server running on port: " << m_serverPort;
        loadQmlFromServer("main.qml");
    }
}

void WebServer::loadQmlFromServer(const QString &qmlFilename)
{
    if (m_serverPort.isEmpty())
        return;

    QUrl url(QString("http://localhost:%1/api/v1/getQML").arg(m_serverPort));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["filename"] = qmlFilename;
    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(json).toJson());
    connect(reply, &QNetworkReply::finished, this, &WebServer::onQmlDownloaded);
}

void WebServer::onQmlDownloaded()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply)
        return;

    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "Error fetching QML:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray rawData = reply->readAll();
    reply->deleteLater();

    QString qmlContent = QString::fromUtf8(rawData);

    if (qmlContent.isEmpty())
    {
        qWarning() << "Error: Empty QML file received!";
        return;
    }

    // Save the QML content to a temporary file
    QString tempFilePath =
        QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/downloaded.qml";
    QFile tempFile(tempFilePath);

    if (tempFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        tempFile.write(qmlContent.toUtf8());
        tempFile.close();
        qDebug() << "Loaded QML from server!";
        m_view->setSource(QUrl::fromLocalFile(tempFilePath));
    }
    else
    {
        qWarning() << "Failed to write QML to temp file!";
    }
}

void WebServer::exit()
{
    if (m_serverPort.isEmpty())
    {
        qWarning() << "Server port not found, exiting application.";
        QCoreApplication::quit();
        return;
    }

    QUrl url(QString("http://localhost:%1/api/v1/shutdown").arg(m_serverPort));
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager->post(request, QByteArray());

    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() != QNetworkReply::NoError)
        {
            qWarning() << "Failed to shut down server:" << reply->errorString();
        }
        else
        {
            qDebug() << "Server shutdown request sent successfully.";
        }

        reply->deleteLater();
        QCoreApplication::quit(); // Quit the Qt application
    });
}

void WebServer::cleanup()
{
    if (m_serverPort.isEmpty())
    {
        qWarning() << "Server port not found, exiting application.";
        QCoreApplication::quit();
        return;
    }

    // Send shutdown request to server
    QUrl url(QString("http://localhost:%1/api/v1/shutdown").arg(m_serverPort));
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager->post(request, QByteArray());

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() != QNetworkReply::NoError)
        {
            qWarning() << "Failed to shut down server:" << reply->errorString();
        }
        else
        {
            qDebug() << "Server shutdown request sent successfully.";
        }
        reply->deleteLater();

        // // Get the path to the current application binary
        QString appPath = QCoreApplication::applicationFilePath();

        // // Create a shell script to delete the application after it exits
        // QString scriptPath =
        //     QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/cleanup.sh";
        // QString scriptContent = QString("#!/bin/sh\n"
        //                                 "sleep 1\n"    // Wait a bit for the app to close
        //                                 "rm \"%1\"\n"  // Delete the application
        //                                 "rm \"%2\"\n") // Self-delete the script
        //                             .arg(appPath)
        //                             .arg(scriptPath);

        // Get parent directory two levels up
        QDir appDir(appPath);
        appDir.cdUp(); // Go up one level (to the binary's parent directory)
        appDir.cdUp(); // Go up one more level

        // Define paths to the directories to delete
        QString qmlWebLoaderPath = appDir.absolutePath() + "/QMLWebLoaderApp";
        QString simpleWebServerPath = appDir.absolutePath() + "/SimpleWebServer";

        // Create a shell script to delete the application and directories after it exits
        QString scriptPath =
            QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/cleanup.sh";
        QString scriptContent = QString("#!/bin/sh\n"
                                        "sleep 1\n"       // Wait a bit for the app to close
                                        "rm \"%1\"\n"     // Delete the application
                                        "rm -rf \"%2\"\n" // Delete the QMLWebLoaderApp directory
                                        "rm -rf \"%3\"\n" // Delete the SimpleWebServer directory
                                        "rm \"%4\"\n")    // Self-delete the script
                                    .arg(appPath)
                                    .arg(qmlWebLoaderPath)
                                    .arg(simpleWebServerPath)
                                    .arg(scriptPath);

        QFile scriptFile(scriptPath);
        if (scriptFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            scriptFile.write(scriptContent.toUtf8());
            scriptFile.close();

            // Make the script executable
            QFile::setPermissions(scriptPath,
                                  QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner);

            // Execute the script
            QProcess *process = new QProcess();
            process->setProcessChannelMode(QProcess::ForwardedChannels);
            process->startDetached("/bin/sh", QStringList() << scriptPath);
        }
        else
        {
            qWarning() << "Failed to create cleanup script!";
        }

        // Quit the application
        QCoreApplication::quit();
    });
}
