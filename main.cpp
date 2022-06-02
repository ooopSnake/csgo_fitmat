#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qt_windows.h>
#include <WinUser.h>
#include <QString>
#include <QDebug>
#include <QQmlContext>
#include <QVariant>
#include "display.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    qRegisterMetaType<DisplaySetting>("DisplaySetting");    
    Display display;
    QQmlApplicationEngine engine;
    auto* engin_ctx = engine.rootContext();
    engin_ctx->setContextProperty("display",&display);
    auto args = QGuiApplication::arguments();
    engin_ctx->setContextProperty("autoExit",QVariant::fromValue((args.size()>1 ? args[1] : "0")));
    const QUrl url("qrc:/fit_mat/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
