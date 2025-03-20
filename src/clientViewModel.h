#ifndef CLIENTVIEWMODEL_H
#define CLIENTVIEWMODEL_H

#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QTimer>
#include <webserver.h>

#ifdef Q_OS_LINUX
#include <libudev.h>
#elif defined(Q_OS_MACOS)
#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>
#endif

class ClientViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString elapsedTime READ elapsedTime NOTIFY elapsedTimeChanged FINAL)
    Q_PROPERTY(bool isTimerActive READ isTimerActive NOTIFY timerStatusChanged FINAL)
    Q_PROPERTY(QStringList devices READ devices NOTIFY devicesChanged)
  public:
    explicit ClientViewModel(QQuickView *, QObject *parent = nullptr);
    void renderView();
    void connecttoWebServer(WebServer *server);

    Q_INVOKABLE void toggleTimer();
    Q_INVOKABLE void fetchUSBDeviceList();
    Q_INVOKABLE void exit();
    Q_INVOKABLE void cleanup();

    QString elapsedTime() const;
    bool isTimerActive() const;
    QStringList devices() const;

  private:
    QQuickView *view;
    WebServer *server;
    QString m_elapsedTime;
    QTimer timer;
    int timerCount;
    QStringList m_devices;

    QStringList getUsbDevicesList();

  public slots:
    void onTimeOut();
  signals:
    void elapsedTimeChanged();
    void timerStatusChanged();
    void devicesChanged();
};

#endif // CLIENTVIEWMODEL_H
