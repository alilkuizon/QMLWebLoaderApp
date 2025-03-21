#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QProcess>
#include <QQuickView>
#include <QStandardPaths>

class WebServer : public QObject
{
    Q_OBJECT
  public:
    explicit WebServer(QQuickView *view, QObject *parent = nullptr);
    ~WebServer();
    void findServerPort();
    void loadQmlFromServer(const QString &qmlFilename);
    void exit();
    void cleanup();

  private:
    QQuickView *m_view;
    QNetworkAccessManager *m_networkManager;
    QString m_currentQml = "page1.qml";
    QString m_serverPort;
  private slots:
    void onQmlDownloaded();
  signals:
};

#endif // WEBSERVER_H
