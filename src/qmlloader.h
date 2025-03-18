#ifndef QMLLOADER_H
#define QMLLOADER_H

#include <QDir>
#include <QNetworkAccessManager>
#include <QObject>
#include <QQmlEngine>
#include <QQuickView>

class QMLLoader : public QObject
{
    Q_OBJECT
public:
  explicit QMLLoader(QQuickView *, QObject *parent = nullptr);
  QStringList fetchAvailableQMLFiles();
  void loadQMLFile(const QString &filename);

private:
  QQuickView *view;
  QNetworkAccessManager *manager;

signals:
};

#endif // QMLLOADER_H
