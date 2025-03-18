#ifndef QMLLOADER_H
#define QMLLOADER_H

#include <QDir>
#include <QNetworkAccessManager>
#include <QObject>

class QMLLoader : public QObject
{
    Q_OBJECT
public:
  explicit QMLLoader(QObject *parent = nullptr);
  QStringList fetchAvailableQMLFiles();
  void loadQMLFile(const QString &filename);

private:
  QNetworkAccessManager *manager;

signals:
};

#endif // QMLLOADER_H
