#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <qrtchart.h>
#include <glchart.h>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qmlRegisterType<QRTChart>("QRTChart", 1, 0, "QRTChart");
    qmlRegisterType<GLChart>("Shapes", 1, 0, "Triangle");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
