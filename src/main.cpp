#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <clientViewModel.h>
#include <webserver.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView view;
    ClientViewModel viewModel(&view);
    WebServer server(&view);
    viewModel.connecttoWebServer(&server);
    viewModel.renderView();

    return app.exec();
}
