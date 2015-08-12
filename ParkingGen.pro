TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    src/pvertexesnode.cpp \
    src/plinesnode.cpp \
    src/pplacesnode.cpp \
    src/parking.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/pvertexesnode.h \
    src/plinesnode.h \
    src/pplacesnode.h \
    src/parking.h
