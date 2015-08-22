#include <QApplication>
#include <QQmlApplicationEngine>

#include "src/parking.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<ParkingQuickItem>("CustomGeometry", 1, 0, "Parking");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
