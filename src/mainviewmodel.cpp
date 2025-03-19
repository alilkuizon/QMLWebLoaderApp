#include "mainviewmodel.h"
#include <QDebug>

MainViewModel::MainViewModel(QQuickView *mView, QObject *) : view(mView)
{
    timerCount = 0;
    connect(&timer, &QTimer::timeout, this, &MainViewModel::onTimeOut);
    timer.setInterval(1000);
}

void MainViewModel::renderView()
{
    view->setTitle("QML Web Loader App");
    view->setWidth(640);
    view->setHeight(480);
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->rootContext()->setContextProperty("viewModel", this);
    view->show();
}

QString MainViewModel::elapsedTime() const
{
    return QString::number(timerCount);
}

void MainViewModel::toggleTimer()
{
    qDebug() << "Timer toggled";
    if (timer.isActive())
    {
        timerCount = 0;
        timer.stop();
        emit elapsedTimeChanged();
    }
    else
    {
        timer.start();
    }
    emit timerStatusChanged();
}

void MainViewModel::fetchUSBDeviceList()
{
    m_devices.clear();

    // ADD Fetching code here

    QString deviceInfo =
        QString("Vendor: ") + QString("vendor") + QString(" Product: ") + QString("product");
    m_devices.append(deviceInfo);

    QString deviceInfo1 =
        QString("Vendor: ") + QString("vendor") + QString(" Product: ") + QString("product");
    m_devices.append(deviceInfo1);

    QString deviceInfo2 =
        QString("Vendor: ") + QString("vendor") + QString(" Product: ") + QString("product");
    m_devices.append(deviceInfo2);

    emit devicesChanged();
}

bool MainViewModel::isTimerActive() const
{
    return timer.isActive();
}

QStringList MainViewModel::devices() const
{
    return m_devices;
}

void MainViewModel::onTimeOut()
{
    timerCount += 1;
    emit elapsedTimeChanged();
}
