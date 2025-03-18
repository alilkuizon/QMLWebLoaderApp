#include "qmlloader.h"

QMLLoader::QMLLoader(QQuickView *mView, QObject *)
    : view(mView), manager(new QNetworkAccessManager(this))
{
}

QStringList QMLLoader::fetchAvailableQMLFiles()
{ // Set import path and load Main.qml
    QString activeDir = QDir::currentPath();
    qDebug() << "Active Directory: " << activeDir; // Debugging output

    // Set QML import path to active directory
    view->engine()->addImportPath(activeDir);

    return QStringList();
}
