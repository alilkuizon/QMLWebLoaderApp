INCLUDEPATH += $$PWD

QT+=quick
SOURCES += \
    $$PWD/clientViewModel.cpp \
    $$PWD/webserver.cpp

HEADERS += \
    $$PWD/clientViewModel.h \
    $$PWD/webserver.h

unix {
    LIBS += -ludev
    INCLUDEPATH += /usr/include/libudev
}
