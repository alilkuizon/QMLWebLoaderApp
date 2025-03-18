#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <mainviewmodel.h>
#include <qmlloader.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QMLLoader qmlLoader;
    qmlLoader.fetchAvailableQMLFiles();

    QQuickView view;
    MainViewModel viewModel(&view);
    viewModel.renderView();

    return app.exec();
}
