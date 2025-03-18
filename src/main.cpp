#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <qmlloader.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;
    view.setTitle("QML Web Loader App");
    view.setWidth(640);
    view.setHeight(480);
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    QMLLoader qmlLoader(&view);
    qmlLoader.fetchAvailableQMLFiles();
    // QStringList qmlList = qmlLoader.fetchAvailableQMLFiles();

    // for (const QString& item : qmlList) {
    //     qDebug() << "Item:" << item;
    // }

    QUrl qmlUrl1("qrc:/qml/main.qml");
    view.setSource(qmlUrl1);

    return app.exec();
}
