#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <customchart.h>
#include <qrtchart.h>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<CustomChart>("Chart", 1, 0, "CustomChart");
    qmlRegisterType<QRTChart>("QRTChart", 1, 0, "QRTChart");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
