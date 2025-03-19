#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <mainviewmodel.h>
#include <webserver.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    MainViewModel viewModel(&view);
    viewModel.renderView();

    WebServer server(&view);
    server.findServerPort();

    return app.exec();
}
