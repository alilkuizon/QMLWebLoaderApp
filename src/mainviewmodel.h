#ifndef MAINVIEWMODEL_H
#define MAINVIEWMODEL_H

#include <QObject>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickView>
#include <QTimer>

class MainViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString elapsedTime READ elapsedTime NOTIFY elapsedTimeChanged FINAL)
    Q_PROPERTY(bool isTimerActive READ isTimerActive NOTIFY timerStatusChanged FINAL)
    Q_PROPERTY(QStringList devices READ devices NOTIFY devicesChanged)
  public:
    explicit MainViewModel(QQuickView *, QObject *parent = nullptr);
    void renderView();

    Q_INVOKABLE void toggleTimer();
    Q_INVOKABLE void fetchUSBDeviceList();

    QString elapsedTime() const;
    bool isTimerActive() const;
    QStringList devices() const;

  private:
    QQuickView *view;
    QString m_elapsedTime;
    QTimer timer;
    int timerCount;
    QStringList m_devices;

  private slots:
    void onTimeOut();
  signals:
    void elapsedTimeChanged();
    void timerStatusChanged();
    void devicesChanged();
};

#endif // MAINVIEWMODEL_H
