TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    GameListener.cpp \
    Chess.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    GameListener.h \
    Chess.h
